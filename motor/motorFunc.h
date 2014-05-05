/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Functions that control the motors.
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Chris Diemer and Cheyn Rushing
 */

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

using namespace std;

const char FWDPATH1 [29] = "/sys/class/gpio/gpio69/value"; // P8 Pin 7
const char REVPATH1 [29] = "/sys/class/gpio/gpio66/value"; // P8 Pin 9
const char FWDPATH2 [29] = "/sys/class/gpio/gpio67/value"; // P8 Pin 8
const char REVPATH2 [29] = "/sys/class/gpio/gpio68/value"; // P8 Pin 10
const char FWDPATH3 [29] = "/sys/class/gpio/gpio23/value"; // P8 Pin 13
const char REVPATH3 [29] = "/sys/class/gpio/gpio47/value"; // P8 Pin 15
const char FWDPATH4 [29] = "/sys/class/gpio/gpio26/value"; // P8 Pin 14
const char REVPATH4 [29] = "/sys/class/gpio/gpio46/value"; // P8 Pin 16

const int STRING1 = 0;
const int STRING2 = 1;
const int STRING3 = 2;
const int STRING4 = 3;
const double RES = 0.25; // Encoder resolution

void motorStart(const char * file) {
  const char * start = "1";
  int handle = open(file, O_WRONLY);
  write(handle, start, 1);
  perror("Result");
  close(handle);
}

void motorStop(const char * file) {
  const char * stop = "0";
  int handle = open(file, O_WRONLY);
  write(handle, stop, 1);
  perror("Result");
  close(handle);
}


double motorTune(double freqDiff, const int stringNum) {	// speed of motor changes if it is up or down, equation for string changes between strings. , char note
  double turns = 0.0;

  if(stringNum == 3){
    if (freqDiff < 0) {
      turns = (freqDiff + 1.3595)/13.076;
    } else {
      turns = (freqDiff - 1.3595)/13.076;				//an oversimplified linear equation representing G. Better equation to be created once FETs arrive.
    }
  } else if (stringNum == 2){
      turns = (freqDiff)/13.0;
  } else if (stringNum == 1){
    if (freqDiff < 0) {
      turns = (freqDiff + 1)/13.0;
    } else {
      turns = (freqDiff - 1)/13.0;
    }
  } else if (stringNum == 0){
    if (freqDiff < 0) {
      turns = (freqDiff + 1)/13.0;
    } else {
      turns = (freqDiff - 1)/13.0;
    }
  }
  if(turns == 0){
    perror("In tune!");
  }

  return turns;

}

void encoder(const int stringNum, double turns){

  const char ENCODER1 [29] = "/sys/class/gpio/gpio87/value";
  const char ENCODER2 [29] = "/sys/class/gpio/gpio89/value";
  const char ENCODER3 [29] = "/sys/class/gpio/gpio10/value";
  const char ENCODER4 [29] = "/sys/class/gpio/gpio11/value";
  int Handle;

  if (stringNum == 0) {
    Handle = open(ENCODER1, O_RDONLY);
  } else if (stringNum == 1) {
    Handle = open(ENCODER2, O_RDONLY);
  } else if (stringNum == 2) {
    Handle = open(ENCODER3, O_RDONLY);
  } else if (stringNum == 3) {
    Handle = open(ENCODER4, O_RDONLY);
  } else {
    cout << "Invalid string" << endl;
    exit(0);
  }

  bool firstLoop = true;
  char ReadValue1 [2];
  char LastRead [2];
  char ReadValue2;
  int counter = 0;
  timespec startTime, lastTime;
  double runTime;
  double debounceTime = .10;
  lastTime.tv_sec = 0;
  lastTime.tv_nsec = 0;

  ReadValue2 = ReadValue1[0];
  read(Handle, LastRead, 1);
  lseek(Handle, 0, SEEK_SET);

  int ticks = turns / RES;  // 4 is the number of switches on the head of the drill
  double timeTicks = turns / RES;
  double overTicks = timeTicks - ticks;

  while (counter != ticks) {
    read(Handle, ReadValue1, 1);
    lseek(Handle, 0, SEEK_SET);
    clock_gettime(CLOCK_MONOTONIC,&startTime);

    if (ReadValue1[0] != ReadValue2) {
      double nTime = (startTime.tv_nsec - lastTime.tv_nsec);
      double sTime = (startTime.tv_sec - lastTime.tv_sec);
      runTime = sTime + nTime/1000000000.0;
      cout << "runTime: " << runTime << endl;

      if (runTime > debounceTime) {
        if (!firstLoop) {
          clock_gettime(CLOCK_MONOTONIC,&lastTime);
          counter++;
          cout << "counter: " << counter << endl;
          ReadValue2 = ReadValue1[0];
        } else {
          firstLoop = false;
        }
      }
    }
    ReadValue2 = ReadValue1[0];
  }

}
