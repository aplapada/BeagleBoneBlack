#include<iostream>
#include<stdio.h>
using namespace std;

void adder(int *value);
int main(){
  int luku = 2;
  
  adder(&luku);
  printf("Luku on: %d\n", luku);
  return 0;
}

void adder(int *value){
  *value = 5;
}
