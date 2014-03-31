/* Written by Cheyn Rushing
 * Defines functions used on the LCD screen,
 * using standard HD44780 instruction set.
 */

#include <iostream>
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
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}

void setDDRAM(char* array) {
  int handle = open(RS, O_WRONLY);
  write(handle, OFF, 1);
  close(handle);
  handle = open(DATA7, O_WRONLY);
  write(handle, ON, 1);
  close(handle);
  handle = open(DATA6, O_WRONLY);
  write(handle, &array[6], 1);
  close(handle);
  handle = open(DATA5, O_WRONLY);
  write(handle, &array[5], 1);
  close(handle);
  handle = open(DATA4, O_WRONLY);
  write(handle, &array[4], 1);
  close(handle);
  handle = open(DATA3, O_WRONLY);
  write(handle, &array[3], 1);
  close(handle);
  handle = open(DATA2, O_WRONLY);
  write(handle, &array[2], 1);
  close(handle);
  handle = open(DATA1, O_WRONLY);
  write(handle, &array[1], 1);
  close(handle);
  handle = open(DATA0, O_WRONLY);
  write(handle, &array[0], 1);
  close(handle);
  handle = open(CLK, O_WRONLY);
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}

void getCharArray(char* charArray, char* address, int arraySize) {
  char char0 = address[0];
  char char1 = address[1];
  cout << "getCharArray..." << endl;
  for (int i = 0; i < arraySize; i++) {
    cout << "In the for loop!" << endl;
    if (i > 3) {
      cout << "In the greater if!" << endl;
      charArray[i] = char1 % 2;
      cout << "Bit " << i << ": " << charArray[i] << endl;
      char1 = char1 / 2;
    } else {
      cout << "In the lesser if!" << endl;
      charArray[i] = char0 % 2;
      cout << "Bit " << i << ": " << charArray[i] << endl;
      char0 = char0 / 2;
    }
  }
}

void writeChar(char * character, char * address) {
  char dataBits[8];
  getCharArray(dataBits, character, 8);
//  char * dB7 = &dataBits[7];
//  char * dB6 = &dataBits[6];
//  char * dB5 = &dataBits[5];
//  char * dB4 = &dataBits[4];
//  char * dB3 = &dataBits[3];
//  char * dB2 = &dataBits[2];
//  char * dB1 = &dataBits[1];
//  char * dB0 = &dataBits[0];
  for (int i = 7; i >= 0; i--) {
    cout << "Bit " << i << ": " << dataBits[i] << endl;
  }
  setDDRAM(address);
  int handle = open(RS, O_WRONLY);
  write(handle, ON, 1);
  close(handle);
  handle = open(DATA7, O_WRONLY);
  write(handle, dataBits[7], 1);
//  write(handle, dB7, 1);
  close(handle);
  handle = open(DATA6, O_WRONLY);
  write(handle, dataBits[6], 1);
//  write(handle, dB6, 1);
  close(handle);
  handle = open(DATA5, O_WRONLY);
  write(handle, dataBits[5], 1);
//  write(handle, dB5, 1);
  close(handle);
  handle = open(DATA4, O_WRONLY);
  write(handle, dataBits[4], 1);
//  write(handle, dB4, 1);
  close(handle);
  handle = open(DATA3, O_WRONLY);
  write(handle, dataBits[3], 1);
//  write(handle, dB3, 1);
  close(handle);
  handle = open(DATA2, O_WRONLY);
  write(handle, dataBits[2], 1);
//  write(handle, dB2, 1);
  close(handle);
  handle = open(DATA1, O_WRONLY);
  write(handle, dataBits[1], 1);
//  write(handle, dB1, 1);
  close(handle);
  handle = open(DATA0, O_WRONLY);
  write(handle, dataBits[0], 1);
//  write(handle, dB0, 1);
  close(handle);
  handle = open(CLK, O_WRONLY);
  write(handle, OFF, 1);
  lseek(handle, 0, SEEK_SET);
  write(handle, ON, 1);
  close(handle);
}
