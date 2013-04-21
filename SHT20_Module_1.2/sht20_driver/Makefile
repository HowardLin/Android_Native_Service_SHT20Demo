###########################################################################################
#       Module Name: sht20
#       Abstract: Makefile for sht20 humidity and temperature sensor linux driver on Kernel series 2.6
#	Author: Howard Lin
#	Contact:cdpda.teacher@gmail.com	
#########################################################################################

.PHONY: module install clean

KERNELDIR ?= /home/cyess/qt210_ics_kernel3.0.8_adk
MODULE_NAME =sht20

obj-m := $(MODULE_NAME).o

PWD := $(shell pwd)

all: module install

module:
	 $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	sudo cp $(MODULE_NAME).ko /home/cdpda/root_mkfs/lib/modules/2.6.35.7/kernel/
clean:
	 rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers
