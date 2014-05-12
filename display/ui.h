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

// Navigation Bit Files
const char * leftData = "/sys/class/gpio/gpio20/value";
const char * rightData = "/sys/class/gpio/gpio7/value";
const char * enterData = "/sys/class/gpio/gpio70/value";
const char * upData = "/sys/class/gpio/gpio71/value";
const char * downData = "/sys/class/gpio/gpio72/value";

const char * ON = "1";
const char * OFF = "0";

char stringSelect [30] = "->E     A     D     G     GO!";
char stringNums [25] = "  1     2     3     4";

/* Clears the LCD screen.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void clearScreen() {
  for (int i = 0; i < 60; i++) {
    std::cout << std::endl;
  }
}

/* Called to set the screen to the first string.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void selectString1() {
  stringSelect[0] = '-';
  stringSelect[1] = '>';
  stringSelect[6] = ' ';
  stringSelect[7] = ' ';
  stringSelect[12] = ' ';
  stringSelect[13] = ' ';
  stringSelect[18] = ' ';
  stringSelect[19] = ' ';
  stringSelect[24] = ' ';
  stringSelect[25] = ' ';
  clearScreen();
  std::cout << "SMARTune Self-Tuning System" << std::endl << std::endl;
  std::cout << stringSelect << std::endl;
  std::cout << stringNums << std::endl << std::endl;
}

/* Called to set the screen to the second string.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void selectString2() {
  stringSelect[0] = ' ';
  stringSelect[1] = ' ';
  stringSelect[6] = '-';
  stringSelect[7] = '>';
  stringSelect[12] = ' ';
  stringSelect[13] = ' ';
  stringSelect[18] = ' ';
  stringSelect[19] = ' ';
  stringSelect[24] = ' ';
  stringSelect[25] = ' ';
  clearScreen();
  std::cout << "SMARTune Self-Tuning System" << std::endl << std::endl;
  std::cout << stringSelect << std::endl;
  std::cout << stringNums << std::endl << std::endl;
}

/* Called to set the screen to the third string.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void selectString3() {
  stringSelect[0] = ' ';
  stringSelect[1] = ' ';
  stringSelect[6] = ' ';
  stringSelect[7] = ' ';
  stringSelect[12] = '-';
  stringSelect[13] = '>';
  stringSelect[18] = ' ';
  stringSelect[19] = ' ';
  stringSelect[24] = ' ';
  stringSelect[25] = ' ';
  clearScreen();
  std::cout << "SMARTune Self-Tuning System" << std::endl << std::endl;
  std::cout << stringSelect << std::endl;
  std::cout << stringNums << std::endl << std::endl;
}

/* Called to set the screen to the fourth string..
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void selectString4() {
  stringSelect[0] = ' ';
  stringSelect[1] = ' ';
  stringSelect[6] = ' ';
  stringSelect[7] = ' ';
  stringSelect[12] = ' ';
  stringSelect[13] = ' ';
  stringSelect[18] = '-';
  stringSelect[19] = '>';
  stringSelect[24] = ' ';
  stringSelect[25] = ' ';
  clearScreen();
  std::cout << "SMARTune Self-Tuning System" << std::endl << std::endl;
  std::cout << stringSelect << std::endl;
  std::cout << stringNums << std::endl << std::endl;
}

/* Called to set the screen to the "GO!" selection.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void selectGo() {
  stringSelect[0] = ' ';
  stringSelect[1] = ' ';
  stringSelect[6] = ' ';
  stringSelect[7] = ' ';
  stringSelect[12] = ' ';
  stringSelect[13] = ' ';
  stringSelect[18] = ' ';
  stringSelect[19] = ' ';
  stringSelect[24] = '-';
  stringSelect[25] = '>';
  clearScreen();
  std::cout << "SMARTune Self-Tuning System" << std::endl << std::endl;
  std::cout << stringSelect << std::endl;
  std::cout << stringNums << std::endl << std::endl;
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
      selectGo();
      break;
// Arrow currently at position 1.
    case 1:
      selectString1();
      break;
// Arrow currently at position 2.
    case 2:
      selectString2();
      break;
// Arrow currently at position 3.
    case 3:
      selectString3();
      break;
// Arrow currently at position 4.
    case 4:
      selectString4();
      break;
// Reset arrow to position 0 and clear remaining positions.
    default:
      selectString1();
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
      selectString2();
      break;
// Arrow currently at position 1.
    case 1:
      selectString3();
      break;
// Arrow currently at position 2.
    case 2:
      selectString4();
      break;
// Arrow currently at position 3.
    case 3:
      selectGo();
      break;
// Arrow currently at position 4.
    case 4:
      selectString1();
      break;
// Reset arrow to position 0 and clear remaining positions.
    default:
      selectString1();
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
      stringSelect[2] = 'D';
      stringSelect[3] = 'b';
      break;
// Case 1: Db to D.
    case 1:
      stringSelect[2] = 'D';
      stringSelect[3] = ' ';
      break;
// Case 2: D to Eb.
    case 2:
      stringSelect[2] = 'E';
      stringSelect[3] = 'b';
      break;
// Case 3: Eb to E.
    case 3:
      stringSelect[2] = 'E';
      stringSelect[3] = ' ';
      break;
// Case 4: E to F.
    case 4:
      stringSelect[2] = 'F';
      stringSelect[3] = ' ';
      break;
// Case 5: F to Gb.
    case 5:
      stringSelect[2] = 'G';
      stringSelect[3] = 'b';
      break;
// Case 6: Gb to G.
    case 6:
      stringSelect[2] = 'G';
      stringSelect[3] = ' ';
      break;
// Case 7: G to C.
    case 7:
      stringSelect[2] = 'C';
      stringSelect[3] = ' ';
      break;
// Reset note to E.
    default:
      stringSelect[2] = 'E';
      stringSelect[3] = ' ';
      selectString1();
      return 4;
  }
  selectString1();
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
      stringSelect[8] = 'G';
      stringSelect[9] = 'b';
      break;
// Case 6: Gb to G.
    case 6:
      stringSelect[8] = 'G';
      stringSelect[9] = ' ';
      break;
// Case 7: G to Ab.
    case 7:
      stringSelect[8] = 'A';
      stringSelect[9] = 'b';
      break;
// Case 8: Ab to A.
    case 8:
      stringSelect[8] = 'A';
      stringSelect[9] = ' ';
      break;
// Case 9: A to Bb.
    case 9:
      stringSelect[8] = 'B';
      stringSelect[9] = 'b';
      break;
// Case 10: Bb to B.
    case 10:
      stringSelect[8] = 'B';
      stringSelect[9] = ' ';
      break;
// Case 11: B to C.
    case 11:
      stringSelect[8] = 'C';
      stringSelect[9] = ' ';
      break;
// Case 12: C to F.
    case 12:
      stringSelect[8] = 'F';
      stringSelect[9] = ' ';
      break;
// Reset note to A.
    default:
      stringSelect[8] = 'A';
      stringSelect[9] = ' ';
      selectString2();
      return 9;
  }
  if (currentNote > 11) {
    currentNote = 4;
  }
  selectString2();
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
      stringSelect[14] = 'B';
      stringSelect[15] = ' ';
      break;
// Case 11: B to C.
    case 11:
      stringSelect[14] = 'C';
      stringSelect[15] = ' ';
      break;
// Case 12: C to Db.
    case 12:
      stringSelect[14] = 'D';
      stringSelect[15] = 'b';
      break;
// Case 13: Db to D.
    case 13:
      stringSelect[14] = 'D';
      stringSelect[15] = ' ';
      break;
// Case 14: D to Eb.
    case 14:
      stringSelect[14] = 'E';
      stringSelect[15] = 'b';
      break;
// Case 15: Eb to E.
    case 15:
      stringSelect[14] = 'E';
      stringSelect[15] = ' ';
      break;
// Case 16: E to F.
    case 16:
      stringSelect[14] = 'F';
      stringSelect[15] = ' ';
      break;
// Case 17: F to Bb.
    case 17:
      stringSelect[14] = 'B';
      stringSelect[15] = 'b';
      break;
// Reset note to D.
    default:
      stringSelect[14] = 'D';
      stringSelect[15] = ' ';
      selectString3();
      return 14;
  }
  if (currentNote > 16) {
    currentNote = 9;
  }
  selectString3();
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
      stringSelect[20] = 'E';
      stringSelect[21] = ' ';
      break;
// Case 16: E to F.
    case 16:
      stringSelect[20] = 'F';
      stringSelect[21] = ' ';
      break;
// Case 17: F to Gb.
    case 17:
      stringSelect[20] = 'G';
      stringSelect[21] = 'b';
      break;
// Case 18: Gb to G.
    case 18:
      stringSelect[20] = 'G';
      stringSelect[21] = ' ';
      break;
// Case 19: G to Ab.
    case 19:
      stringSelect[20] = 'A';
      stringSelect[21] = 'b';
      break;
// Case 20: Ab to A.
    case 20:
      stringSelect[20] = 'A';
      stringSelect[21] = ' ';
      break;
// Case 21: A to Bb.
    case 21:
      stringSelect[20] = 'B';
      stringSelect[21] = 'b';
      break;
// Case 22: Bb to Eb.
    case 22:
      stringSelect[20] = 'E';
      stringSelect[21] = 'b';
      break;
// Reset note to G.
    default:
      stringSelect[20] = 'G';
      stringSelect[21] = ' ';
      selectString4();
      return 19;
  }
  if (currentNote > 21) {
    currentNote = 14;
  }
  selectString4();
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
      stringSelect[2] = 'G';
      stringSelect[3] = ' ';
      break;
// Case 1: Db to C.
    case 1:
      stringSelect[2] = 'C';
      stringSelect[3] = ' ';
      break;
// Case 2: D to Db.
    case 2:
      stringSelect[2] = 'D';
      stringSelect[3] = 'b';
      break;
// Case 3: Eb to D.
    case 3:
      stringSelect[2] = 'D';
      stringSelect[3] = ' ';
      break;
// Case 4: E to Eb.
    case 4:
      stringSelect[2] = 'E';
      stringSelect[3] = 'b';
      break;
// Case 5: F to E.
    case 5:
      stringSelect[2] = 'E';
      stringSelect[3] = ' ';
      break;
// Case 6: Gb to F.
    case 6:
      stringSelect[2] = 'F';
      stringSelect[3] = ' ';
      break;
// Case 7: G to Gb.
    case 7:
      stringSelect[2] = 'G';
      stringSelect[3] = 'b';
      break;
// Reset note to E.
    default:
      stringSelect[2] = 'E';
      stringSelect[3] = ' ';
      selectString1();
      return 4;
  }
  if (currentNote < 1) {
    currentNote = 8;
  }
  selectString1();
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
    stringSelect[8] = 'C';
    stringSelect[9] = ' ';
    break;
// Case 6: Gb to F.
  case 6:
    stringSelect[8] = 'F';
    stringSelect[9] = ' ';
    break;
// Case 7: G to Gb.
  case 7:
    stringSelect[8] = 'G';
    stringSelect[9] = 'b';
    break;
// Case 8: Ab to G.
  case 8:
    stringSelect[8] = 'G';
    stringSelect[9] = ' ';
    break;
// Case 9: A to Ab.
  case 9:
    stringSelect[8] = 'A';
    stringSelect[9] = 'b';
    break;
// Case 10: Bb to A.
  case 10:
    stringSelect[8] = 'A';
    stringSelect[9] = ' ';
    break;
// Case 11: B to Bb.
  case 11:
    stringSelect[8] = 'B';
    stringSelect[9] = 'b';
    break;
// Case 12: C to B.
  case 12:
    stringSelect[8] = 'B';
    stringSelect[9] = ' ';
    break;
// Reset note to A.
  default:
    stringSelect[8] = 'A';
    stringSelect[9] = ' ';
    selectString2();
    return 9;
  }
  if (currentNote < 6) {
    currentNote = 13;
  }
  selectString2();
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
      stringSelect[14] = 'F';
      stringSelect[15] = ' ';
      break;
// Case 11: B to Bb.
    case 11:
      stringSelect[14] = 'B';
      stringSelect[15] = 'b';
      break;
// Case 12: C to B.
    case 12:
      stringSelect[14] = 'B';
      stringSelect[15] = ' ';
      break;
// Case 13: Db to C.
    case 13:
      stringSelect[14] = 'C';
      stringSelect[15] = ' ';
      break;
// Case 14: D to Db.
    case 14:
      stringSelect[14] = 'D';
      stringSelect[15] = 'b';
      break;
// Case 15: Eb to D.
    case 15:
      stringSelect[14] = 'D';
      stringSelect[15] = ' ';
      break;
// Case 16: E to Eb.
    case 16:
      stringSelect[14] = 'E';
      stringSelect[15] = 'b';
      break;
// Case 17: F to E.
    case 17:
      stringSelect[14] = 'E';
      stringSelect[15] = ' ';
      break;
// Reset note to D.
    default:
      stringSelect[14] = 'D';
      stringSelect[15] = ' ';
      selectString3();
      return 14;
  }
  if (currentNote < 11) {
    currentNote = 18;
  }
  selectString3();
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
      stringSelect[20] = 'B';
      stringSelect[21] = 'b';
      break;
// Case 16: E to Eb.
    case 16:
      stringSelect[20] = 'E';
      stringSelect[21] = 'b';
      break;
// Case 17: F to E.
    case 17:
      stringSelect[20] = 'E';
      stringSelect[21] = ' ';
      break;
// Case 18: Gb to F.
    case 18:
      stringSelect[20] = 'F';
      stringSelect[21] = ' ';
      break;
// Case 19: G to Gb.
    case 19:
      stringSelect[20] = 'G';
      stringSelect[21] = 'b';
      break;
// Case 20: Ab to G.
    case 20:
      stringSelect[20] = 'G';
      stringSelect[21] = ' ';
      break;
// Case 21: A to Ab.
    case 21:
      stringSelect[20] = 'A';
      stringSelect[21] = 'b';
      break;
// Case 22: Bb to A.
    case 22:
      stringSelect[20] = 'A';
      stringSelect[21] = ' ';
      break;
// Reset note to G.
    default:
      stringSelect[20] = 'G';
      stringSelect[21] = ' ';
      selectString4();
      return 19;
  }
  if (currentNote < 16) {
    currentNote = 23;
  }
  selectString4();
  return (currentNote - 1);
}

/* Writes the words "Strum string 1 now" to the terminal.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeStrum1() {
  std::cout << "Strum string 1 now" << std::endl << std::endl;
}

/* Writes the words "Strum string 2 now" to the terminal.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeStrum2() {
  std::cout << "Strum string 2 now" << std::endl << std::endl;
}

/* Writes the words "Strum string 3 now" to the terminal.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeStrum3() {
  std::cout << "Strum string 3 now" << std::endl << std::endl;
}

/* Writes the words "Strum string 4 now" to the terminal.
 * Receives:	 Nothing.
 * Returns:	 Nothing.
 * Restrictions: None.
 */
