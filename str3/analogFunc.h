/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Functions to notify user of "life" and to get
 * an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

unsigned getAnalog(unsigned stringNum, int strHandle) {
  char analogBuffer [5];
  unsigned aVal;
  read(strHandle, analogBuffer, 4);
//  perror("\nRead result");
//  errno = 0;
  analogBuffer[4] = '\0';
  aVal = atoi(analogBuffer);
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
    fread(onOff, sizeof(char), 1, LEDHandle);
    isOn = atoi(onOff);
    if (isOn == 0) {
      fwrite("1", sizeof(char), 1, LEDHandle);
    } else {
      fwrite("0", sizeof(char), 1, LEDHandle);
    }
    fclose(LEDHandle);
  }
}
