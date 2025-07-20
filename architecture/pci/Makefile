# All objects in obj-m will be a part of the kernel module
# hello.c to hello.o is done by makefile in kernel header
obj-m += smc6785_pci_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
