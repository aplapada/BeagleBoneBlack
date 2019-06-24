#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define BAUDRATE B115200   // Change as needed, keep B
#define MODEMDEVICE "/dev/ttyO1" //Beaglebone Black serial port

//#define _POSIX_SOURCE 1 /* POSIX compliant source */

//#define FALSE 0
//#define TRUE 1

int main()
{
    int fd, c, res;
    struct termios oldtio, newtio;
    char buf[255];
    
    // Load the pin configuration
    int suc1, suc2;
    if((suc1 = system("config-pin p9.24 uart")) < 0) printf("error\n");
    if((suc2 = system("config-pin p9.26 uart")) < 0) printf("error\n");	
    if(suc1 < 0 || suc2 < 0) return -1;
    
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
    if (fd < 0) { perror(MODEMDEVICE); exit(-1); }

    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

    /* BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
       CRTSCTS : output hardware flow control (only used if the cable has
                 all necessary lines. See sect. 7 of Serial-HOWTO)
       CS8     : 8n1 (8bit,no parity,1 stopbit)
       CLOCAL  : local connection, no modem contol
       CREAD   : enable receiving characters */
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

    /* IGNPAR  : ignore bytes with parity errors
       otherwise make device raw (no other input processing) */
    newtio.c_iflag = IGNPAR;

    /*  Raw output  */
    newtio.c_oflag = 0;

    /* ICANON  : enable canonical input
       disable all echo functionality, and don't send signals to calling program */
    newtio.c_lflag = ICANON;
    /* now clean the modem line and activate the settings for the port */
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
       
    
    printf("Start read\n");
    int i = 0;
unsigned char transmit[18] = "Hello BeagleBone!";
write(fd, &transmit, 18);	
    /* terminal settings done, now handle input*/
    while (1) {     /* loop continuously */
        printf("i = %d\n",i);
	        
	if ((i = read(fd, buf, 255))<0){   //receive the data
      		perror("Failed to read from the input\n");
      		return -1;
   	}
	buf[i] = 0;             /* set end of string, so we can printf */
        printf("Received: %s", buf);
	if(strcmp(buf, "1234\r\n")==0) printf("samat on\n");
	
	if(strcmp(buf, "end\r\n")==0) break;
	printf("Sending back to PC\n");
	write(fd, &buf, i);
    } 
    printf("End red\n");
    tcsetattr(fd, TCSANOW, &oldtio);
    return 0;
}
