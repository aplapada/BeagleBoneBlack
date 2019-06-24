import Adafruit_BBIO.UART as UART
import serial
UART.setup("UART1")
disp = serial.Serial (port = "/dev/ttyO1", baudrate=9600)

while True:
        if disp.isOpen():

                print "Serial is Open\n"
                message = raw_input("Enter your message:\n")

                disp.write(message)
                disp.write("\n")

                exit = raw_input("You want to exit or not Y\N:")

                while ((exit != 'Y') and (exit != 'N') and (exit != 'y') and (exit != 'n')):

                        print "Invalid Input!!!\n"

                        exit = raw_input("You want to exit or not Y\N:")


                if (exit == 'Y') or (exit == 'y'):
                        break

                else:
                        print "To be continue....\n"


print "Sorry!!! You not able to do communicate with device" 
disp.close()
