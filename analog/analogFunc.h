/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Functions to notify user of "life" and to get
 * an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
//#include <errno.h>
#include <sys/time.h>
#include <fcntl.h>
#include <fftw3.h>

/* Gets the analog voltage given by the specified file.
 * Receives:
 *     stringNum, the string being measured.
 *     strHandle, the filehandle to read from.
 * Returns: The analog voltage reading.
 * Restrictions: None.
 */
double getAnalog(unsigned stringNum, int strHandle) {
  char analogBuffer [5];
  double aVal;
  std::stringstream ss;
  read(strHandle, analogBuffer, 4);
  for (int i = 0; i < 4; i++) {
    ss << analogBuffer[i];
  }
  analogBuffer[4] = '\0';
  ss >> aVal;
/*  cout << "String " << stringNum << " Voltage Reading: "
       << aVal << endl; */
  return aVal;
}

/* Adapted from:
 * https://learnbuildshare.wordpress.com/2013/05/19/beaglebone-black-controlling-user-leds-using-c/
 * This is supposed to show that the BeagleBone Black is doing something.
 * Receives: Nothing.
 * Returns: Nothing.
 * Restrictions: None.
 */
void heart() {
  FILE * LEDHandle = NULL;
  char onOff [2];
  int isOn = 0;
  char LEDBrightness [50] = "/sys/class/leds/beaglebone:green:usr0/brightness";
  if((LEDHandle = fopen(LEDBrightness, "r+")) != NULL){
    fread(onOff, sizeof(char), 1, LEDHandle);
    isOn = onOff[0] % 2;
//    isOn = atoi(onOff);
    if (isOn == 0) {
      fwrite("1", sizeof(char), 1, LEDHandle);
    } else {
      fwrite("0", sizeof(char), 1, LEDHandle);
    }
    fclose(LEDHandle);
  }
}

/* Calculates the fundamental frequency from an FFT.
 * Receives:
 *     FFT, the array containing the FFT results.
 *     size, the size of the array.
 *     limit, which limits the for loop.
 *         The reason for this is that guitars sometimes emit higher
 *         amplitudes of frequencies larger than the fundamental.
 *     sampleFreq, the sampling frequency.
 * Returns: The fundamental frequency.
 * Restrictions: None.
 */
double getFrequency(double *FFT, int size, int limit, const double& sampleFreq) {
  double * max = FFT;
  int index = 0;
  double frequency;
  for (int i = 1; i < limit; i++) {
//    std::cout << *(FFT + i) << std::endl;
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


/* Calculates the difference between frequencies in cents.
 * Receives:
 *     currFreq, the frequency measured.
 *     idealFreq, the desired frequency.
 * Returns: The proper frequency.
 * Restrictions: None.
 */
double getCents(double& currFreq, double& idealFreq) {
  return 1200 * log2(currFreq / idealFreq);
}

/* Translates a number into a frequency.
 * Receives: A "noteNumber" which represents a note
 *     between C (~32 Hz) and Bb (~116 Hz) 
 * Returns: The proper frequency.
 * Restrictions: None.
 */
double translateFrequency(int noteNumber) {
/* The low C is the "fourth" note (which is "0" 
 * for this tuning system) when starting with
 * A,, sub-contra-octave as note "one."
 */
  int offset = 4;
  return (pow(pow(2,1/12.0), noteNumber + offset - 49) * 440);
}
