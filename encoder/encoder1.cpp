 using namespace std;


int main() {

const char INPIN [29] = "/sys/class/gpio/gpio87/value";

int Array[2];
int counter = 0;


while(1){
Array[0] = Array[1];
Array[0] = INPIN;

if ( Array[0] != Array[1]){
 Counter++

 cout << the counter is at: << "Counter" << endl;
}

}
}
