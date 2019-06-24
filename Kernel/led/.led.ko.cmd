cmd_/home/apla/led/led.ko := ld -EL -r  -T ./scripts/module-common.lds --build-id  -T ./arch/arm/kernel/module.lds -o /home/apla/led/led.ko /home/apla/led/led.o /home/apla/led/led.mod.o ;  true
