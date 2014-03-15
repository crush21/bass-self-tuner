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
  sleep(time);
  write(handle, stop, 1);
  close(handle);
}
