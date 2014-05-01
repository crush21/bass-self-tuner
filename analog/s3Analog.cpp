/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
#include <fstream>
#include <poll.h>

const int NUM_CYCLES = 1500;
const int PEAK_LIMIT = NUM_CYCLES / 8;
const double ONE_MIL = 1000000.0;
const double ONE_BIL = 1000000000.0;

int main(int argc, char *argv[]) {
  timespec startTime, endTime, runTime;
  double waveform[NUM_CYCLES];
  double FFTdouble[NUM_CYCLES];
  fftw_complex FFT[NUM_CYCLES];
//  double aIn;
  double totalSec, avgSec;
  fftw_plan fftPlan;

  char strIn [35] = "/sys/devices/ocp.3/helper.12/AIN2"; // Changed from helper.15 to helper.12
//  char FFTout [35] = "/root/code/output.txt";
//  char waveOut [35] = "/root/code/waveform.txt";

  if (argc != 2) {
    printf("\nYou must provide one argument.\n");
    printf("The argument represents a note for a string.\n");
    printf("The note starts at 0 = C and increases by one half step\n");
    printf("For every integer increase of 1, to a maximum of 7 = G.\n\n");
    printf("Usage: s3Analog noteNum\n");
    printf("noteNum:\n");
    printf("  Must be between 10 and 17.\n");
    exit(0);
  }

  std::cout << "\nStarting program to read analog signals.\n" << std::endl;
  
  std::cout << strIn << std::endl;
  
  int strHandle = open(strIn, O_RDONLY | O_SYNC);
  std::perror("Result");

  std::cout << "\nEntering the loop..." << std::endl;

  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;

  clock_gettime(CLOCK_MONOTONIC, &startTime);

  for (int i = 0; i < NUM_CYCLES; i++) {

    poll(&strFile, 1, -1);
    waveform[i] = getAnalog(1, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

//    waveform[i] = aIn;

//    usleep(680);
    
//    heart();

//    aIn2 = getAnalog(2, str2In);
    
//    heart();
    
//    aIn3 = getAnalog(3, str3In);
    
//    heart();
    
//    aIn4 = getAnalog(4, str4In);
    
  }
  
  clock_gettime(CLOCK_MONOTONIC,&endTime);
  runTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
  runTime.tv_nsec = endTime.tv_nsec - startTime.tv_nsec;
  totalSec = runTime.tv_sec + runTime.tv_nsec / ONE_BIL;
  avgSec = totalSec / NUM_CYCLES;
  std::cout << "Total runtime is: " << totalSec << std::endl;
  std::cout << "Average sample time is: " << avgSec << std::endl;
  close(strHandle);

  fftPlan = fftw_plan_dft_r2c_1d(NUM_CYCLES, waveform, FFT, FFTW_DESTROY_INPUT | FFTW_MEASURE);
//  std::cout << "Made it here!" << std::endl;
  fftw_execute(fftPlan);

/* Not necessary, but keeping for debugging purposes.
// Write waveform and FFT result to files.
  std::ofstream wavFile;
  std::fstream FFTfile;
  wavFile.open(waveOut);
  FFTfile.open(FFTout);
  for (int i = 0; i < (NUM_CYCLES / 2 + 1); i++) {
    wavFile << waveform[i] << std::endl;
    FFTfile << FFT[i][0] << std::endl;
  }
  wavFile.close();
  FFTfile.close();
*/

  for (int j = 1; j < (NUM_CYCLES); j++) {
    FFTdouble[j] = fabs(FFT[j][0]);
  }

  double sampleFrequency = 1 / avgSec;
  double frequency = getFrequency(FFTdouble, NUM_CYCLES - 1, PEAK_LIMIT, sampleFrequency);
  int noteNum = atoi(argv[1]);
  double idealFreq = translateFrequency(noteNum);
  std::cout << "Frequency: " << frequency << std::endl;
  std::cout << "Cent Difference: " << getCents(frequency, idealFreq) << std::endl;
  // Insert motor call.
  return 0;
}
