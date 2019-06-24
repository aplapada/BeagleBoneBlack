#include <stdio.h>
#include <stdlib.h>
   #include <unistd.h>
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
  
   #include <string.h>

   int main(int argc, char *argv[])
   {
	//char temp[100];
	//strcpy(temp, PWM_PATH);
	system("/home/apla/pwm/pwm_bash/pwm_config.sh pwmchip4 p9.14 pwm-4:0");
        //printf("Path: %s\n", PWM_PATH);
	//printf("Path: %s\n", strcat(temp,"/duty_cycle"));
	int f;      
	char cmd[10];
	unsigned int cmd_value = 0;
	char str[12];
	char onoff[5];
	while(1){
		printf("\nGive command (duty, period, on, off):");
		scanf("%s", &cmd);
	
	
		if(strcmp(cmd,"duty") == 0){
			printf("Give value:");
			scanf("%u", &cmd_value);
	                printf("%u\n", cmd_value);
			f = open("/sys/class/pwm/pwmchip4/pwm-4:0/duty_cycle", O_WRONLY);
			cmd_value *= 1000000;
			sprintf(str, "%u", cmd_value);
			write(f,str,sizeof(str));	
		}else if(strcmp(cmd,"period")==0){
			printf("Give value:");
			scanf("%u", &cmd_value);
	                printf("%u\n", cmd_value);
			f = open("/sys/class/pwm/pwmchip4/pwm-4:0/period", O_WRONLY);
                        cmd_value *= 1000000;
			sprintf(str,"%u",cmd_value);
                        write(f,str,sizeof(str));   
		}else if(strcmp(cmd,"on")==0 || strcmp(cmd, "off") == 0){
			
			f = open("/sys/class/pwm/pwmchip4/pwm-4:0/enable", O_WRONLY);
			if(strcmp(cmd,"on") == 0){
				write(f,"1",sizeof("1"));
			}else if(strcmp(cmd,"off") == 0){
				write(f,"0",sizeof("0"));
			}
		}else{
			break;
		}
	}
       	return 0;
   }
