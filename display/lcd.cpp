/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

const char left = "/sys/class/gpio/gpio";
const char right = "/sys/class/gpio/gpio";
const char up = "/sys/class/gpio/gpio";
const char down = "/sys/class/gpio/gpio";
const char enter = "/sys/class/gpio/gpio";

int main() {
  clearScreen();
  char * ZERO = "0";
  char * ONE = "1";
  string address;
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  address = "0x0000000";
  startScreen();
  
  while (1) {
    if () {
      
    }
  }
}
