/*
 * Copyright (C) 2008 The Android Open Source Project
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

#define LOG_TAG "HumiditySHT20"
#include <cutils/log.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <include/sht20.h>
#include <stdlib.h>
 
#if 1
#define SHT20_HUMIDITY_SYS_PATH    "/sys/bus/i2c/devices/1-0040/humidity"
#define SHT20_TEMPERATURE_SYS_PATH "/sys/bus/i2c/devices/1-0040/temperature"

#define TEMP_BUF_MAX_SIZE 4
#define HUM_BUF_MAX_SIZE  5


int get_humidity(struct sht20_device_t *dev,int** val)
{
	LOGI("Get humidity");
	int sht20_humidity_fd;
	int res;
	char humidity_buf[HUM_BUF_MAX_SIZE];
	 //Open humidity sysfile
        sht20_humidity_fd = open (SHT20_HUMIDITY_SYS_PATH,O_RDONLY);
        if(-1 == sht20_humidity_fd)
        {
                printf("ERROR:Can not detect sht20 module\n");
                return -1;
        }
	 //Read sht20 humidity value
        res=read(sht20_humidity_fd,humidity_buf,4);
        if(res <=0)
        {
                printf("Can not read humidity value\n");
                return 1;
        }
	**val = atoi(humidity_buf);
	close(sht20_humidity_fd);
	return 0;
}

int get_temperature(struct sht20_device_t *dev,int** val)
{
        LOGI("Get Temperature");
        int sht20_temperature_fd;
        int res;
        char temperature_buf[TEMP_BUF_MAX_SIZE];
	
	//Open Temperature sysfile
        sht20_temperature_fd = open (SHT20_TEMPERATURE_SYS_PATH,O_RDONLY);
        if(-1 == sht20_temperature_fd)
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

        **val = atoi(temperature_buf);
        close(sht20_temperature_fd);
        return 0;
}

static int close_sht20(struct cht20_device_t *dev)
{
    LOGI("Close SHT20");
    if (dev)
        free(dev);
    return 0;
}

static int open_sht20(const struct hw_module_t *module, char const *name,
                        struct hw_device_t **device)
{
    LOGI("Open SHT20 Humidity HAL");

    struct  sht20_device_t *dev = malloc(sizeof(struct sht20_device_t));
    memset(dev, 0, sizeof(*dev));

    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = 0;
    dev->common.module = (struct hw_module_t *)module;
    dev->common.close = (int (*)(struct hw_device_t *))close_sht20;
    dev->get_humidity = get_humidity;
    dev->get_temperature = get_temperature;

    *device = (struct hw_device_t *)dev;

    return 0;
}

static struct hw_module_methods_t sht20_module_methods = {
    .open =  open_sht20,
};

const struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = HARDWARE_MODULE_TAG,
    .version_major = 1,
    .version_minor = 0,
    .id = HUMIDITY_HARDWARE_MODULE_ID,
    .name = "SHT20 Humidity Module",
    .author = "CYESS Co,. Ltd.",
    .methods = &sht20_module_methods,
};

#endif
