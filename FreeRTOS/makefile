objects = main.o croutine.o list.o queue.o tasks.o timers.o port.o serial.o heap_1.o
out: $(objects)
	avr-gcc -mmcu=atmega328p -o out main.o croutine.o list.o queue.o tasks.o timers.o port.o serial.o heap_1.o

main.o: main.c FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/semphr.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/queue.h /usr/local/Cellar/avr-gcc@9/9.3.0_2/avr/include/avr/io.h FreeRTOS/Source/include/extras/serial.h
	avr-gcc -mmcu=atmega328p -c main.c
croutine.o: FreeRTOS/Source/croutine.c FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/croutine.h FreeRTOS/Source/include/list.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/croutine.c
list.o: FreeRTOS/Source/list.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/list.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/list.c
queue.o: FreeRTOS/Source/queue.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/string.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/croutine.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/queue.c
tasks.o: FreeRTOS/Source/tasks.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdio.h /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/String.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/timers.h FreeRTOS/Source/include/StackMacros.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/tasks.c	
timers.o: FreeRTOS/Source/timers.c FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/queue.h FreeRTOS/Source/include/timers.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/timers.c
port.o: FreeRTOS/Source/portable/GCC/ATMega328/port.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h /usr/local/Cellar/avr-gcc@9/9.3.0_2/avr/include/avr/interrupt.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/portable/GCC/ATMega328/port.c
serial.o: FreeRTOS/Source/portable/GCC/ATMega328/extras/serial.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h /usr/local/Cellar/avr-gcc@9/9.3.0_2/avr/include/avr/interrupt.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/queue.h FreeRTOS/Source/include/task.h FreeRTOS/Source/include/extras/serial.h 
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/portable/GCC/ATMega328/extras/serial.c
heap_1.o: FreeRTOS/Source/portable/MemMang/heap_1.c /usr/local/Cellar/gcc/10.2.0_4/include/c++/10.2.0/tr1/stdlib.h FreeRTOS/Source/include/FreeRTOS.h FreeRTOS/Source/include/task.h
	avr-gcc -mmcu=atmega328p -c FreeRTOS/Source/portable/MemMang/heap_1.c

toHex: /usr/local/Cellar/avr-binutils/2.35.1_1/avr/bin/objcopy
	avr-objcopy -O ihex -j .text -j .data out out.hex
upload: /usr/local/Cellar/avrdude/6.3_1/bin/avrdude
	avrdude -C /usr/local/Cellar/avrdude/6.3_1/etc/avrdude.conf -v -p atmega328p -c stk500v1 -P /dev/tty.usbserial-DN02Z1QJ -U flash:w:/Users/chenshen/Desktop/FreeRTOS710-template-for-ATmega328P-master/out.hex -F

clean: rm out main.o croutine.o list.o queue.o tasks.o timers.o port.o serial.o heap_1.o
# this is a comment and clean should always be the last 
.PHONY: toHex upload clean
