/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include "motorFunc.h"

using namespace std;

int main() {
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
  for (int i = 0; i < 200; i++) {
    cout << "Running forward" << endl;
    motorControl(bwdPath, 30000000); // Forward 60 seconds.
    motorControl(brake, 1000000); // Brake for 1 second.
    cout << "Running backward" << endl;
    motorControl(bwdPath, 1000000); // Backward 5 seconds.
    motorControl(brake, 1000000);
  }
}
