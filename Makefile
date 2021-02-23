obj-m += packet_drop.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:	
	rm *.mod
	rm *.ko
	rm *.o
	rm *mod.c
	rm modules.order
	rm Module.symvers 

