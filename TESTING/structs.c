#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

enum State {ON, OFF, FLASH};
enum Kuukausi {JAN = 1, FEB = 2, MAR = 3};

typedef enum{
	GPIO_Mode_IN  =  0,
	GPIO_Mode_OUT =  1
}GPIOmode_Typedef;

typedef struct{
  int GPIO_Pin;
  GPIOmode_Typedef GPIO_Mode;
  State GPIOstate;
}GPIO_typedef;

void GPIO_Init(GPIO_typedef *GPIO){

  if(GPIO->GPIO_Pin == 5){
	printf("Pinni on: %d\n", GPIO->GPIO_Pin);
	GPIO->GPIO_Pin = 3;
  }
}

int main(){
  GPIO_typedef initStruct;
  initStruct.GPIO_Pin = 5;
  initStruct.GPIO_Mode = GPIO_Mode_OUT;
  initStruct.GPIOstate = FLASH;
  GPIO_Init(&initStruct);
  printf("Pin: %d, Mode: %d\n", initStruct.GPIO_Pin, initStruct.GPIO_Mode);
  printf("%d\n", initStruct.GPIOstate);
  if(initStruct.GPIOstate == FLASH){
     printf("FLASH\n");
  }
  Kuukausi kk = FEB;
  if(kk == 2){
   printf("FEB\n");

  }
  if(kk == FEB){
   printf("FEB\n");
  }

  return 0;
}
