#!/bin/bash
echo "Args should be: pwmchipN, pwm-X:Y, on/off"
echo "N range [0..7] | X range: [0..7] | Y range: [0..1]"
echo "Args: $1 $2 $3"


PWM_PATH=/sys/class/pwm/$1/$2

if [ "$3" == "on" ]; then
	echo 1 >> "$PWM_PATH/enable"
elif [ "$3" == "off" ]; then
	echo 0 >> "$PWM_PATH/enable"
fi

