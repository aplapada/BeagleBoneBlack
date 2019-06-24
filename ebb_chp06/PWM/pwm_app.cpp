#include<iostream>
#include<unistd.h> //for usleep
#include<string.h>
#include"PWM.h"
using namespace eeroSpace;
using namespace std;

int main(){
   //string pin = "P9_14";
   string pin = "P9_42";
   PWM pwm1A(pin);
   cout << "App starting: " << pin << endl;
   pwm1A.setState(1);
   usleep(5000000);
   pwm1A.setState(0);
   cout << "App finished " << endl;
   return 0;
}
