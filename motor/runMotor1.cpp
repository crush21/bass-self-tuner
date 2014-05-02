/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code that runs the motors for tuning the bass.
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Chris Diemer and Cheyn Rushing
 */

#include "motorFunc.h"

using namespace std;

const char FWDPATH [29] = "/sys/class/gpio/gpio69/value"; // P8 Pin 7
const char BWDPATH [29] = "/sys/class/gpio/gpio66/value"; // P8 Pin 9
//  char FWDPATH [29] = "/sys/class/gpio/gpio67/value"; // P8 Pin 8
//  char BWDPATH [29] = "/sys/class/gpio/gpio68/value"; // P8 Pin 10
//  char FWDPATH [29] = "/sys/class/gpio/gpio23/value"; // P8 Pin 13
//  char BWDPATH [29] = "/sys/class/gpio/gpio47/value"; // P8 Pin 15
//  char FWDPATH [29] = "/sys/class/gpio/gpio26/value"; // P8 Pin 14
//  char BWDPATH [29] = "/sys/class/gpio/gpio46/value"; // P8 Pin 16


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
  double turns = motorTune(freqDiff, STRING1);
  cout << "Turns: " << turns << endl;
  if (turns > 0) {
    motorStart(FWDPATH);
    cout << "motor forward" << endl;
    encoder(STRING1,turns);
    cout << "turning off motor" << endl;
    motorStop(FWDPATH);
    usleep(1000000);
  } else if (turns < 0) {
    motorStart(BWDPATH);
    cout << "motor backward" << endl;
    encoder(STRING1,turns);
    cout << "turning off motor" << endl;
    motorStop(BWDPATH);
    usleep(1000000);    
  }

  cout << "Done tuning!" << endl;
  return 0;
}
