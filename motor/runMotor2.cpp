/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code that runs the motors for tuning the bass.
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Chris Diemer and Cheyn Rushing
 */

#include "motorFunc.h"

using namespace std;


int main(int argc, char * argv[]) {
  double freqDiff;

  if (argc != 2) {
    printf("\nYou must provide one argument.\n");
    printf("Usage: runMotor2 freqDiff\n");
    printf("\nfreqDiff:\n");
    printf(" Floating point number represent difference between\n");
    printf(" measured and ideal frequencies.\n");
    exit(0);
  }

  freqDiff = strtod(argv[1], NULL); // Convert argument to double.

  cout << "motorTune: Done" << endl;
  double turns = motorTune(freqDiff, STRING2);
  cout << "Turns: " << turns << endl;
/* This function is different from the other strings
 * because three of our six infrared sensors failed
 * to properly work. Because of this, a time-based
 * motor tuning is implemented.
 */
  turnMotor2(turns);

  cout << "Done tuning!" << endl;
  return 0;
}
