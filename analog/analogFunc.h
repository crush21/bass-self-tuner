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
#include <sys/wait.h>
#include <fftw3.h>

const int STRING1 = 0;
const int STRING2 = 1;
const int STRING3 = 2;
const int STRING4 = 3;

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
/*  std::cout << "String " << stringNum << " Voltage Reading: "
       << aVal << std::endl; */
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
double getFrequency(double *FFT, int size, int lowLimit, int highLimit, const double& sampleFreq) {
  double * max = FFT;
  int index = 0;
  double frequency;
  for (int i = lowLimit; i < highLimit; i++) {
//    std::cout << *(FFT + i) << std::endl;
//    sleep(2);
    if (*(FFT + i) > *max) {
      max = FFT + i;
      index = i;
    }
  }
  std::cout << "Highest index is: " << index << std::endl;
  frequency = (index + 1) * sampleFreq / size;
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
  return 1200 * log2(idealFreq / currFreq);
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

int callMotor(const int stringNum, double freqDiff) {
  pid_t childProcess;
  pid_t waiting;
  int child_status;
  const char * CMD1 = "/root/code/runMotor1";
  const char * CMD2 = "/root/code/runMotor2";
  const char * CMD3 = "/root/code/runMotor3";
  const char * CMD4 = "/root/code/runMotor4";
  char freqStr [8];

  sprintf(freqStr, "%f", freqDiff);
  if (stringNum == 0) {
    childProcess = vfork();
    if (childProcess == 0) {
      execlp(CMD1, "/root/code", reinterpret_cast<const char *>(freqStr), (char*)NULL);
      std::cout << "Child process!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status);
      } while (waiting != childProcess);
    }
  } else if (stringNum == 1) {
    childProcess = vfork();
    if (childProcess == 0) {
      execlp(CMD2, "/root/code", reinterpret_cast<const char *>(freqStr), (char*)NULL);
      std::cout << "Child process!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status);
      } while (waiting != childProcess);
    }
  } else if (stringNum == 2) {
    childProcess = vfork();
    if (childProcess == 0) {
      execlp(CMD3, "/root/code", reinterpret_cast<const char *>(freqStr), (char*)NULL);
      std::cout << "Child process!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status);
      } while (waiting != childProcess);
    }
  } else if (stringNum == 3) {
    childProcess = vfork();
    if (childProcess == 0) {
      execlp(CMD4, "/root/code", reinterpret_cast<const char *>(freqStr), (char*)NULL);
      std::cout << "Child process!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status);
      } while (waiting != childProcess);
    }
  }
  return 0;
}
