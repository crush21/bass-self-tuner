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
#include <math.h>
#include <fcntl.h>

using namespace std;

const char FWDPATH1 [29] = "/sys/class/gpio/gpio66/value"; // P8 Pin 7
const char REVPATH1 [29] = "/sys/class/gpio/gpio69/value"; // P8 Pin 9
const char FWDPATH2 [29] = "/sys/class/gpio/gpio67/value"; // P8 Pin 8
const char REVPATH2 [29] = "/sys/class/gpio/gpio68/value"; // P8 Pin 10
const char FWDPATH3 [29] = "/sys/class/gpio/gpio23/value"; // P8 Pin 13
const char REVPATH3 [29] = "/sys/class/gpio/gpio47/value"; // P8 Pin 15
const char FWDPATH4 [29] = "/sys/class/gpio/gpio26/value"; // P8 Pin 14
const char REVPATH4 [29] = "/sys/class/gpio/gpio46/value"; // P8 Pin 16
const char * START = "1";
const char * STOP = "0";

const int STRING1 = 0;
const int STRING2 = 1;
const int STRING3 = 2;
const int STRING4 = 3;
const double RES = 0.25; // Encoder resolution

void motorStart(const char * file) {
  int handle = open(file, O_WRONLY);
  write(handle, START, 1);
//  perror("Result");
  close(handle);
}

void motorStop(const char * file) {
  int handle = open(file, O_WRONLY);
  write(handle, STOP, 1);
//  perror("Result");
  close(handle);
}


double motorTune(double freqDiff, const int stringNum) {	// speed of motor changes if it is up or down, equation for string changes between strings. , char note
  double turns = 0.0;

  if(stringNum == 3){
      turns = (freqDiff)/13;
  } else if (stringNum == 2){
      turns = (freqDiff)/13;
  } else if (stringNum == 1){
      turns = (freqDiff)/13;
  } else if (stringNum == 0){
      turns = (freqDiff)/13;
  }
  if(turns == 0){
    perror("In tune!");
  }

  return turns;

}

void turnMotor(const int stringNum, double turns){

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

  char ReadValue1 [2];
  char LastRead [2];
  char ReadValue2;
  int counter = 0;
  timespec startTime, lastTime;
  double debounceTime = 0.025;

  int ticks = turns / RES;
  double timeTicks = fabs(turns) / RES;
  double overTicks = fabs(timeTicks) - abs(ticks);
  long double times [abs(ticks)];
  long double runTime;
  long double avgTime = 0;
  long double turnTime;
  long unsigned lastnSec;
  long unsigned lastSec;
  long unsigned startnSec;
  long unsigned startSec;

  read(Handle, LastRead, 1);
  lseek(Handle, 0, SEEK_SET);
  read(Handle, ReadValue1, 1);
  lseek(Handle, 0, SEEK_SET);
  ReadValue2 = ReadValue1[0];

  if (turns > 0) {
    motorStart(FWDPATH1);
    cout << "motor forward" << endl;
  } else if (turns < 0) {
    ticks--;
    motorStart(REVPATH1);
    cout << "motor backward" << endl;
  }
  
  cout << "Turns: " << turns << endl;

  clock_gettime(CLOCK_MONOTONIC_RAW,&lastTime);

  if (abs(ticks) >= 1) {
    while (counter != abs(ticks)) {
      read(Handle, ReadValue1, 1);
      lseek(Handle, 0, SEEK_SET);
      clock_gettime(CLOCK_MONOTONIC_RAW,&startTime);

      if ( ReadValue1[0] != ReadValue2){
//      cout << ReadValue1[0] << " " << ReadValue2 << endl;
        startSec = startTime.tv_sec;
        startnSec = startTime.tv_nsec;
        lastSec = lastTime.tv_sec;
        lastnSec = lastTime.tv_nsec;
        long double nTime = (startnSec - lastnSec);
        cout << "nTime: " << nTime << endl;
        long double sTime = (startSec - lastSec);
        cout << "startTime: " << startSec << endl << "lastTime: " << lastSec << endl;
        cout << "sTime: " << sTime << endl;
        runTime = sTime + nTime/1000000000.0;
        cout << "runTime: " << runTime << endl;
      
        if(runTime > debounceTime){
          if (ReadValue1[0] != LastRead[0]) {
            if (turns > 0) {
              motorStart(REVPATH1);
              usleep(300000);
              motorStop(REVPATH1);
            } else if (turns < 0) {
              motorStart(FWDPATH1);
              usleep(300000);
              motorStop(FWDPATH1);
            }
            clock_gettime(CLOCK_MONOTONIC_RAW,&lastTime);
            counter++;
            cout << "counter: " << counter << endl;
            times[counter - 1] = runTime;
            cout << times[counter - 1] << endl;
          }
        }
      }
      ReadValue2 = ReadValue1[0];
    }
  }

 //   cout << "turning off motor" << endl;
  if (turns > 0) {
    motorStart(REVPATH1);
    usleep(300000);
    motorStop(REVPATH1);
    motorStop(FWDPATH1);
  } else if (turns < 0) {
    motorStart(FWDPATH1);
    usleep(300000);
    motorStop(FWDPATH1);
    motorStop(REVPATH1);
  }

  if (overTicks > 0) {
    if (ticks > 0) {
      for (int i = 0; i < ticks; i++) {
        avgTime += times[i];
      }
      avgTime = (avgTime / ticks) * 1000000;
      turnTime = overTicks * avgTime;
      cout << overTicks << " " << avgTime << " " <<  turnTime << endl;
      motorStart(FWDPATH1);
      usleep(turnTime);
      motorStart(REVPATH1);
      usleep(300000);
      motorStop(REVPATH1);
      motorStop(FWDPATH1);
    } else {
      for (int i = 0; i < abs(ticks); i++) {
        avgTime += times[i];
      }
      avgTime = (avgTime / abs(ticks)) * 1000000;
      turnTime = overTicks * avgTime;
      cout << overTicks << " " << avgTime << " " <<  turnTime << endl;
      motorStart(REVPATH1);
      usleep(turnTime);
      motorStart(FWDPATH1);
      usleep(300000);
      motorStop(FWDPATH1);
      motorStop(REVPATH1);
    }
  }
}

