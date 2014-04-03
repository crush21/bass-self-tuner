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

void setDDRAM(char * addr6, char * addr5, char * addr4, char * addr3, char * addr2, char * addr1, char * addr0) {
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

/*
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
*/

void writeChar(char * dB7, char * dB6, char * dB5, char * dB4, char * dB3, char * dB2, char * dB1, char * dB0) {
/*  char dataBits[8];
  getCharArray(dataBits, character, 8);
  char * dB7 = &dataBits[7];
  char * dB6 = &dataBits[6];
  char * dB5 = &dataBits[5];
  char * dB4 = &dataBits[4];
  char * dB3 = &dataBits[3];
  char * dB2 = &dataBits[2];
  char * dB1 = &dataBits[1];
  char * dB0 = &dataBits[0]; */
/*  for (int i = 7; i >= 0; i--) {
//    cout << "Bit " << i << ": " << *(character + i) << endl;
//    cout << "Bit " << i << ": " << dataBits[i] << endl;
  } */
/*  cout << "Bit 7: " << *dB7 << endl;
  cout << "Bit 6: " << *dB6 << endl;
  cout << "Bit 5: " << *dB5 << endl;
  cout << "Bit 4: " << *dB4 << endl;
  cout << "Bit 3: " << *dB3 << endl;
  cout << "Bit 2: " << *dB2 << endl;
  cout << "Bit 1: " << *dB1 << endl;
  cout << "Bit 0: " << *dB0 << endl; */
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
