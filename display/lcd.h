/* Written by Cheyn Rushing
 * Defines functions used on the LCD screen,
 * using standard HD44780 instruction set.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
//#include <cmath>
#include <fcntl.h>

using namespace std;

const char RS [29] = "/sys/class/gpio/gpio2/value";
const char CLK [29] = "/sys/class/gpio/gpio3/value";
const char DATA7 [29] = "/sys/class/gpio/gpio14/value";
const char DATA6 [29] = "/sys/class/gpio/gpio49/value";
const char DATA5 [29] = "/sys/class/gpio/gpio51/value";
const char DATA4 [29] = "/sys/class/gpio/gpio48/value";
const char DATA3 [29] = "/sys/class/gpio/gpio15/value";
const char DATA2 [29] = "/sys/class/gpio/gpio31/value";
const char DATA1 [29] = "/sys/class/gpio/gpio60/value";
const char DATA0 [29] = "/sys/class/gpio/gpio30/value";
const char * ON = "1";
const char * OFF = "0";

void dispCtrl(char* dispOn, char* cursorOn, char* blinkOn) {
  if ((atoi(dispOn) > 1) || (atoi(cursorOn) > 1) || (atoi(blinkOn) > 1)) {
    cout << "Error: Parameter is greater than 1." << endl;
    return;
  } else {
    int handle = open(RS, O_WRONLY);
    write(handle, OFF, 1);
    close(handle);
    handle = open(DATA7, O_WRONLY);
    write(handle, OFF, 1);
    close(handle);
    handle = open(DATA6, O_WRONLY);
    write(handle, OFF, 1);
    close(handle);
    handle = open(DATA5, O_WRONLY);
    write(handle, OFF, 1);
    close(handle);
    handle = open(DATA4, O_WRONLY);
    write(handle, OFF, 1);
    close(handle);
    handle = open(DATA3, O_WRONLY);
    write(handle, ON, 1);
    close(handle);
//    sprintf(buffer, "%d", dispOn);
    handle = open(DATA2, O_WRONLY);
    write(handle, dispOn, 1);
    close(handle);
//    sprintf(buffer, "%d", cursorOn);
    handle = open(DATA1, O_WRONLY);
    write(handle, cursorOn, 1);
    close(handle);
//    sprintf(buffer, "%d", blinkOn);
    handle = open(DATA0, O_WRONLY);
    write(handle, blinkOn, 1);
    close(handle);
    handle = open(CLK, O_WRONLY);
    write(handle, ON, 1);
    lseek(handle, 0, SEEK_SET);
    write(handle, OFF, 1);
    lseek(handle, 0, SEEK_SET);
    write(handle, ON, 1);
    close(handle);
  }
}

void clearScreen() {
  int handle = open(RS, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA7, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA6, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA5, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA4, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA3, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA2, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA1, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA0, O_WRONLY);
  write(handle, ON, 1);
  close(handle);
  handle = open(CLK, O_WRONLY);
  write(handle, ON, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}

void setDDRAM(char * addr6, char * addr5, char * addr4,
	      char * addr3, char * addr2, char * addr1, char * addr0) {
  int handle = open(RS, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA7, O_WRONLY);
  write(handle, ON, 1);
  close(handle);
  handle = open(DATA6, O_WRONLY);
  write(handle, addr6, 1);
  close(handle);
  handle = open(DATA5, O_WRONLY);
  write(handle, addr5, 1);
  close(handle);
  handle = open(DATA4, O_WRONLY);
  write(handle, addr4, 1);
  close(handle);
  handle = open(DATA3, O_WRONLY);
  write(handle, addr3, 1);
  close(handle);
  handle = open(DATA2, O_WRONLY);
  write(handle, addr2, 1);
  close(handle);
  handle = open(DATA1, O_WRONLY);
  write(handle, addr1, 1);
  close(handle);
  handle = open(DATA0, O_WRONLY);
  write(handle, addr0, 1);
  close(handle);
  handle = open(CLK, O_WRONLY);
  write(handle, ON, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}

void writeChar(char * dB7, char * dB6, char * dB5, char * dB4,
	       char * dB3, char * dB2, char * dB1, char * dB0) {
  int handle = open(RS, O_WRONLY);
  write(handle, ON, 1);
  close(handle);
  handle = open(DATA7, O_WRONLY);
  write(handle, dB7, 1);
  close(handle);
  handle = open(DATA6, O_WRONLY);
  write(handle, dB6, 1);
  close(handle);
  handle = open(DATA5, O_WRONLY);
  write(handle, dB5, 1);
  close(handle);
  handle = open(DATA4, O_WRONLY);
  write(handle, dB4, 1);
  close(handle);
  handle = open(DATA3, O_WRONLY);
  write(handle, dB3, 1);
  close(handle);
  handle = open(DATA2, O_WRONLY);
  write(handle, dB2, 1);
  close(handle);
  handle = open(DATA1, O_WRONLY);
  write(handle, dB1, 1);
  close(handle);
  handle = open(DATA0, O_WRONLY);
  write(handle, dB0, 1);
  close(handle);
  handle = open(CLK, O_WRONLY);  
  write(handle, ON, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}

void startScreen() {
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  writeChar(ZERO, ONE, ONE, ONE, ONE, ONE, ONE, ZERO);		// "->"
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ZERO, ONE);	// "E"
  writeChar(ZERO, ONE, ONE, ZERO, ZERO, ZERO, ONE, ZERO);	// "b"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO, ONE);	// "A"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ZERO, ZERO);	// "D"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ONE, ONE);	// "G"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ONE, ONE);	// "G"
  writeChar(ZERO, ONE, ZERO, ZERO, ONE, ONE, ONE, ONE);		// "O"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ONE);	// "!"

  setDDRAM(ONE, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ZERO, ONE);	// "1"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ONE, ZERO);	// "2"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ONE, ONE);	// "3"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ONE, ZERO, ZERO);	// "4"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
}
