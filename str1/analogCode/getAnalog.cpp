/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
#include <fstream>
#include <poll.h>

using namespace std;

int main() {
  const int NUM_CYCLES = 8192;
  const double ONE_MIL = 1000000.0;
  
  double waveform[NUM_CYCLES];
  double FFT[NUM_CYCLES];
  double aIn;
  timeval startTime, endTime, runTime;
  double avgSec;
  char strIn [35] = "/sys/devices/ocp.3/helper.15/AIN0";
//  char str2In [35] = "/sys/devices/ocp.3/helper.15/AIN1";
//  char str3In [35] = "/sys/devices/ocp.3/helper.15/AIN2";
//  char str4In [35] = "/sys/devices/ocp.3/helper.15/AIN3";
  char FFTout [35] = "/root/code/str1/output.txt";
  
  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << strIn << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(strIn, O_RDONLY);
  
  cout << "\nEntering infinite loop..." << endl;
  
  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;

  gettimeofday(&startTime, NULL);

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

    poll(&strFile, 1, -1);
    aIn = getAnalog(1, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

    waveform[i] = aIn;

//    usleep(680);
    
    
//    heart();

//    aIn2 = getAnalog(2, str2In);
    
//    sleep(1);

//    heart();
    
//    aIn3 = getAnalog(3, str3In);
    
//    sleep(1);

//    heart();
    
//    aIn4 = getAnalog(4, str4In);
    
//    sleep(1);
    
  }
  
  gettimeofday(&endTime, NULL);
  timersub(&endTime,&startTime,&runTime);
  avgSec = (runTime.tv_sec + runTime.tv_usec / ONE_MIL) / NUM_CYCLES;
  cout << "Total runtime is: " << runTime.tv_sec + runTime.tv_usec / 
          ONE_MIL << endl;
  cout << "Average sample time is: " << avgSec << endl;
  close(strHandle);
  cout << "Size of waveform: " << sizeof(waveform) / 8 << endl;
//  getFFT(fftPlan,waveform,FFT);
  fftw_plan fftPlan = fftw_plan_r2r_1d(NUM_CYCLES, waveform, FFT, FFTW_R2HC, FFTW_DESTROY_INPUT);
  cout << "Made it here!" << endl;
//  fftw_print_plan(fftPlan);
  fftw_execute(fftPlan);
  //fftw_execute(fftPlan);
  ofstream FFTfile;
  FFTfile.open(FFTout);
  for (int i = 0; i < NUM_CYCLES; i++) {
    FFTfile << FFT[i] << endl;
  }
  FFTfile.close();
  return 0;
}

