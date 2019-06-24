#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library

int main(){
   int file, count;

   if ((file = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }
   struct termios options;               //The termios structure is vital
   tcgetattr(file, &options);            //Sets the parameters associated with file

   // Set up the communications options:
   //   9600 baud, 8-bit, enable receiver, no modem control lines
   options.c_cflag = B9600 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;    //ignore partity errors, CR -> newline
   tcflush(file, TCIFLUSH);             //discard file information not transmitted
   tcsetattr(file, TCSANOW, &options);  //changes occur immmediately

   unsigned char transmit[18] = "Hello BeagleBone!";  //the string to send

   if ((count = write(file, &transmit,18))<0){        //send the string
      perror("Failed to write to the output\n");
      return -1;
   }

   //usleep(5000000);                  //give the Arduino a chance to respond

   unsigned char receive[100];      //declare a buffer for receiving data
   char buf[255];
   while(1){
  	//if((count = read(file, buf, 255)) < 0 ){
	//	perror("Failed to read from input\n");
		//return -1;
  	//}
	count = read(file,buf,255);
   	buf[count] = 0;
   	
	if(count > 0) printf("%s\n", buf, count);
	usleep(100000);	
   }
   //if ((count = read(file, (void*)receive, 100))<0){   //receive the data
     // perror("Failed to read from the input\n");
      //return -1;
  // }
   if (count==0) printf("There was no data available to read!\n");
   else {
      printf("The following was read in [%d]: %s\n",count,receive);
   }
   close(file);
   return 0;
}
