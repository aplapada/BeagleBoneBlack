#!/bin/bash
echo "Arg 1: $1"

PWM_PATH=/sys/class/pwm/pwmchip4
echo "hei, $(whoami), hoplaa"
config-pin p9.14 pwm
config-pin -q p9.14
echo 0 >> "$PWM_PATH/export"
PWM4_PATH=$PWM_PATH/pwm-4:0/
echo 1000000000 >> "$PWM4_PATH/period"
cat "$PWM4_PATH/period"
echo 500000000 >> "$PWM4_PATH/duty_cycle"
cat "$PWM4_PATH/duty_cycle"
echo $1 >> "$PWM4_PATH/enable"
cat "$PWM4_PATH/enable"
