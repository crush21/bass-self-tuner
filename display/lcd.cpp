/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

const char * ZERO = "0";
const char * ONE = "1";

int main() {
  int stringNum = 0;
  int leftFile = open(leftData, O_RDONLY);
  int rightFile = open(rightData, O_RDONLY);
  int enterFile = open(enterData, O_RDONLY);
  int upFile = open(upData, O_RDONLY);
  int downFile = open(downData, O_RDONLY);
  char leftPush [1];
  char rightPush [1]; 
  char enterPush [1];
  char upPush [1];
  char downPush [1];
/* The following integers represent the strings
 * from lowest to highest. The range for each
 * note is 8 half-steps. The standard note
 * for each string is located at "4."
 * For example, string1 (the "E" string)
 * ranges from C (0) to G (7).
 */
  int string1 = 4; // Holds "note" of E string
  int string2 = 9; // Holds "note" of A string
  int string3 = 14; // Holds "note" of D string
  int string4 = 19; // Holds "note" of G string

  functionSet(ONE, ONE);
  dispCtrl(ONE, ZERO, ZERO);
  entryMode(ONE, ZERO);
  clearScreen();
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  startScreen();
  int i = 0;
  bool isOn = false;
  while (1) {
    read(leftFile, leftPush, 1);
    read(rightFile, rightPush, 1);
    read(enterFile, enterPush, 1);
    read(upFile, upPush, 1);
    read(downFile, downPush, 1);
    if (!isOn) {
//      std::cout << "         " << upPush[0] << std::endl;
//      std::cout << "Not on!" << std::endl;
      if (leftPush[0] == '1') {
//        std::cout << "Left push!" << std::endl;
        stringNum = moveLeft(stringNum);
//        std::cout << "String num after left is: " << stringNum << std::endl;
        isOn = true;
      } else if (rightPush[0] == '1') {
//        std::cout << "Right push!" << std::endl;
        stringNum = moveRight(stringNum);
//        std::cout << "String num after right is: " << stringNum << std::endl;
        isOn = true;
      } else if (enterPush[0] == '1') {
	if (stringNum == 4) {
	  tuningSequence(string1, string2, string3, string4);
	}
        isOn = true;
      } else if (upPush[0] == '0') {
	if (stringNum == 0) {
          string1 = moveUpStr1(string1);
	} else if (stringNum == 1) {
          string2 = moveUpStr2(string2);
          std::cout << string2 << std::endl;
	} else if (stringNum == 2) {
          string3 = moveUpStr3(string3);
	} else if (stringNum == 3) {
          string4 = moveUpStr4(string4);
        }
        isOn = true;
      } else if (downPush[0] == '0') {
	if (stringNum == 0) {
          string1 = moveDownStr1(string1);
	} else if (stringNum == 1) {
          string2 = moveDownStr2(string2);
	} else if (stringNum == 2) {
          string3 = moveDownStr3(string3);
	} else if (stringNum == 3) {
          string4 = moveDownStr4(string4);
        }
        isOn = true;
      }
    } else {
//      std::cout << "Is on!" << std::endl;
//      std::cout << leftPush[0] << " " << rightPush[0] << " " 
//                << enterPush[0] << " " << upPush[0] << " "
//                << downPush[0] << std::endl;
      if ((leftPush[0] == '0') && (rightPush[0] == '0') &&
	  (enterPush[0] == '0') && (upPush[0] == '1') &&
	  (downPush[0] == '1')) {
//        std::cout << "All off!" << std::endl;
        i++;
        isOn = false;
      }
    }
    lseek(leftFile, SEEK_SET, 0);
    lseek(rightFile, SEEK_SET, 0);
    lseek(enterFile, SEEK_SET, 0);
    lseek(upFile, SEEK_SET, 0);
    lseek(downFile, SEEK_SET, 0);
  }
  close(leftFile);
  close(rightFile);
  close(enterFile);
  close(upFile);
  close(downFile);
}
