###########################################################################################
#       Tester Name: sht20_test
#       Abstract: Makefile for sht20 humidity and temperature sensor linux tester code
#       Author: Howard Lin
#       Contact:cdpda.teacher@gmail.com
#########################################################################################


.PHONY:sht20_test
CC= arm-linux-gcc
SRC=sht20_test
CFLAGS = -lm --static

all:
	$(CC) $(SRC).c -o $(SRC) $(CFLAGS)

install:
	cp $(SRC)  /home/cdpda/root_mkfs/bin

clean:
	rm $(SRC)
