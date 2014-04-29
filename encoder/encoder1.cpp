#include <iostream> 
#include <unistd.h>
#include <fcntl.h>

using namespace std;


int main() {

const char INPIN [29] = "/sys/class/gpio/gpio87/value";

int Handle = open(INPIN, O_RDONLY);


char Value1 [2];
char Value2;
int counter = 0;


while(1){
Value2 = Value1[0];
read(Handle, Value1, 1);
lseek(Handle, 0, SEEK_SET);

if ( Value1[0] != Value2){
 counter++;

 cout << "the counter is at: "  << counter << endl;
}

}
}
