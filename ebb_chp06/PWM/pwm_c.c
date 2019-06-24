#include <stdlib.h> //system call
#include<stdio.h>   //printf
#include<string.h>
#include<unistd.h>  //file operations
#include <fcntl.h>

#define PWM_PATH "/sys/class/pwm/pwmchip4/"//"/sys/devices/ocp.3/"

int main(){
	char str[100];
	strcpy(str,PWM_PATH);
	int file;
	//if(system("config-pin p9.14 pwm") < 0) printf("error\n");

	//if(system("echo 1 > /sys/class/pwm/pwmchip4/export")) printf("error2\n");
	//file = open("/sys/class/pwm/pwmchip4/pwm-4:0/",O_RDWR);

	if(system("echo 1000000000 > /sys/class/pwm/pwmchip4/pwm-4:0/period")) printf("error2\n");
	if(system("echo 500000000 > /sys/class/pwm/pwmchip4/pwm-4:0/duty_cycle")) printf("error2\n");
	if(system("echo 1 > /sys/class/pwm/pwmchip4/pwm-4:0/enable")) printf("error2\n");
	/*if ((file = open("/sys/class/pwm/pwmchip4/pwm-4:0",O_RDWR))<0){
	      perror("UART: Failed to open the file.\n");
	      return -1;
	}
	if(write(file,"period",1000000000) <0)printf("error3\n");

	strcat(str, "export/");
	printf("%s\n", str);
	char yksi = '1';
	//write(file,,)
	file = open(str, O_RDWR);
	write(file,&yksi,1);
	*/
	return 0;
}
