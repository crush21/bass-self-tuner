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
  char strIn [35] = "/sys/devices/ocp.3/helper.15/AIN1";
  
  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << strIn << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(strIn, O_RDONLY);
  
  cout << "\nEntering infinite loop..." << endl;

  gettimeofday(&startTime, NULL);
  
  pollfd strFile;
  strFile.fd = strHandle;
  strFile.events = POLLIN;
  strFile.revents = POLLIN;

  for (int i = 0; i < NUM_CYCLES; i++) {

//    heart();

    poll(&strFile, 1, 0);
    aIn = getAnalog(2, strFile.fd);
    lseek(strHandle, 0, SEEK_SET);

    usleep(680);

    waveform[i] = aIn;
    
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
