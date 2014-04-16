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

// LCD Data Bit files
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

// LCD Navigation Bit files
const char * leftData = "/sys/class/gpio/gpio20/value";
const char * rightData = "/sys/class/gpio/gpio7/value";
const char * upData = "/sys/class/gpio/gpio125/value";
const char * downData = "/sys/class/gpio/gpio122/value";
const char * enterData = "/sys/class/gpio/gpio14/value";

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

void setDDRAM(const char * addr6, const char * addr5, const char * addr4,
	      const char * addr3, const char * addr2, const char * addr1, const char * addr0) {
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

void writeChar(const char * dB7, const char * dB6, const char * dB5, const char * dB4,
	       const char * dB3, const char * dB2, const char * dB1, const char * dB0) {
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

void writeArrow() {
  writeChar(OFF, ON, ON, ON, ON, ON, ON, OFF);
}

void startScreen() {
  setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
  writeArrow();							// "->"
  writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);	// "E"
  writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);	// "b"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);	// "A"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);	// "D"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);	// "G"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);	// "G"
  writeChar(OFF, ON, OFF, OFF, ON, ON, ON, ON);		// "O"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, ON);	// "!"

  setDDRAM(ON, OFF, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, OFF, ON);	// "1"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, OFF);	// "2"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, ON);	// "3"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, ON, OFF, OFF);	// "4"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
}

/* Called if left pushbutton is pressed during navigation loop.
 * Receives:	 current position.
 * Returns:	 new position, one to the left.
 * Restrictions: max currentPos is 4.
 */
int moveLeft(int currentPos) {
  int curPos = currentPos;
  if (curPos > 4) {
    curPos = 0;
  }
  switch (curPos) {
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeArrow();
      break;
// Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      break;
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeArrow();
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeArrow();
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeArrow();
      break;
// Reset arrow to position 0 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 0;
  }
  return (curPos + 1) % 5;
}
