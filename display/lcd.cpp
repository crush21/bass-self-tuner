/* Written by Cheyn Rushing
 * To control the 16 x 2 character LCD interface
 */

#include "lcd.h"

int main() {
  clearScreen();
  char * ZERO = "0";
  char * ONE = "1";
  
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
/* Have to do this twice, or the top row will be offset by one character to the left.
 * Still trying to figure out why this is so.
 */
  setDDRAM(ZERO, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  writeChar(ZERO, ONE, ONE, ONE, ONE, ONE, ONE, ZERO);		// "->"
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ZERO, ONE);	// "E"
  writeChar(ZERO, ONE, ONE, ZERO, ZERO, ZERO, ONE, ZERO);	// "b"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO, ONE);	// "A"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ZERO, ZERO);	// "D"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ONE, ONE);	// "G"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ONE, ZERO, ZERO, ZERO, ONE, ONE, ONE);	// "G"
  writeChar(ZERO, ONE, ZERO, ZERO, ONE, ONE, ONE, ONE);		// "O"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ONE);	// "!"

  setDDRAM(ONE, ZERO, ZERO, ZERO, ZERO, ZERO, ZERO);
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ZERO, ONE);	// "1"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ONE, ZERO);	// "2"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ZERO, ONE, ONE);	// "3"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ONE, ZERO, ONE, ZERO, ZERO);	// "4"
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
  writeChar(ZERO, ZERO, ONE, ZERO, ZERO, ZERO, ZERO, ZERO);	// " "
}
