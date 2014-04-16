/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

const char * ZERO = "0";
const char * ONE = "1";

int main() {
  int leftFile = open(leftData, O_RDONLY);
/*  int rightFile = open(rightData, O_RDONLY);
  int upFile = open(upData, O_RDONLY);
  int downFile = open(downData, O_RDONLY);
  int enterFile = open(enterData, O_RDONLY); */
  int stringNum = 1;
  char leftPush [1];
/*  char rightPush [1];
  char upPush [1];
  char downPush [1];
  char enterPush [1]; */

  clearScreen();
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  startScreen();
  int i = 0;
  bool isOn = false;
  while (i < 20) {
    read(leftFile, leftPush, 1);
    if ((leftPush[0] == '1') && (!isOn)) {
      cout << "In the if!" << endl;
      stringNum = moveLeft(stringNum);
      isOn = true;
    }
    lseek(leftFile, SEEK_SET, 0);
    if ((leftPush[0] == '0') && (isOn)) {
      i++;
      isOn = false;
    }
  }
  close(leftFile);
}
