/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Functions that control the motors.
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

using namespace std;

void motorControl(char * file, unsigned time) {
  char * start = "1";
  char * stop = "0";
  int handle = open(file, O_WRONLY);
  write(handle, start, 1);
  perror("Result");
  errno = 0;
  usleep(time);
  write(handle, stop, 1);
  close(handle);
}

int motorTune(double freqDiff, char note){				//speed of motor changes if it is up or down, equation for string changes between strings. , char note
  int turns;

  if('G'== note){
	turns = (freqDiff - 1.3595)/13.076;				//an oversimplified linear equation representing G. Better equation to be created once FETs arrive.
	}
  if('D' == note){
	turns = (freqDiff)/13;
  	}
  if('A' == note){
	turns = (freqDiff - 1)/13;
  	}
  if('E' == note){
	turns = (freqDiff - 1)/13;
  	}
  if(turns == 0){
	perror("In tune!");
  	} 

  return turns;

}

int encoder(char note, int turns){

if(note == 'D'){
	const char INPIN [29] = "/sys/class/gpio/gpio87/value";
} else{
	cout << "Invalid string" << endl;
}

int Handle = open(INPIN, O_RDONLY);

char ReadValue1 [2];
char LastRead [2];
char ReadValue2;
int counter = 0;
timespec startTime, lastTime;
double runTime;
double debounceTime = .3;
lastTime.tv_sec = 0;
lastTime.tv_nsec = 0;

read(Handle, LastRead, 1);
lseek(Handle, 0, SEEK_SET);

int ticks = turns * 2;  //2 is the number of breaks on the head of the drill

while(counter != ticks){
ReadValue2 = ReadValue1[0];
read(Handle, ReadValue1, 1);
lseek(Handle, 0, SEEK_SET);
clock_gettime(CLOCK_MONOTONIC,&startTime);

if ( ReadValue1[0] != ReadValue2){
double nTime = (startTime.tv_nsec - lastTime.tv_nsec);
double sTime = (startTime.tv_sec - lastTime.tv_sec);
runTime = sTime + nTime/1000000000.0;
//cout << "runTime: " << runTime << endl;

	if(runTime > debounceTime){
		if(ReadValue1[0] != LastRead[0]){
		clock_gettime(CLOCK_MONOTONIC,&lastTime);
		counter++;
	//	cout << "counter: " << counter << endl;
		}
	}
}


}

return 0;
}
