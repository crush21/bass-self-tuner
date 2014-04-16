/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

const char * left = "/sys/class/gpio/gpio20";
const char * right = "/sys/class/gpio/gpio7";
const char * up = "/sys/class/gpio/gpio125";
const char * down = "/sys/class/gpio/gpio122";
const char * enter = "/sys/class/gpio/gpio14";
const char * ZERO = "0";
const char * ONE = "1";

int main() {
  clearScreen();
  int stringNum = 1;
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  startScreen(); /*
  int leftFile = open(left, O_RDONLY);
  int rightFile = open(right, O_RDONLY);
  int upFile = open(up, O_RDONLY);
  int downFile = open(down, O_RDONLY);
  int enterFile = open(enter, O_RDONLY); */
  for (int i = 0; i < 4; i++) {
/*    if () {

    } */
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
    writeArrow();
    sleep(1);
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
    writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ONE, ONE);
    writeArrow();
    sleep(1);
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ONE, ONE);
    writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ONE, ONE, ZERO);
    writeArrow();
    sleep(1);
    setDDRAM(ZERO, ZERO, ZERO, ZERO, ONE, ONE, ZERO);
    writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);
    setDDRAM(ZERO, ZERO, ZERO, ONE, ZERO, ZERO, ONE);
    writeArrow();
    sleep(1);
    setDDRAM(ZERO, ZERO, ZERO, ONE, ZERO, ZERO, ONE);
    writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);
    setDDRAM(ZERO, ZERO, ZERO, ONE, ONE, ZERO, ZERO);
    writeArrow();
    sleep(1);
    setDDRAM(ZERO, ZERO, ZERO, ONE, ONE, ZERO, ZERO);
    writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);
  }
}
