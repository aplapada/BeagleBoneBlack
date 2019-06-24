#!/bin/bash
echo "Arg 1: $1"
echo "Arg 2: $2"
echo "Arg 3: $3"

PWM_PATH=/sys/class/pwm/$1
echo "hei, $(whoami), hoplaa"
config-pin $2 pwm
config-pin -q $2
echo 0 >> "$PWM_PATH/export"

PWMN_PATH=$PWM_PATH/$3/

echo 1000000000 >> "$PWMN_PATH/period"
cat "$PWMN_PATH/period"

echo 500000000 >> "$PWMN_PATH/duty_cycle"
cat "$PWMN_PATH/duty_cycle"

echo 1 >> "$PWMN_PATH/enable"
cat "$PWMN_PATH/enable"