void writeStrum4() {
  std::cout << "Strum string 4 now" << std::endl << std::endl;
}

/* Called if enter pushbutton is pressed during navigation loop.
 * Receives:	 current position and whether on or off.
 * Returns:	 1 if on, 0 if off.
 * Restrictions: None.
 */
int tuningSequence(int firstString, int secondString,
                   int thirdString, int fourthString) {

  int enterFile = open(enterData, O_RDONLY);
  char enterPush [1];
  enterPush[0] = '3';

  pid_t childProcess1;
//  pid_t childProcess2;
//  pid_t childProcess3;
  pid_t childProcess4;
  pid_t waiting;
  int child_status1;
//  int child_status2;
//  int child_status3;
  int child_status4;
  char firstNote [2];
//  char secondNote [2];
//  char thirdNote [2];
  char fourthNote [2];
  const char * CMD1 = "/root/code/s1Analog";
//  const char * CMD2 = "/root/code/s2Analog";
//  const char * CMD3 = "/root/code/s3Analog";
  const char * CMD4 = "/root/code/s4Analog";

  usleep(1000000);
  while (enterPush[0] != '0') {
    read(enterFile, enterPush, 1);
    lseek(enterFile, SEEK_SET, 0);
  }
/*    
  writeStrum1();

  waiting = -1;
  sprintf(firstNote, "%d", firstString);
  std::cout << firstNote[0] << firstNote[1] << std::endl;
  childProcess1 = vfork();
  if (childProcess1 == 0) {
    writeStrum1();
    while (enterPush[0] != '1') {
      read(enterFile, enterPush, 1);
      lseek(enterFile, SEEK_SET, 0);
    }
    execlp(CMD1,"/root/code",reinterpret_cast<const char *>(firstNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status1);
      if (waiting == 1) {
        break;
      }
    } while (waiting != childProcess1);
  }

  std::cout << "Done with string 1!\n" << std::endl;
*/
/*
  waiting = -1;
  sprintf(secondNote, "%d", secondString);
  std::cout << secondNote[0] << secondNote[1] << std::endl;
    childProcess2 = vfork();
    if (childProcess2 == 0) {
      writeStrum2();
      execlp(CMD2,"/root/code",reinterpret_cast<const char *>(secondNote),(char*)NULL);
      std::cout << "Child!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status2);
        if (waiting == 1) {
          break;
        }
      } while (waiting != childProcess2);
  }
*/
//  std::cout << "Done with string 2!\n" << std::endl;
/*
  waiting = -1;
  sprintf(thirdNote, "%d", thirdString);
  std::cout << thirdNote[0] << thirdNote[1] << std::endl;
    childProcess3 = vfork();
    if (childProcess3 == 0) {
      writeStrum3();
      execlp(CMD3,"/root/code",reinterpret_cast<const char *>(thirdNote),(char*)NULL);
      std::cout << "Child!" << std::endl;
    } else {
      do {
        waiting = wait(&child_status3);
        if (waiting == 1) {
          break;
        }
    } while (waiting != childProcess3);
  }
*/
//  std::cout << "Done with string 3!\n" << std::endl;

  usleep(1000000);
  enterPush[0] = '3';
  writeStrum4();
  waiting = -1;
  sprintf(fourthNote, "%d", fourthString);
  std::cout << fourthNote[0] << fourthNote[1] << std::endl;
  childProcess4 = vfork();
  if (childProcess4 == 0) {
    writeStrum4();
    while (enterPush[0] != '1') {
      read(enterFile, enterPush, 1);
      lseek(enterFile, SEEK_SET, 0);
    }
    execlp(CMD4,"/root/code",reinterpret_cast<const char *>(fourthNote),(char*)NULL);
    std::cout << "Child!" << std::endl;
  } else {
    do {
      waiting = wait(&child_status4);
      if (waiting == 1) {
        break;
      }
    } while (waiting != childProcess4);
  }

  std::cout << "Done with string 4!\n" << std::endl;

  usleep(1000000);
  selectGo();
  return 0;
}
