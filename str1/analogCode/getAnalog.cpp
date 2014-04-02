/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
//#include <fstream>
#include <poll.h>

  const int NUM_CYCLES = 8192;
  const double ONE_MIL = 1000000.0;

int main() {
  timeval startTime, endTime, runTime;
  double waveform[NUM_CYCLES];
  double FFT[NUM_CYCLES];
  double aIn;
  double totalSec, avgSec;
  fftw_plan fftPlan;
  char * strAddr;

  char strIn [35] = "/sys/devices/ocp.3/helper.15/AIN0";
//  char str2In [35] = "/sys/devices/ocp.3/helper.15/AIN1";
//  char str3In [35] = "/sys/devices/ocp.3/helper.15/AIN2";
//  char str4In [35] = "/sys/devices/ocp.3/helper.15/AIN3";
//  char FFTout [35] = "/root/code/str1/output.txt";

  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << strIn << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(strIn, O_RDONLY);
  strAddr = (char*)mmap(NULL, 1, PROT_READ, MAP_SHARED, strHandle, 0);

  cout << "\nEntering infinite loop..." << endl;
/*
  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;
*/
  gettimeofday(&startTime, NULL);

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

//    poll(&strFile, 1, -1);
    aIn = getAnalog(1, strAddr); //strFile.fd);
//    lseek(strHandle, 0, SEEK_SET);

    waveform[i] = aIn;

//    usleep(680);    
    
//    heart();

//    aIn2 = getAnalog(2, str2In);
    
//    heart();
    
//    aIn3 = getAnalog(3, str3In);
    
//    heart();
    
//    aIn4 = getAnalog(4, str4In);
    
  }
  
  gettimeofday(&endTime, NULL);
  timersub(&endTime,&startTime,&runTime);
  totalSec = runTime.tv_sec + runTime.tv_usec / ONE_MIL;
  avgSec = totalSec / NUM_CYCLES;
  cout << "Total runtime is: " << totalSec << endl;
  cout << "Average sample time is: " << avgSec << endl;
//  close(strHandle);
  fftPlan = fftw_plan_r2r_1d(NUM_CYCLES, waveform, FFT, FFTW_R2HC, FFTW_DESTROY_INPUT);
//  cout << "Made it here!" << endl;
  fftw_execute(fftPlan);
/*
  ofstream FFTfile;
  FFTfile.open(FFTout);
  for (int i = 0; i < (NUM_CYCLES / 2 + 1); i++) {
    FFTfile << FFT[i] << endl;
  }
  FFTfile.close();
*/
// Check average of FFT with DC value ( FFT[0] )
/*
  double avg = 0;
  for (int j = 1; j < (NUM_CYCLES / 2 + 1); j++) {
    if (FFT[j] < 0) {
      avg -= FFT[j];
    } else {
      avg += FFT[j];
    }
  }
  avg = avg / NUM_CYCLES;
  cout << "Average: " << avg << endl;
  cout << "FFT[0]: " << FFT[0] << endl;
  if (avg == FFT[0]) {
    cout << "Success! FFT[0] is the average!" << endl;
  }
*/
  FFT[0] = 0;
  cout << "Frequency: " << getFrequency(FFT, NUM_CYCLES / 2 + 1, totalSec) << endl;
  return 0;
}
