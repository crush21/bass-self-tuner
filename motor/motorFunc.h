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

double motorTune(double freqDiff, char note){				//speed of motor changes if it is up or down, equation for string changes between strings. , char note
  double speed = 1; 							//speed of motor: Turns/Sec
  double turns = 0;

  if('G'== note){
	turns = (freqDiff - 1.3595)/13.076;				//an oversimplified linear equation representing G. Better equation to be created once FETs arrive.
	}
  if('D' == note){
	turns = (freqDiff - 1)/13;
  	}
  if('A' == note){
	turns = (freqDiff - 1)/13;
  	}
  if('E' == note){
	turns = (freqDiff - 1)/13;
  	}
  if(turns == 0){
	perror("Error!");
  	} 
  double time = turns/speed;
  return time;

}

