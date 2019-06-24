#include<iostream>
#include<unistd.h>
#include"GPIO_my.h"
using namespace eeroSpace;
using namespace std;

int main(){
   if(getuid() != 0){
	   cout << "Must be run as root. Exiting!" << endl;
	   return -1;
   }
   GPIO outGPIO(60), inGPIO(115);
   inGPIO.setDir(INPUT);    //button is an input
   outGPIO.setDir(OUTPUT);  //LED is an output
   inGPIO.setEdgeType(RISING);   //wait for falling edge
   outGPIO.streamOpen();          //fast write, ready file
   outGPIO.streamWrite(LOW);      //turn the LED off
   cout << "Press the button:" << endl;
   inGPIO.waitForEdge();          //will wait forever
   outGPIO.streamWrite(HIGH);     //button pressed, light LED
   outGPIO.streamClose();         //close the output stream
   usleep(1000000); //1s
   outGPIO.setVal(LOW);  //LED is an output
   return 0;
}
