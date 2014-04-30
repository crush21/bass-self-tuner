/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code that runs the motors for tuning the bass.
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Chris Diemer and Cheyn Rushing
 */

#include "motorFunc.h"

using namespace std;

int main(int argc, char * argv[]) {
  char fwdPath [29] = "/sys/class/gpio/gpio69/value"; // P8 Pin 7
  char bwdPath [29] = "/sys/class/gpio/gpio66/value"; // P8 Pin 9
  char brake [29] = "/sys/class/gpio/gpio45/value";   // P8 Pin 11
//  char fwdPath [29] = "/sys/class/gpio/gpio67/value"; // P8 Pin 8
//  char bwdPath [29] = "/sys/class/gpio/gpio68/value"; // P8 Pin 10
//  char brake [29] = "/sys/class/gpio/gpio45/value"; // P8 Pin 12
//  char fwdPath [29] = "/sys/class/gpio/gpio23/value"; // P8 Pin 13
//  char bwdPath [29] = "/sys/class/gpio/gpio47/value"; // P8 Pin 15
//  char brake [29] = "/sys/class/gpio/gpio27/value"; // P8 Pin 17
//  char fwdPath [29] = "/sys/class/gpio/gpio26/value"; // P8 Pin 14
//  char bwdPath [29] = "/sys/class/gpio/gpio46/value"; // P8 Pin 16
//  char brake [29] = "/sys/class/gpio/gpio65/value"; // P8 Pin 18

  if (argc != 2) {
    printf("\nYou must provide one argument.\n");
    printf("The argument represents a note for a string.\n");
    printf("The note starts at 0 = C and increases by one half step\n");
    printf("For every integer increase of 1, to a maximum of 7 = G.\n\n");
    printf("Usage: runMotor1 centDiff\n");
    printf("centDiff:\n");
    printf(" Floating point number represent difference between\n");
    printf(" measured and ideal frequencies.\n");
    exit(0);
  }

  for (int i = 0; i < 200; i++) {
    cout << "Running forward" << endl;
    motorControl(bwdPath, 500000); // Forward 60 seconds.
    motorControl(brake, 1000000); // Brake for 1 second.
    cout << "Running backward" << endl;
    motorControl(bwdPath, 500000); // Backward 5 seconds.
    motorControl(brake, 1000000);
  }
/*
  cout << "The amount of time required to turn the motor is: " << motorTune(5, 'G') << endl;
  
  double time = motorTune(5, 'G');

  if(time < 0){
	cout << "Running Backward" << endl;
	time = time * -1000000;
	motorControl(bwdPath, time);
	cout << "using double for unsigned worked!";
  	motorControl(brake, 1000000);
	}
  if(time > 0){
	cout << "Running Forward" << endl;
	time = time * 1000000;
	motorControl(fwdPath, time);
	cout << "using double for unsigned worked!";
	motorControl(brake, 1000000);
	}
*/
}
