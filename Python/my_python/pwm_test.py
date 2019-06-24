import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.PWM as PWM
import time
#GPIO.setup("P9_14",PWM)
#PWM.start("P9_14", 1)
for i in range(0,101,1):
	PWM.start("P9_14",i)
	print("Duty Cycle: " + str(i) + "%")
	time.sleep(0.1)
#PWM.set_duty_cycle("P9_42", 25.5) 
#PWM.set_frequency("P9_42", 10)
#time.sleep(10)
PWM.stop("P9_42")
PWM.cleanup()

#set polarity to 1 on start:
#PWM.start("P9_42", 50, 2000, 1)
