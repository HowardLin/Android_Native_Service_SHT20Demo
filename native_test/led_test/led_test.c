/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * CYESS Co.,Ltd howard.lin@cyess.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define LED_ON  0x1
#define LED_OFF 0x0

int main()
{
	int dev_fd;
 	
	dev_fd = open("/dev/led",O_RDWR | O_NONBLOCK);

	if ( dev_fd == -1 ) {

		  printf("Cann't open file /dev/led\n");
		  exit(0);
 	}

	while(1){

		ioctl(dev_fd,LED_ON,0);
		usleep(100000);
		ioctl(dev_fd,LED_ON,1);
		usleep(100000);
		ioctl(dev_fd,LED_ON,2);
		usleep(100000);
		ioctl(dev_fd,LED_ON,3);
		usleep(100000);
		ioctl(dev_fd,LED_OFF,0);
		usleep(100000);
		ioctl(dev_fd,LED_OFF,1);
		usleep(100000);
		ioctl(dev_fd,LED_OFF,2);
		usleep(100000);
		ioctl(dev_fd,LED_OFF,3);
		usleep(100000);
	}
	return 0;
 }
