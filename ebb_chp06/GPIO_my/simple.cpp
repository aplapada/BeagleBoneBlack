/* A Simple GPIO application
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2018
* ISBN 9781119533160. Please see the file README.md in the repository root
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<unistd.h> //for usleep
#include"GPIO_my.h"
using namespace eeroSpace;
using namespace std;

int main(){
   int ledGPIO = 60;
   GPIO outGPIO(ledGPIO);//, inGPIO(46);
   cout << "Blinkind GPIO: " << ledGPIO << endl;	
   // Basic Output - Flash the LED 10 times, once per second
   outGPIO.setDir(OUTPUT);
   for (int i=0; i<10; i++){
      outGPIO.setVal(HIGH);
      usleep(500000); //micro-second sleep 0.5 seconds
      outGPIO.setVal(LOW);
      usleep(500000);
   }
   cout << "Blinking finished " << endl;
   // Basic Input example
   //inGPIO.setDirection(INPUT);
   //cout << "The value of the input is: "<< inGPIO.getValue() << endl;

   // Fast write to GPIO 1 million times
   /*outGPIO.streamOpen();
   for (int i=0; i<1000000; i++){
      outGPIO.streamWrite(HIGH);
      outGPIO.streamWrite(LOW);
   }
   outGPIO.streamClose();
   */
   return 0;
}
