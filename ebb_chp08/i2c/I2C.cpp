#include"I2C.h"
#include<iostream>
#include<sstream>
#include<fcntl.h>
#include<stdio.h>
#include<iomanip>
#include<unistd.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
using namespace std;

namespace eeroSpace{

I2C::I2C(unsigned int bus, unsigned int device){
	this->bus = bus;
	this->device = device;
	this->file = -1;
	this->open();

}

int I2C::open(){
	string name;
	if(		this->bus==0)name = "/dev/i2c-0";
	else if(this->bus==1)name = "/dev/i2c-1";
	else 				 name = "/dev/i2c-2";

	if((this->file=::open(name.c_str(), O_RDWR)) < 0){
	      perror("I2C: failed to open the bus\n");
		  return 1;
    }
    if(ioctl(this->file, I2C_SLAVE, this->device) < 0){
	      perror("I2C: Failed to connect to the device\n");
		  return 1;
	}
    cout << "File opened" << endl;
    return 0;
}

int I2C::write(unsigned char value){
	unsigned char buffer[1];
	buffer[0]=value;
	if(::write(this->file, buffer, 1)!=1){
	      perror("I2C: Failed to write to the device\n");
	      return 1;
	}
	return 0;
}

int I2C::writeReg(unsigned char reg, unsigned char value){

}
unsigned char I2C::read(){
	//this->write(0);
    unsigned char buffer[1];
    if(::read(this->file, buffer, 1)!=1){
       perror("I2C: Failed to read in the value.\n");
       return 1;
   }
   return buffer[0];
}
unsigned char* I2C::readReg(unsigned char reg, unsigned char value){

}

void I2C::close(){
	::close(this->file);
	this->file = -1;
}

I2C::~I2C() {
	if(file!=-1) this->close();
}

} //eeroSpace
