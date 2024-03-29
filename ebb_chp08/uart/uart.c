#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

int main(int argc, char *argv[]){
   int file, count;
   if(argc!=2){
       printf("Please pass a message string to send, exiting!\n");
       return -2;
   }
   if ((file = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the device.\n");
      return -1;
   }
   struct termios options;
   tcgetattr(file, &options);
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

   // send the string plus the null character
      if ((count = write(file, argv[1], strlen(argv[1])+1))<0){
         perror("UART: Failed to write to the output.\n");
         return -1;
      }
   usleep(10000000);
   unsigned char receive[5];
   if ((count = read(file, (void*)receive, 5))<0){   //receive the data
         perror("Failed to read from the input\n");
         return -1;
   }
   if (count==0) printf("There was no data available to read!\n");
   else {
         printf("The following was read in [%d]: %s\n",count,receive);
   }
   // send the string plus the null character
   if ((count = write(file, argv[1], strlen(argv[1])+1))<0){
      perror("UART: Failed to write to the output.\n");
      return -1;
   }
   close(file);
   printf("Finished sending the message, exiting.\n");
   return 0;
}
