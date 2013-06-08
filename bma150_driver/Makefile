###########################################################################################
#       Module Name: bma150
#       Abstract: Makefile for bma150 g-sensor linux driver on Kernel series 3.0+
#	Author: Howard Lin
#	Contact:howard.lin@cyess.com
#########################################################################################

.PHONY: module install clean

KERNELDIR ?= /home/cdpda/qt210_ics_kernel3.0.8_adk
MODULE_NAME =bma150

obj-m := $(MODULE_NAME).o

PWD := $(shell pwd)

all: module

module:
	 $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	sudo cp $(MODULE_NAME).ko /home/cdpda/root_mkfs/lib/modules/2.6.35.7/kernel/
clean:
	 rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order Module.symvers
