/*

  SHT20Module Tester code
  Author:     Howard  Lin <cdpda.teacher@gmail.com>

  Connect VCC of the SHT20 Module to 3.3V or 5V (Auto detect)
  Connect GND to Ground
  Connect SCL to i2c clock
  Connect SDA to i2c data

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHT20_HUMIDITY_SYS_PATH    "/sys/bus/i2c/devices/1-0040/humidity"
#define SHT20_TEMPERATURE_SYS_PATH "/sys/bus/i2c/devices/1-0040/temperature"

#define TEMP_BUF_MAX_SIZE 4
#define HUM_BUF_MAX_SIZE  5



int main(int argc,char *argv[]){
	
	int sht20_temperature_fd,sht20_humidity_fd;
	int res;
	float sht20_temperature,sht20_humidity;
        char  temperature_buf[TEMP_BUF_MAX_SIZE],humidity_buf[HUM_BUF_MAX_SIZE];


	//Open Temperature sysfile
	sht20_temperature_fd = open (SHT20_TEMPERATURE_SYS_PATH,O_RDONLY);
	if(-1 == sht20_temperature_fd)
	{
		printf("ERROR:Can not detect sht20 module\n");
                return -1;
	}
	
	//Open humidity sysfile
	sht20_humidity_fd = open (SHT20_HUMIDITY_SYS_PATH,O_RDONLY);
        if(-1 == sht20_humidity_fd)
        {
                printf("ERROR:Can not detect sht20 module\n");
                return -1;
        }

	//Read sht20 temperature value
        res=read(sht20_temperature_fd,temperature_buf,TEMP_BUF_MAX_SIZE);
        if(res <=0)
        {
                printf("Can not read temperature value\n");
                return 1;
        }
        sht20_temperature=atof(temperature_buf);
        printf("Temperature = %.2f 'C \n",sht20_temperature/100);


	//Read sht20 humidity value
        res=read(sht20_humidity_fd,humidity_buf,HUM_BUF_MAX_SIZE);
        if(res <=0)
        {
                printf("Can not read humidity value\n");
                return 1;
        }
        sht20_humidity=atof(humidity_buf);
        printf("humidity = %.2f %RH \n",sht20_humidity/100);

	
	close(sht20_humidity);
	close(sht20_temperature);
	return 0;
}
