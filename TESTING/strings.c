#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

void adder(int *value);
int pituus(char *arr){
  return strlen(arr);
}
int main(){
  char arr[4] = "xyz";
  
  printf("%d\n",pituus(arr));
  printf("Sana on: %s\n", arr);
  strcpy(arr,"NEW123");
  printf("%d\n",pituus(arr));
  arr[0] = '\0';
  printf("%d\n",pituus(arr));
  printf("Sana on: %s\n", arr);
  printf("Eka %c\n", arr[0]);
  printf("toka %c\n", arr[3]);
  return 0;
}

void adder(int *value){
  *value = 5;
}

