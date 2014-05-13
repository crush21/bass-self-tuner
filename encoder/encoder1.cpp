/**********************************************

Encoder code written by Chris Diemer 5/2/2014

***********************************************/


#include <iostream> 
#include <unistd.h>
#include <fcntl.h>

using namespace std;


int main() {

const char INPIN [29] = "/sys/class/gpio/gpio87/value";

int Handle = open(INPIN, O_RDONLY);


char ReadValue1 [2];
char LastRead [2];
char ReadValue2;
int counter = 0;
timespec startTime, lastTime;
double runTime;
double debounceTime = 0;
lastTime.tv_sec = 0;
lastTime.tv_nsec = 0;

read(Handle, LastRead, 1);
lseek(Handle, 0, SEEK_SET);


while(1){
ReadValue2 = ReadValue1[0];
read(Handle, ReadValue1, 1);
lseek(Handle, 0, SEEK_SET);
clock_gettime(CLOCK_MONOTONIC,&startTime);

if ( ReadValue1[0] != ReadValue2){
double nTime = (startTime.tv_nsec - lastTime.tv_nsec);
double sTime = (startTime.tv_sec - lastTime.tv_sec);
runTime = sTime + nTime/1000000000.0;
cout << "runTime: " << runTime << endl;

	if(runTime > debounceTime){
		if(ReadValue1[0] != LastRead[0]){
		clock_gettime(CLOCK_MONOTONIC,&lastTime);
		counter++;
		cout << "counter: " << counter << endl;
		}
	}
}


}
}
