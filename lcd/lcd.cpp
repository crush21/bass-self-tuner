/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

int main() {
  clearScreen();
  char * arrow = "NG";
  char * startAdd = "0000000";
  writeChar(arrow, startAdd);
}
