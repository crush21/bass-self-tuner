/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Functions to notify user of "life" and to get
 * an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
//#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>
//#include <fftw3.h>
#include <octave/oct.h>
#include <octave/builtin-defun-decls.h>
#include <octave/ov.h>

//using namespace std;

double getAnalog(unsigned stringNum, /* unsigned long * strAddress) {  */ int strHandle) {
  char analogBuffer [5];
  double aVal;
  std::stringstream ss;
/*  for (int i = 0; i < 4; i++) {
    analogBuffer[i] = *(strAddress + i);
  } */
  read(strHandle, analogBuffer, 4);
  for (int i = 0; i < 4; i++) {
    ss << analogBuffer[i];
  }
  analogBuffer[4] = '\0';
  ss >> aVal;
//  aVal = atoi(analogBuffer);
/*  cout << "String " << stringNum << " Voltage Reading: "
       << aVal << endl; */
  return aVal;
}

/* Adapted from:
 * https://learnbuildshare.wordpress.com/2013/05/19/beaglebone-black-controlling-user-leds-using-c/
 */
void heart() {
  FILE * LEDHandle = NULL;
  char onOff [2];
  int isOn = 0;
  char LEDBrightness [50] = "/sys/class/leds/beaglebone:green:usr0/brightness";
  if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
    std::fread(onOff, sizeof(char), 1, LEDHandle);
    isOn = onOff[0] % 2;
//    isOn = std::atoi(onOff);
    if (isOn == 0) {
      std::fwrite("1", sizeof(char), 1, LEDHandle);
    } else {
      std::fwrite("0", sizeof(char), 1, LEDHandle);
    }
    fclose(LEDHandle);
  }
}

double getFrequency(double *FFT, int size, int limit, const double& sampleFreq) {
  double *max = FFT;
  int index = 0;
  double frequency;
  for (int i = 1; i < limit; i++) {
    std::cout << *(FFT + i) << std::endl;
//    sleep(2);
    if (*(FFT + i) > *max) {
      max = FFT + i;
      index = i;
    }
  }
  std::cout << "Highest index is: " << index << std::endl;
  frequency = index * sampleFreq / size;
  return frequency;
}

double getCents(double& currFreq, double& idealFreq) {
  return 1200 * log2(currFreq / idealFreq);
}
