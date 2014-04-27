/* Written by Cheyn Rushing
 * Defines functions used on the LCD screen,
 * using standard HD44780 instruction set.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
//#include <cmath>
#include <fcntl.h>

//using namespace std;

// LCD Data Bit files
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

// LCD Navigation Bit files
const char * leftData = "/sys/class/gpio/gpio20/value";
const char * rightData = "/sys/class/gpio/gpio7/value";
const char * enterData = "/sys/class/gpio/gpio70/value";
const char * upData = "/sys/class/gpio/gpio71/value";
const char * downData = "/sys/class/gpio/gpio72/value";

const char * ON = "1";
const char * OFF = "0";

/* Called to easily setup the LCD screen.
 * dispOn is display on bit.
 * cursorOn is cursor display bit.
 * blinkOn is cursor blink bit.
 * Receives:	 Characters representing 0 or 1.
 * Returns:	 Nothing.
 * Restrictions: Characters must be 0 or 1.
 */
void dispCtrl(char* dispOn, char* cursorOn, char* blinkOn) {
  if ((atoi(dispOn) > 1) || (atoi(cursorOn) > 1) || (atoi(blinkOn) > 1)) {
    std::cout << "Error: Parameter is greater than 1." << std::endl;
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

/* Clears the LCD screen.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
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

/* Called to set the current position on the LCD screen.
 * Receives:	 Seven bits determining position on the LCD.
 * Returns:	 Nothing.
 * Restrictions: None. LCD range is 0x00 (upper left corner) to 0x1F (lower right corner)
 */
void setDDRAM(const char * addr6, const char * addr5, const char * addr4,
	      const char * addr3, const char * addr2, const char * addr1, const char * addr0) {
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

/* Called write a character to the LCD.
 * Receives:	 A binary representation of a character based on HD44780.
 * Returns:	 Nothing.
 * Restrictions: None. Just know what character you want to write in binary.
 */
void writeChar(const char * dB7, const char * dB6, const char * dB5, const char * dB4,
	       const char * dB3, const char * dB2, const char * dB1, const char * dB0) {
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

/* Called to easily write an arrow to the LCD.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeArrow() {
  writeChar(OFF, ON, ON, ON, ON, ON, ON, OFF);
}

/* Called to write the "1" to the screen during the motor sequence.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeOne() {
  setDDRAM(ON, OFF, OFF, OFF, OFF, OFF, ON);
  writeChar(OFF, OFF, ON, ON, OFF, OFF, OFF, ON);	// "1"
}

/* Called to write the "2" to the screen during the motor sequence.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeTwo() {
  setDDRAM(ON, OFF, OFF, OFF, ON, OFF, OFF);
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, OFF);	// "2"
}

/* Called to write the "3" to the screen during the motor sequence.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeThree() {
  setDDRAM(ON, OFF, OFF, OFF, ON, ON, ON);
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, ON);	// "3"
}

/* Called to write the "4" to the screen during the motor sequence.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeFour() {
  setDDRAM(ON, OFF, OFF, ON, OFF, ON, OFF);
  writeChar(OFF, OFF, ON, ON, OFF, ON, OFF, OFF);	// "4"
}

/* Called to reset the screen to the start.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void startScreen() {
  setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
  writeArrow();							// "->"
  writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);	// "E"
  writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);	// "b"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);	// "A"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);	// "D"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);	// "G"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);	// "G"
  writeChar(OFF, ON, OFF, OFF, ON, ON, ON, ON);		// "O"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, ON);	// "!"

  setDDRAM(ON, OFF, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, OFF, ON);	// "1"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, OFF);	// "2"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, OFF, ON, ON);	// "3"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, ON, OFF, ON, OFF, OFF);	// "4"
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
}

/* Called if left pushbutton is pressed during navigation loop.
 * Receives:	 current position.
 * Returns:	 new position, one to the left.
 * Restrictions: max currentPos is 4.
 */
int moveLeft(int currentPos) {
  int curPos = currentPos;
  if (curPos > 4) {
    curPos = 0;
  }
  switch (curPos) {
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeArrow();
      break;
// Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      break;
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeArrow();
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeArrow();
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeArrow();
      break;
// Reset arrow to position 0 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      return 0;
  }
  if ((curPos - 1) < 0) {
    curPos = 5;
  }
  return (curPos - 1) % 5;
}

/* Called if right pushbutton is pressed during navigation loop.
 * Receives:	 current position.
 * Returns:	 new position, one to the right.
 * Restrictions: max currentPos is 4.
 */
int moveRight(int currentPos) {
  int curPos = currentPos;
  if (curPos > 4) {
    curPos = 0;
  }
  switch (curPos) {
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeArrow();
      break; // Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeArrow();
      break;
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeArrow();
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeArrow();
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      break;
// Reset arrow to position 0 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, ON, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, OFF);
      writeArrow();
      return 0;
  }
  return (curPos + 1) % 5;
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentPos is 4, max currentNote is 7.
 */
int moveUpStr1(int currentNote) {
  int curNote = currentNote;
  if (curNote > 7) {
    curNote = 4;
  }
  switch (curNote) {
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  return (curNote + 1) % 8;
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentPos is 4, max currentNote is 7.
 */
int moveUpStr1(int currentNote) {
  int curNote = currentNote;
  if (curNote > 12) {
    curNote = 9;
  }
  switch (curNote) {
// Case 5: C to F.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 6: C to F.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 7: C to F.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 8: C to F.
    case 8:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 9: C to F.
    case 9:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 10: Bb to B.
    case 10:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 11: B to C.
    case 11:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 12: C to F.
    case 12;
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset note to A.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 9;
  }
  return (curNote + 1) % 8 + 5;
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentPos is 4, max currentNote is 7.
 */
int moveUpStr1(int currentNote) {
  int curNote = currentNote;
  if (curNote > 7) {
    curNote = 4;
  }
  switch (curNote) {
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 5.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 6.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 7.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset arrow to position 4 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  return (curNote + 1) % 8 + 10;
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentPos is 4, max currentNote is 7.
 */
int moveUpStr1(int currentNote) {
  int curNote = currentNote;
  if (curNote > 7) {
    curNote = 4;
  }
  switch (curNote) {
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 5.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 6.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 7.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset arrow to position 4 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  return (curNote + 1) % 8 + 15;
}

/* Called if down pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one down.
 * Restrictions: max currentPos is 7.
 */
int moveDownStr1(int currentNote) {
  int curNote = currentNote;
  if (curNote > 7) {
    curNote = 4;
  }
  switch (curNote) {
// Arrow currently at position 2.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 3.
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 4.
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 5.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 6.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 7.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Arrow currently at position 0.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Arrow currently at position 1.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset arrow to position 4 and clear remaining positions.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  if ((curNote - 1) < 0) {
    curNote = 8;
  }
  return (curNote - 1) % 8;
}

/* Clears bottom row of LCD.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void clearBottomRow() {
  setDDRAM(ON, OFF, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
}

/* Called if enter pushbutton is pressed during navigation loop.
 * Receives:	 current position and whether on or off.
 * Returns:	 1 if on, 0 if off.
 * Restrictions: None.
 */
int tuningSequence(int firstString, int secondString,
		   int thirdString, int fourthString) {
  clearBottomRow();
  sleep(1);
  writeOne();
  sleep(2);
  writeTwo();
  sleep(2);
  writeThree();
  sleep(2);
  writeFour();
  return 0;
}
