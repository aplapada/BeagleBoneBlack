#include"PWM.h"
//#include "util.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<string.h>
using std::string;
using namespace std;

namespace eeroSpace{

PWM::PWM(string pin){
	this->pin = pin;
	this->duty = 0;
	this->period = 0;
	if(this->select_chip()) std::cout << "Select chip failed" << endl;
	this->path = PWM_PATH + this->chip + "/";
	this->chipPath = PWM_PATH + this->chip + "/";
	if(this->export_device()) std::cout << "Export device failed" << endl;
	// save new this->path
	this->path += this->channel + "/";
	this->setInitValues();
}
int PWM::select_chip(){

	if((this->pin).compare("P9_14") == 0){
		this->chip = "pwmchip4";
		this->channel = "pwm-4:0";
		return 0;
	}else if((this->pin).compare("P9_16") == 0){
		this->chip = "pwmchip4";
		this->channel = "pwm-4:1";
		return 0;
	}else if((this->pin).compare("P9_21") == 0){ //
		this->chip = "pwmchip1";
		this->channel = "pwm-1:1";
		return 0;
	}else if((this->pin).compare("P9_22") == 0){ //
		this->chip = "pwmchip1";
		this->channel = "pwm-1:0";
		return 0;
	}else if((this->pin).compare("P9_42") == 0){
		this->chip = "pwmchip0";
		this->channel = "pwm-0:0";
		return 0;
	}
	//cout << "Select chip failed" << endl;
	return 1;
}

int PWM::export_device(){
	std::cout << "Exporting\n";
	// config pin
	string config_line = "config-pin " + this->pin + " pwm";
	if(system(config_line.c_str()) < 0) return 1;
	//export pwm
	//std::cout << "Export: " << this->path << " " << this->channel.back() << endl;

	this->write(this->chipPath, "export", string(1,this->channel.back()));

	return 0;
}

int PWM::setInitValues(){
	this->setPeriod(1000000000);
	this->setDuty(500000000);

	return 0;
}

int PWM::setPeriod(unsigned int period_ns){
	if(write(this->path, PWM_PERIOD, period_ns)==0){
		this->period = period_ns;
		return 0;
	}else{
		std::cout << "Failed to set period\n";
		return -1;
	}
}
int PWM::setDuty(unsigned int duty_ns){
	if(duty_ns > this->period){
		std::cout << "Trying to set higher duty_cycle than the period is!\n";
		return -1;
	}
	if(write(this->path, PWM_DUTY, duty_ns)==0){
		this->duty = duty_ns;
		return 0;
	}else{
		std::cout << "Failed to set duty_cycle\n";
		return -1;
	}

}

int PWM::setState(int state){
	return write(this->path, PWM_ENABLE, std::to_string(state));
}

int PWM::write(string path, string fname, string value){

	ofstream fs;
    fs.open((path + fname).c_str());
    if (!fs.is_open()){
    	std::cout << path << " " << fname << " " << value << endl;
 	   perror("PWM: write failed to open file ");
 	   return -1;
    }
    fs << value;
    fs.close();
    return 0;
}

int PWM::write(string path, string filename, int value){
   stringstream s;
   s << value;
   return write(path,filename,s.str());
}

PWM::~PWM() {
	//unexport the pwm
	//usleep(100000);
	this->write(this->chipPath, "unexport", string(1,this->channel.back()));
}

} //eeroSpace
