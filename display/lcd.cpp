/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

const char * ZERO = "0";
const char * ONE = "1";

int main() {
  int leftFile = open(leftData, O_RDONLY);
  int rightFile = open(rightData, O_RDONLY);
/*  int upFile = open(upData, O_RDONLY);
  int downFile = open(downData, O_RDONLY);
  int enterFile = open(enterData, O_RDONLY); */
  int stringNum = 0;
/*  int string1 = 0; // Holds "note" of E string
  int string2 = 0; // Holds "note" of A string
  int string3 = 0; // Holds "note" of D string
  int string4 = 0; // Holds "note" of G string */
  char leftPush [1];
  char rightPush [1];
/*  char upPush [1];
  char downPush [1];
  char enterPush [1]; */

  clearScreen();
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  startScreen();
  int i = 0;
  bool isOn = false;
  while (i < 40) {
    read(leftFile, leftPush, 1);
    read(rightFile, rightPush, 1);
    if (!isOn) {
//      std::cout << "Not on!" << std::endl;
      if (leftPush[0] == '1') {
//        std::cout << "Left push!" << std::endl;
        stringNum = moveLeft(stringNum);
        std::cout << "String num after left is: " << stringNum << std::endl;
        isOn = true;
      } else if (rightPush[0] == '1') {
//        std::cout << "Right push!" << std::endl;
        stringNum = moveRight(stringNum);
        std::cout << "String num after right is: " << stringNum << std::endl;
        isOn = true;
      }
    }
    lseek(leftFile, SEEK_SET, 0);
    lseek(rightFile, SEEK_SET, 0);
    if (isOn) {
//      std::cout << "Is on!" << std::endl;
      if ((leftPush[0] == '0') && (rightPush[0] == '0')) {
//        std::cout << "All off!" << std::endl;
        i++;
        isOn = false;
      }
    }
  }
  close(leftFile);
  close(rightFile);
}
