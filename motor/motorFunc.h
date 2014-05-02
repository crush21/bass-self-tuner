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
    turns = (freqDiff - 1.3595)/13.076;				//an oversimplified linear equation representing G. Better equation to be created once FETs arrive.
  } else if (stringNum == 2){
    turns = (freqDiff)/13.0;
  } else if (stringNum == 1){
    turns = (freqDiff)/13.0;
//    turns = (freqDiff - 1)/13.0;
  } else if (stringNum == 0){
    turns = (freqDiff)/13.0;
//    turns = (freqDiff - 1)/13.0;
  }
  if(turns == 0){
    perror("In tune!");
  } 

  return turns;

}

int encoder(char note, double turns){

  const char INPIN [29] = "/sys/class/gpio/gpio87/value";

/*
if(note == 'D'){
	const char INPIN [29] = "/sys/class/gpio/gpio87/value";
} else{
	cout << "Invalid string" << endl;
}
*/

  int Handle = open(INPIN, O_RDONLY);

  bool firstLoop = true;
  char ReadValue1 [2];
  char LastRead [2];
  char ReadValue2;
  int counter = 0;
  timespec startTime, lastTime;
  double runTime;
  double debounceTime = .25;
  lastTime.tv_sec = 0;
  lastTime.tv_nsec = 0;
  
  ReadValue2 = ReadValue1[0];
  read(Handle, LastRead, 1);
  lseek(Handle, 0, SEEK_SET);

  int ticks = turns / RES;  //2 is the number of breaks on the head of the drill

  while (counter != ticks) {
    read(Handle, ReadValue1, 1);
    lseek(Handle, 0, SEEK_SET);
    clock_gettime(CLOCK_MONOTONIC,&startTime);

    if (ReadValue1[0] != ReadValue2) {
      double nTime = (startTime.tv_nsec - lastTime.tv_nsec);
      double sTime = (startTime.tv_sec - lastTime.tv_sec);
      runTime = sTime + nTime/1000000000.0;
      //cout << "runTime: " << runTime << endl;

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

  return 0;
}
