#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

void adder(char *value);
void printti(char *arr);

int main(){
  char str[] = "xyz";
  int len = 3;
  char *arr = (char *)malloc(sizeof(char) * (len+1));
  strcpy(arr,"EKA");
  printti(arr);
  strcpy(arr,"NEW");
  printf("Sana: %s ja pituus: %d\n"",arr, strlen(arr));
  //const char *str = "xyz";
  //*str = "hello";
  //adder(str);
  printti(str);
//printf("Luku on: %s\n", str);
  free(arr);
  return 0;
}

void adder(char value){
  //value = "hello";
}

void printti(char *arr){
  //strcpy(arr,"XXX");
  printf("Sana on: %s\n", arr);
}

