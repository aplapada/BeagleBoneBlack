#include "GPIO_my.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<cstdio>
#include<fcntl.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<pthread.h>
using namespace std;

namespace eeroSpace {

GPIO::GPIO(int num){
	this->num = num;
	//this->
	this->callbackFunction = NULL;
	this->threadRunning = false;
	this->debounceTime = 0;

	ostringstream s;
	s << "gpio" << num;
	this->name = string(s.str());
	this->path = GPIO_PATH + this->name +  "/";
	usleep(250000); // 250ms delay
}

int GPIO::write(string path, string fname, string val){
	ofstream fs;
	fs.open((path + fname).c_str());
	if (!fs.is_open()){
	   perror("GPIO: write failed to open file ");
	   return -1;
	}
	fs << val;
	fs.close();
	return 0;
}

int GPIO::write(string path, string fname, int val){
	stringstream s;
	s << val;
	return this->write(path,fname,s.str());
}

int GPIO::setDir(GPIO_DIR dir){
	switch(dir){
	case INPUT: return this->write(this->path, "direction", "in");
		break;
	case OUTPUT: return this->write(this->path, "direction", "out");
		break;
	}
	return -1;

}

int GPIO::setVal(GPIO_VAL val){
	switch(val){
	case HIGH: return this->write(this->path, "value", "1");
	      break;
	case LOW: return this->write(this->path, "value", "0");
	      break;
	}
	return -1;
}

int GPIO::setEdgeType(GPIO_EDGE edge){
	switch(edge){
	case NONE: return this->write(this->path, "edge", "none");
		break;
	case RISING: return this->write(this->path, "edge", "rising");
		break;
	case FALLING: return this->write(this->path, "edge", "falling");
		break;
	case BOTH: return this->write(this->path, "edge", "both");
		break;
	}
	return -1;
}

// Blocking Poll - based on the epoll socket code in the epoll man page
int GPIO::waitForEdge(){
	this->setDir(INPUT); // must be an input pin to poll its value
	int fd, i, epollfd, count=0;
	struct epoll_event ev;
	epollfd = epoll_create(1);
    if (epollfd == -1) {
	   perror("GPIO: Failed to create epollfd");
	   return -1;
    }
    if ((fd = open((this->path + "value").c_str(), O_RDONLY | O_NONBLOCK)) == -1) {
       perror("GPIO: Failed to open file");
       return -1;
    }

    //ev.events = read operation | edge triggered | urgent data
    ev.events = EPOLLIN | EPOLLET | EPOLLPRI;
    ev.data.fd = fd;  // attach the file file descriptor

    //Register the file descriptor on the epoll instance, see: man epoll_ctl
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
       perror("GPIO: Failed to add control interface");
       return -1;
    }
	while(count<=1){  // ignore the first trigger
		i = epoll_wait(epollfd, &ev, 1, -1);
		if (i==-1){
			perror("GPIO: Poll Wait fail");
			count=5; // terminate loop
		}
		else {
			count++; // count the triggers up
		}
	}
    close(fd);
    if (count==5) return -1;
	return 0;
}

int GPIO::waitForEdge(CallbackType callback){
	this->threadRunning = true;
	this->callbackFunction = callback;
    // create the thread, pass the reference, address of the function and data
    if(pthread_create(&this->thread, NULL, &threadedPoll, static_cast<void*>(this))){
    	perror("GPIO: Failed to create the poll thread");
    	this->threadRunning = false;
    	return -1;
    }
    return 0;
}


int GPIO::streamOpen(){
	stream.open((path + "value").c_str());
	return 0;
}
int GPIO::streamWrite(GPIO_VAL val){
	stream << val << std::flush;
	return 0;
}
int GPIO::streamClose(){
	stream.close();
	return 0;
}



void* threadedPoll(void *value){
	GPIO *gpio = static_cast<GPIO*>(value);
	while(gpio->threadRunning){
		gpio->callbackFunction(gpio->waitForEdge());
		usleep(gpio->debounceTime * 1000);
	}
	return 0;
}

GPIO::~GPIO() {
//	this->unexportGPIO();
}

} // eeroSpace
