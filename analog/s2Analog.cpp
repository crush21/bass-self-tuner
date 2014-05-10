/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
#include <fstream>
#include <poll.h>

const int NUM_CYCLES = 4096;
const int LOW_LIMIT = NUM_CYCLES / 25;
const int PEAK_LIMIT = NUM_CYCLES / 13;
const double ONE_MIL = 1000000.0;
const double ONE_BIL = 1000000000.0;
const double THRESHOLD = 830;

int main(int argc, char *argv[]) {
  timespec startTime, endTime, runTime;
  double aIn = 0.0;
  double waveform[NUM_CYCLES];
  double FFTdouble[NUM_CYCLES];
  fftw_complex FFT[NUM_CYCLES];
  double totalSec, avgSec;
  fftw_plan fftPlan;

  char strIn [50] = "/sys/bus/iio/devices/iio:device0/in_voltage3_raw";
//  char FFTout [35] = "/root/code/output.txt";
//  char waveOut [35] = "/root/code/waveform.txt";

  if (argc != 2) {
    printf("\nYou must provide one argument.\n");
    printf("The argument represents a note for a string.\n");
    printf("The note starts at 5 = F and increases by one half step\n");
    printf("For every integer increase of 1, to a maximum of 12 = C.\n\n");
    printf("Usage: s2Analog noteNum\n");
    printf("noteNum:\n");
    printf("  Must be between 5 and 12.\n");
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

  while (aIn < THRESHOLD) {
    poll(&strFile, 1, -1);
    aIn = getAnalog(STRING2, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);
  }

  for (int i = 0; i < NUM_CYCLES; i++) {

    poll(&strFile, 1, -1);
    waveform[i] = getAnalog(STRING2, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

  }
  
  clock_gettime(CLOCK_MONOTONIC,&endTime);
  runTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
  runTime.tv_nsec = endTime.tv_nsec - startTime.tv_nsec;
  totalSec = runTime.tv_sec + runTime.tv_nsec / ONE_BIL;
  avgSec = totalSec / NUM_CYCLES;
  std::cout << "Total runtime is: " << totalSec << std::endl;
  std::cout << "Average sample time is: " << avgSec << std::endl;
  close(strHandle);

  fftw_set_timelimit(1.0);
  fftPlan = fftw_plan_dft_r2c_1d(NUM_CYCLES, waveform, FFT, FFTW_DESTROY_INPUT | FFTW_MEASURE);
//  std::cout << "Made it here!" << std::endl;
  fftw_execute(fftPlan);
/*
// Not necessary, but keeping for debugging purposes.
// Write waveform and FFT result to files.
  std::ofstream wavFile;
  std::fstream FFTfile;
  wavFile.open(waveOut);
  FFTfile.open(FFTout);
  for (int i = 0; i < NUM_CYCLES; i++) {
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
  double frequency = getFrequency(FFTdouble, NUM_CYCLES - 1, LOW_LIMIT, PEAK_LIMIT, sampleFrequency);
  int noteNum = atoi(argv[1]);
  double idealFreq = translateFrequency(noteNum);
  double freqDiff = idealFreq - frequency;
  double centDiff = getCents(frequency, idealFreq);
  std::cout << "Frequency: " << frequency << std::endl;
  std::cout << "Cent Difference: " << centDiff << std::endl;
  if (fabs(centDiff) > 5) {
//    callMotor(STRING2, freqDiff);
  } else {
    return 1;
  }
  return 0;
}
