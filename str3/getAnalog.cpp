/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing, basic syscall information
 * from Phil Fynan. Some information from
 * https://learnbuildshare.wordpress.com/2013/05/19/beaglebone-black-controlling-user-leds-using-c/
 */

#include "analogFunc.h"
#include <poll.h>
#include <sys/time.h>

using namespace std;

int main() {
  
  unsigned aIn1, aIn2, aIn3, aIn4;
  timeval startTime, endTime, runTime;
  double avgSec;
  char str1In [35] = "/sys/devices/ocp.2/helper.14/AIN0";
  char str2In [35] = "/sys/devices/ocp.2/helper.14/AIN1";
  char str3In [35] = "/sys/devices/ocp.2/helper.14/AIN2";
  char str4In [35] = "/sys/devices/ocp.2/helper.14/AIN3";
  
  cout << "\nStarting program to read analog signals.\n" << endl;
  
  cout << str3In << endl;
  
  /* Open a file once before the while loop, to
   * "initialize" the files to update. I do not
   * understand why this is so. A bug in the driver?
   */
  
  int strHandle = open(str3In, O_RDONLY);
  
  cout << "\nEntering infinite loop..." << endl;

  gettimeofday(&startTime, NULL);
  
  for (int i = 0; i < 100000; i++) {

//    heart();

    pollfd strFile;
    strFile.fd = strHandle;
    strFile.events = POLLIN;
    strFile.revents = POLLIN;
    if (poll(&strFile, 1, -1) != 0) {
      aIn1 = getAnalog(2, strFile.fd);
      lseek(strHandle, 0, SEEK_SET);
    }
    usleep(800);

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
  avgSec = (runTime.tv_sec + runTime.tv_usec / 1000000) / 100000.0;
  cout << "Total runtime is: " << runTime.tv_sec + runTime.tv_usec / 
          100000.0 << endl;
  cout << "Average sample time is: " << avgSec << endl;
  close(strHandle);
  return 0;
}
