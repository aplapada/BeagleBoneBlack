#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO_my.h"
using namespace eeroSpace;
using namespace std;

GPIO *outGPIO, *inGPIO;           //global pointers

int activateLED(int var){
   outGPIO->streamWrite(HIGH);    //turn on the LED
   cout << "Button Pressed" << endl;
   return 0;
}

int main(){
   inGPIO = new GPIO(115);         //button
   outGPIO = new GPIO(60);        //LED
   inGPIO->setDir(INPUT);   //button is an input
   outGPIO->setDir(OUTPUT); //LED is an output
   outGPIO->streamOpen();         //fast write to LED
   outGPIO->streamWrite(LOW);     //turn the LED off
   inGPIO->setEdgeType(RISING);  //wait for falling edge
   cout << "You have 10 seconds to press the button:" << endl;
   inGPIO->waitForEdge(&activateLED); //pass the function
   cout << "Listening, but also doing something else..." << endl;
   for(int i = 0; i < 10; i++){
	   cout << "i = " << i << endl;
	   usleep(1000000);
   }
   //usleep(10000000);              //allow 10 seconds
   outGPIO->streamWrite(LOW);     //turn off the LED after 10 seconds
   outGPIO->streamClose();        //sutdown
   cout << "App completed" << endl;
   return 0;
}
