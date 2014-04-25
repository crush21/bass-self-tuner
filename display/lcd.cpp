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
  int string2 = 4; // Holds "note" of A string
  int string3 = 4; // Holds "note" of D string
  int string4 = 4; // Holds "note" of G string
  
  clearScreen();
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  startScreen();
  int i = 0;
  bool isOn = false;
  while (i < 40) {
    read(leftFile, leftPush, 1);
    read(rightFile, rightPush, 1);
    read(enterFile, enterPush, 1);
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
      } else if (enterPush[0] == '1') {
	if (stringNum == 4) {
	  tuningSequence(string1, string2, string3, string4);
	}
      } else if (upPush[0] == '1') {
	if (stringNum == 0) {
	  moveUp(string1);
	} else if (stringNum == 1) {
	  moveUp(string2);
	} else if (stringNum == 2) {
	  moveUp(string3);
	} else if (stringNum == 3) {
	  moveUp(string4);
        }
      } else if (downPush[0] == '1') {
	if (stringNum == 0) {
	  moveDown(string1);
	} else if (stringNum == 1) {
	  moveDown(string2);
	} else if (stringNum == 2) {
	  moveDown(string3);
	} else if (stringNum == 3) {
	  moveDown(string4);
        }
      }
    } else {
//      std::cout << "Is on!" << std::endl;
      if ((leftPush[0] == '0') && (rightPush[0] == '0') &&
	  (enterPush[0] == '0') && (upPush[0] == '0') &&
	  (downPush[0] == '0')) {
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
