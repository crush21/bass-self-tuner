/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan. Some information from
 * https://learnbuildshare.wordpress.com/2013/05/19/beaglebone-black-controlling-user-leds-using-c/
 */

#include "analogFunc.h"
#include <poll.h>

using namespace std;

int main() {
  
  double waveform[512];
  double *FFT = NULL;
  fftw_plan fftPlan;
  double aIn;
  timeval startTime, endTime, runTime;
  double avgSec;
  char str1In [35] = "/sys/devices/ocp.2/helper.14/AIN0";
//  char str2In [35] = "/sys/devices/ocp.2/helper.14/AIN1";
//  char str3In [35] = "/sys/devices/ocp.2/helper.14/AIN2";
//  char str4In [35] = "/sys/devices/ocp.2/helper.14/AIN3";
  
  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << str1In << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(str1In, O_RDONLY);
  
  cout << "\nEntering infinite loop..." << endl;

  gettimeofday(&startTime, NULL);
  
  for (int i = 0; i < 512; i++) {

//    heart();

    pollfd strFile;
    strFile.fd = strHandle;
    strFile.events = POLLIN;
    strFile.revents = POLLIN;
    poll(&strFile, 1, 0);
    aIn = getAnalog(2, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

    usleep(680);

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
  avgSec = (runTime.tv_sec + runTime.tv_usec / 1000000.0) / 512.0;
  cout << "Total runtime is: " << runTime.tv_sec + runTime.tv_usec / 
          1000000.0 << endl;
  cout << "Average sample time is: " << avgSec << endl;
  close(strHandle);
  getFFT(fftPlan,waveform,FFT);
  fftw_execute(fftPlan);
  for (double * i = FFT; i != NULL; *(i+1)) {
    cout << i << endl;
  }
  return 0;
}
