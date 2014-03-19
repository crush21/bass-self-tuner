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
  for (int i = 0; i < 200; i++) {
    cout << "Running forward" << endl;
    motorControl(fwdPath, 1000000); // Forward 5 seconds.
    motorControl(brake, 1000000); // Brake for 1 second.
    cout << "Running backward" << endl;
    motorControl(fwdPath, 1000000); // Backward 5 seconds.
    motorControl(brake, 1000000);
  }
}
