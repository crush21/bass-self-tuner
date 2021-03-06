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

const char FWDPATH1 [29] = "/sys/class/gpio/gpio9/value"; // P8 Pin 7
const char REVPATH1 [29] = "/sys/class/gpio/gpio81/value"; // P8 Pin 9
const char FWDPATH2 [29] = "/sys/class/gpio/gpio8/value"; // P8 Pin 8
const char REVPATH2 [29] = "/sys/class/gpio/gpio80/value"; // P8 Pin 10
const char FWDPATH3 [29] = "/sys/class/gpio/gpio78/value"; // P8 Pin 13
const char REVPATH3 [29] = "/sys/class/gpio/gpio79/value"; // P8 Pin 15
const char FWDPATH4 [29] = "/sys/class/gpio/gpio76/value"; // P8 Pin 14
const char REVPATH4 [29] = "/sys/class/gpio/gpio77/value"; // P8 Pin 16
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
      turns = (freqDiff)/15.51;
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
  int Handle, fwdHandle, revHandle;
  double QUARTERTIME;

  if (stringNum == 0) {
    QUARTERTIME = 0.069 * 1000000;
    Handle = open(ENCODER1, O_RDONLY);
    fwdHandle = open(FWDPATH1, O_WRONLY);
    revHandle = open(REVPATH1, O_WRONLY);
  } else if (stringNum == 1) {
    QUARTERTIME = 0.069 * 1000000;
    Handle = open(ENCODER2, O_RDONLY);
    fwdHandle = open(FWDPATH2, O_WRONLY);
    revHandle = open(REVPATH2, O_WRONLY);
  } else if (stringNum == 2) {
    QUARTERTIME = 0.069 * 1000000;
    Handle = open(ENCODER3, O_RDONLY);
    fwdHandle = open(FWDPATH3, O_WRONLY);
    revHandle = open(REVPATH3, O_WRONLY);
  } else if (stringNum == 3) {
    QUARTERTIME = 0.08 * 1000000;
    Handle = open(ENCODER4, O_RDONLY);
    fwdHandle = open(FWDPATH4, O_WRONLY);
    revHandle = open(REVPATH4, O_WRONLY);
  } else {
    cout << "Invalid string" << endl;
    exit(0);
  }

  char ReadValue1 [2];
  char LastRead [2];
  char ReadValue2;
  int counter = 0;
  timespec startTime, lastTime;
  double debounceTime = 0.03;

  int ticks = turns / RES;
  double timeTicks = fabs(turns) / RES;
  cout << "Ticks: " << ticks << endl;
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
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    cout << "motor forward" << endl;
  } else if (turns < 0) {
    ticks--;
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
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
              write(revHandle, START, 1);
              lseek(revHandle, SEEK_SET, 0);
              usleep(300000);
              write(revHandle, STOP, 1);
              lseek(fwdHandle, SEEK_SET, 0);
            } else if (turns < 0) {
              write(fwdHandle, START, 1);
              lseek(fwdHandle, SEEK_SET, 0);
              usleep(300000);
              write(fwdHandle, STOP, 1);
              lseek(fwdHandle, SEEK_SET, 0);
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
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(300000);
    write(revHandle, STOP, 1);
    write(fwdHandle, STOP, 1);
    lseek(revHandle, SEEK_SET, 0);
    lseek(fwdHandle, SEEK_SET, 0);
  } else if (turns < 0) {
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(300000);
    write(fwdHandle, STOP, 1);
    write(revHandle, STOP, 1);
    lseek(revHandle, SEEK_SET, 0);
    lseek(fwdHandle, SEEK_SET, 0);
  }

  if (turns > 0) {
    turnTime = overTicks * QUARTERTIME;
    cout << overTicks << " " << avgTime << " " <<  turnTime << endl;
    if (turnTime < 30000) {
      turnTime += 30000;
    }
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(turnTime);    
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(300000);
    write(revHandle, STOP, 1);
    write(fwdHandle, STOP, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    lseek(revHandle, SEEK_SET, 0);
  } else if (turns < 0) {
    turnTime = overTicks * QUARTERTIME;
    if (turnTime < 30000) {
      turnTime += 30000;
    }
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(turnTime);
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(300000);
    write(fwdHandle, STOP, 1);
    write(revHandle, STOP, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    lseek(revHandle, SEEK_SET, 0);
  }
}

void turnMotor2(double turns){
  const double QUARTERTIME = 0.069 * 1000000;
  int fwdHandle, revHandle;

  fwdHandle = open(FWDPATH2, O_WRONLY);
  revHandle = open(REVPATH2, O_WRONLY);

  double turnTime;
  int counter = 0;

  int ticks = turns / RES;
  double timeTicks = fabs(turns) / RES;
  cout << "Ticks: " << ticks << endl;
  double overTicks = fabs(timeTicks) - abs(ticks);

  if (turns > 0) {
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    cout << "motor forward" << endl;
  } else if (turns < 0) {
    ticks--;
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    cout << "motor backward" << endl;
  }
  
  cout << "Turns: " << turns << endl;

  if (abs(ticks) >= 1) {
    while (counter != abs(ticks)) {
      usleep(QUARTERTIME);
      if (turns > 0) {
        write(revHandle, START, 1);
        lseek(revHandle, SEEK_SET, 0);
        usleep(300000);
        write(revHandle, STOP, 1);
        lseek(fwdHandle, SEEK_SET, 0);
      } else if (turns < 0) {
        write(fwdHandle, START, 1);
        lseek(fwdHandle, SEEK_SET, 0);
        usleep(300000);
        write(fwdHandle, STOP, 1);
        lseek(fwdHandle, SEEK_SET, 0);
      }
      counter++;
      cout << "counter: " << counter << endl;
    }
  }

 //   cout << "turning off motor" << endl;
  if (turns > 0) {
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(300000);
    write(revHandle, STOP, 1);
    write(fwdHandle, STOP, 1);
    lseek(revHandle, SEEK_SET, 0);
    lseek(fwdHandle, SEEK_SET, 0);
  } else if (turns < 0) {
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(300000);
    write(fwdHandle, STOP, 1);
    write(revHandle, STOP, 1);
    lseek(revHandle, SEEK_SET, 0);
    lseek(fwdHandle, SEEK_SET, 0);
  }

  if ((turns > 0) && (overTicks != 0)) {
    turnTime = overTicks * QUARTERTIME;
    if (turnTime < 30000) {
      turnTime += 30000;
    }
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(turnTime);
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(300000);
    write(fwdHandle, STOP, 1);
    write(revHandle, STOP, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    lseek(revHandle, SEEK_SET, 0);
  } else if ((turns < 0) && (overTicks != 0)){
    turnTime = overTicks * QUARTERTIME;
    if (turnTime < 20000) {
      turnTime += 20000;
    }
    write(revHandle, START, 1);
    lseek(revHandle, SEEK_SET, 0);
    usleep(turnTime);
    write(fwdHandle, START, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    usleep(300000);
    write(fwdHandle, STOP, 1);
    write(revHandle, STOP, 1);
    lseek(fwdHandle, SEEK_SET, 0);
    lseek(revHandle, SEEK_SET, 0);
  }
}

