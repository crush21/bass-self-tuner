/* Written by Cheyn Rushing
 * Defines functions used on the LCD screen,
 * using standard HD44780 instruction set.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <sys/wait.h>

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
void dispCtrl(const char * dispOn, const char * cursorOn, const char * blinkOn) {
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
  writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);	// " "
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
  if (curPos < 1) {
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
 * Restrictions: max currentNote is 7, minimum is 0.
 */
int moveUpStr1(int currentNote) {
  switch (currentNote) {
// Case 0: C to Db.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 1: Db to D.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 2: D to Eb.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 3: Eb to E.
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 4: E to F.
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 5: F to Gb.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 6: Gb to G.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 7: G to C.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset note to E.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  return (currentNote + 1) % 8;
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 2 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentNote is 12, minimum is 5.
 */
int moveUpStr2(int currentNote) {
  switch (currentNote) {
// Case 5: F to Gb.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 6: Gb to G.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 7: G to Ab.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 8: Ab to A.
    case 8:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 9: A to Bb.
    case 9:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 10: Bb to B.
    case 10:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 11: B to C.
    case 11:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 12: C to F.
    case 12:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset note to A.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 9;
  }
  if (currentNote > 11) {
    currentNote = 4;
  }
  return (currentNote + 1);
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 3 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentNote is 17, minimum is 10.
 */
int moveUpStr3(int currentNote) {
  switch (currentNote) {
// Case 10: Bb to B.
    case 10:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 11: B to C.
    case 11:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 12: C to Db.
    case 12:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 13: Db to D.
    case 13:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 14: D to Eb.
    case 14:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 15: Eb to E.
    case 15:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 16: E to F.
    case 16:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 17: F to Bb.
    case 17:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Reset note to D.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 14;
  }
  if (currentNote > 16) {
    currentNote = 9;
  }
  return (currentNote + 1);
}

/* Called if up pushbutton is pressed during navigation loop
 * and string 4 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one up.
 * Restrictions: max currentNote is 22, minimum is 15.
 */
int moveUpStr4(int currentNote) {
  switch (currentNote) {
// Case 15: Eb to E.
    case 15:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 16: E to F.
    case 16:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 17: F to Gb.
    case 17:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 18: Gb to G.
    case 18:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 19: G to Ab.
    case 19:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 20: Ab to A.
    case 20:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 21: A to Bb.
    case 21:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 22: Bb to Eb.
    case 22:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Reset note to G.
    default:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 19;
  }
  if (currentNote > 21) {
    currentNote = 14;
  }
  return (currentNote + 1);
}

/* Called if down pushbutton is pressed during navigation loop
 * and string 1 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one down.
 * Restrictions: max currentPos is 7, minimum is 0.
 */
int moveDownStr1(int currentNote) {
  switch (currentNote) {
// Case 0: C to G.
    case 0:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 1: Db to C.
    case 1:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 2: D to Db.
    case 2:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 3: Eb to D.
    case 3:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 4: E to Eb.
    case 4:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 5: F to E.
    case 5:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 6: Gb to F.
    case 6:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 7: G to Gb.
    case 7:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Reset note to E.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 4;
  }
  if (currentNote < 1) {
    currentNote = 8;
  }
  return (currentNote - 1);
}

/* Called if down pushbutton is pressed during navigation loop
 * and string 2 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one down.
 * Restrictions: max currentNote is 12, minimum is 5.
 */
int moveDownStr2(int currentNote) {
  switch (currentNote) {
// Case 5: F to C.
  case 5:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    break;
// Case 6: Gb to F.
  case 6:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    break;
// Case 7: G to Gb.
  case 7:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
    writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
    break;
// Case 8: Ab to G.
  case 8:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    break;
// Case 9: A to Ab.
  case 9:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
    writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
    break;
// Case 10: Bb to A.
  case 10:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    break;
// Case 11: B to Bb.
  case 11:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
    writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
    break;
// Case 12: C to B.
  case 12:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    break;
// Reset note to A.
  default:
    setDDRAM(OFF, OFF, OFF, OFF, ON, OFF, OFF);
    writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
    writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
    return 9;
  }
  if (currentNote < 6) {
    currentNote = 13;
  }
  return (currentNote - 1);
}

/* Called if down pushbutton is pressed during navigation loop
 * and string 3 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one down.
 * Restrictions: max currentNote is 17, minimum is 10.
 */
int moveDownStr3(int currentNote) {
  switch (currentNote) {
// Case 10: Bb to F.
    case 10:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 11: B to Bb.
    case 11:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 12: C to B.
    case 12:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 13: Db to C.
    case 13:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 14: D to Db.
    case 14:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 15: Eb to D.
    case 15:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 16: E to Eb.
    case 16:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 17: F to E.
    case 17:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset note to D.
    default:
      setDDRAM(OFF, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 14;
  }
  if (currentNote < 11) {
    currentNote = 18;
  }
  return (currentNote - 1);
}

/* Called if down pushbutton is pressed during navigation loop
 * and string 4 is selected.
 * Receives:	 current position.
 * Returns:	 new position, one down.
 * Restrictions: max currentNote is 22, minimum is 15.
 */
int moveDownStr4(int currentNote) {
  switch (currentNote) {
// Case 15: Eb to Bb.
    case 15:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, ON, OFF);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 16: E to Eb.
    case 16:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 17: F to E.
    case 17:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 18: Gb to F.
    case 18:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, OFF);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 19: G to Gb.
    case 19:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 20: Ab to G.
    case 20:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Case 21: A to Ab.
    case 21:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, ON, ON, OFF, OFF, OFF, ON, OFF);
      break;
// Case 22: Bb to A.
    case 22:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, OFF, OFF, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      break;
// Reset note to G.
    default:
      setDDRAM(OFF, OFF, OFF, ON, OFF, ON, OFF);
      writeChar(OFF, ON, OFF, OFF, OFF, ON, ON, ON);
      writeChar(OFF, OFF, ON, OFF, OFF, OFF, OFF, OFF);
      return 19;
  }
  if (currentNote < 16) {
    currentNote = 23;
  }
  return (currentNote - 1);
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
  pid_t childProcess1;
  pid_t childProcess2;
  pid_t childProcess3;
  pid_t childProcess4;
  pid_t waiting;
  int child_status1;
  int child_status2;
  int child_status3;
  int child_status4;
  char firstNote [2];
  char secondNote [2];
  char thirdNote [2];
  char fourthNote [2];
  const char * cmd1 = "/root/code/s1Analog";
  const char * cmd2 = "/root/code/s2Analog";
  const char * cmd3 = "/root/code/s3Analog";
  const char * cmd4 = "/root/code/s4Analog";
/*
  sprintf(firstNote, "%d", firstString);
  std::cout << firstNote[0] << firstNote[1] << std::endl;
  clearBottomRow();
  childProcess1 = vfork();
  if (childProcess1 == 0) {
    execlp(cmd1,"/root/code",reinterpret_cast<const char *>(firstNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status1);
    } while (waiting != childProcess1);
  }
  writeOne();
  
  sprintf(secondNote, "%d", secondString);
  std::cout << secondNote[0] << secondNote[1] << std::endl;
  clearBottomRow();
  childProcess2 = vfork();
  if (childProcess2 == 0) {
    execlp(cmd2,"/root/code",reinterpret_cast<const char *>(secondNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status2);
    } while (waiting != childProcess2);
  }
  writeTwo();

  sprintf(thirdNote, "%d", thirdString);
  std::cout << thirdNote[0] << thirdNote[1] << std::endl;
  clearBottomRow();
  childProcess3 = vfork();
  if (childProcess3 == 0) {
    execlp(cmd3,"/root/code",reinterpret_cast<const char *>(thirdNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status3);
    } while (waiting != childProcess3);
  }
  writeThree();
*/
  sprintf(fourthNote, "%d", fourthString);
  std::cout << fourthNote[0] << fourthNote[1] << std::endl;
  clearBottomRow();
  childProcess4 = vfork();
  if (childProcess4 == 0) {
    execlp(cmd4,"/root/code",reinterpret_cast<const char *>(fourthNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status4);
    } while (waiting != childProcess4);
  }
  writeFour();
  return 0;
}
