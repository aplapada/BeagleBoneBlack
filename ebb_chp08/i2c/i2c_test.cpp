#include<iostream>
#include<unistd.h> //for usleep
#include"I2C.h"
using namespace eeroSpace;
using namespace std;

int main(){
	//bus, device
	I2C arduino(2,6);
	usleep(1000000);
	unsigned char x= 0x00;
	unsigned char readvalue;
	while(x < 51){
		arduino.write(x);
		//usleep(250000);
		readvalue = arduino.read();
		cout << "Read value: " << static_cast<unsigned int>(readvalue) << endl;
		//usleep(250000);
		x++;
	}
	//usleep(1000000);
}

