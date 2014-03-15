/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan.
 */

#include "analogFunc.h"
#include <poll.h>

using namespace std;

int main() {
  const int NUM_CYCLES = 1000000;
  const double ONE_MIL = 1000000.0;
  
  double waveform[NUM_CYCLES];
  double *FFT = NULL;
  fftw_plan fftPlan;
  double aIn;
  timeval startTime, endTime, runTime;
  double avgSec;
  char str1In [35] = "/sys/devices/ocp.3/helper.15/AIN0";
//  char str2In [35] = "/sys/devices/ocp.3/helper.15/AIN1";
//  char str3In [35] = "/sys/devices/ocp.3/helper.15/AIN2";
//  char str4In [35] = "/sys/devices/ocp.3/helper.15/AIN3";
  
  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << str1In << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(str1In, O_RDONLY);
  
  cout << "\nEntering infinite loop..." << endl;

  gettimeofday(&startTime, NULL);
  
  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

    poll(&strFile, 1, 0);
    aIn = getAnalog(1, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

    usleep(200000);

    waveform[i] = aIn;
    
    
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
  getFFT(fftPlan,waveform,FFT);
  fftw_execute(fftPlan);
  for (double * i = FFT; i != NULL; *(i+1)) {
    cout << i << endl;
  }
  return 0;
}
