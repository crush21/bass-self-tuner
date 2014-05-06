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
    printf("Usage: runMotor1 freqDiff\n");
    printf("\nfreqDiff:\n");
    printf(" Floating point number represent difference between\n");
    printf(" measured and ideal frequencies.\n");
    exit(0);
  }

  freqDiff = strtod(argv[1], NULL); // Convert argument to double.

  cout << "motorTune: Done" << endl;
  double turns = motorTune(freqDiff, STRING4);
  cout << "Turns: " << turns << endl;
  if (turns > 0) {
    motorStart(FWDPATH4);
    cout << "motor forward" << endl;
    encoder(STRING1,turns);
    cout << "turning off motor" << endl;
    motorStop(FWDPATH4);
  } else if (turns < 0) {
    motorStart(REVPATH4);
    cout << "motor backward" << endl;
    encoder(STRING1,turns);
    cout << "turning off motor" << endl;
    motorStop(REVPATH4);
  }  
  cout << "Done tuning!" << endl;
  return 0;
}
