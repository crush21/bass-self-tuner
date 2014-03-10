/* * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Code to get an analog signal from analog inputs
 * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Written by Cheyn Rushing
 */

#include "motorFunc.h"

using namespace std;

int main() {
  char fwdPath [29] = "/sys/class/gpio/gpio38/value"; // P8 Pin 3
  char bwdPath [29] = "/sys/class/gpio/gpio34/value"; // P8 Pin 5
  char brake [29] = "/sys/class/gpio/gpio66/value";   // P8 Pin 7
  while (1) {
    cout << "Running forward" << endl;
    motorControl(fwdPath); // Forward 1 second.
    motorControl(brake); // Brake for 1 second.
    cout << "Running backward" << endl;
    motorControl(bwdPath); // Backward 1 second.
    motorControl(brake);
  }
}
