/*
 * Copyright (C) 2011 CDPDA Howard Lin <cdpda.teacher@gmail.com>. All Rights Reserved.
 * SHT20 humidity and temperature sensor Driver for Linux 2.6
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/delay.h>

#define DRIVER_VERSION				"1.0"
#define SHT20_I2C_ADDRESS			0x0A

#define SHT20_TRIGGER_TEMPERATURE_MEAS		0xF3
#define SHT20_TRIGGER_HUMIDITY_MEAS		0xF5
#define SHT20_WRITE_USER_REG			0xE6
#define SHT20_READ_USER_REG			0xE7
#define SHR21_SOFT_RESET			0xFE

#define SHT20_MEAS_TIME_HUMIDITY		29 /* ms, max at 12 bit resolution */
#define SHT20_MEAS_TIME_TEMPERATURE		85 /* ms, max at 14 bit resolution */
#define SHT20_STATUS_BITS_MASK			0x03
#define SHT20_RESULT_TYPE			0x02
#define SHT20_TEMPERATURE_RESULT		0x00
#define SHT20_HUMIDITY_RESULT			0x02

static const unsigned short normal_i2c[] = { SHT20_I2C_ADDRESS, I2C_CLIENT_END };


/* Reads the serial number from the SHT20
 * For further documentation get the application note
 * "Electronic Identification Code" from sensirion.com/sht21
*/
static s32 sht20_get_id(struct i2c_client *client, u8 serial[8])
{
	s32 result;
	u8 serialA[8];
	u8 serialB[6];

	u8 command1[2] = {0xFA, 0x0F}; /* Read from memory location 1 */
	u8 command2[2] = {0xFC, 0xC9}; /* Read from memory location 2 */

	struct i2c_msg get_serial_number_msg[4] = {
		{
			.addr = client->addr,
			.flags = ~I2C_M_RD,
			.len = 2,
			.buf = command1,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = serialA,
		},
		{
			.addr = client->addr,
			.flags = ~I2C_M_RD,
			.len = 2,
			.buf = command2,
		},
		{
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 6,
			.buf = serialB,
		}
	};
  
	result = i2c_transfer(client->adapter, get_serial_number_msg, 4);

	// printk(KERN_INFO "%x %x %x %x %x %x %x %x", serialB[3], serialB[4], serialA[0], serialA[2], serialA[4], serialA[6], serialB[0], serialB[1]);
	
	serial[0] = serialB[3];
	serial[1] = serialB[4];
	serial[2] = serialA[0];
	serial[3] = serialA[2];
	serial[4] = serialA[4];
	serial[5] = serialA[6];
	serial[6] = serialB[0];
	serial[7] = serialB[1];
	
	return result;
}

static s32 sht20_read_temperature(struct i2c_client *client, u16 *temperature)
{
	s32 result = i2c_smbus_write_byte(client, SHT20_TRIGGER_TEMPERATURE_MEAS);
	if (result < 0)
		goto exit;

	msleep(SHT20_MEAS_TIME_TEMPERATURE);
	result = i2c_master_recv(client, (unsigned char*)temperature, sizeof(*temperature));
	if (result < 0)
		goto exit;

	*temperature = be16_to_cpu(*temperature);

	if ((*temperature & SHT20_RESULT_TYPE) != SHT20_TEMPERATURE_RESULT) {
		result = -ERESTARTSYS;	/* we requested a temperature measurement */
		goto exit;		/* but got a humidity result! */
	}

	*temperature = *temperature & ~SHT20_STATUS_BITS_MASK;	/* zero out status bits */
	*temperature = -4685 + ((17572 * *temperature) >> 16);

  exit:
	return result;
}

static s32 sht20_read_humidity(struct i2c_client *client, u16 *humidity)
{
	s32 result = i2c_smbus_write_byte(client, SHT20_TRIGGER_HUMIDITY_MEAS);
	if (result < 0)
		goto exit;

	msleep(SHT20_MEAS_TIME_HUMIDITY);
	result = i2c_master_recv(client, (unsigned char*)humidity, 2);
	if (result < 0)
		goto exit;

	*humidity = be16_to_cpu(*humidity);

	if ((*humidity & SHT20_RESULT_TYPE) != SHT20_HUMIDITY_RESULT) {
		result = -ERESTARTSYS;	/* we requested a humidity measurement */
		goto exit;		/* but got a temperature result! */
	}

	*humidity = *humidity & ~0x03;	/* zero out status bits */
	*humidity = -600 + ((*humidity * 12500) >> 16);

  exit:
	return result;
}


/* following are the sysfs callback functions */
static ssize_t show_temperature(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	s32 result;
	u16 temperature = 0;
	result = sht20_read_temperature(client, &temperature);
	if (result > 0) {
	//	return sprintf(buf, "%d (res: %x)\n", temperature, result);
		return sprintf(buf,"%d",temperature);
	}
	return result;
}
static DEVICE_ATTR(temperature, S_IRUGO, show_temperature, NULL);

static ssize_t show_humidity(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	s32 result;
	u16 humidity = 0;
	result = sht20_read_humidity(client, &humidity);
	if (result > 0) {
		//return sprintf(buf, "%d (res: %x)\n", humidity, result);
		return sprintf(buf,"%d",humidity);
	}
	return result;
}
static DEVICE_ATTR(humidity, S_IRUGO, show_humidity, NULL);


static struct attribute *sht20_attributes[] = {
	&dev_attr_temperature.attr,
	&dev_attr_humidity.attr,
	NULL
};

static const struct attribute_group sht20_attr_group = {
	.attrs = sht20_attributes,
};


static int sht20_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	/* Don't know how to identify this chip. Just assume it's there */
	strlcpy(info->type, "sht20", I2C_NAME_SIZE);
	return 0;
}


static int sht20_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err = 0;
	u8 serial[8];

	err = sht20_get_id(client, serial);
	if (err < 0) {
		dev_err(&client->dev, "probe failed!\n");
		goto exit;
	}
        dev_info(&client->dev, "SHT20 ver. %s found.\n",DRIVER_VERSION);
	printk(KERN_INFO "found SHT20 with serial %x %x %x %x %x %x %x %x\n",
			serial[0], serial[1], serial[2], serial[3],
			serial[4], serial[5], serial[6], serial[7]);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &sht20_attr_group);
	if (err) {
		dev_err(&client->dev, "registering with sysfs failed!\n");
		goto exit;
	}

	dev_info(&client->dev, "probe succeeded!\n");

  exit:
	return err;
}

static int sht20_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &sht20_attr_group);
	return 0;
}


static const struct i2c_device_id sht20_id[] = {
	{ "sht20", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, sht20_id);

static struct i2c_driver sht20_driver = {
	.driver = {
		.owner  = THIS_MODULE,
		.name	= "sht20",
	},
	.id_table	= sht20_id,
	.probe		= sht20_probe,
	.remove		= sht20_remove,

	.class		= I2C_CLASS_HWMON,
	.detect		= sht20_detect,
};

static int __init sht20_init(void)
{
	return i2c_add_driver(&sht20_driver);
}

static void __exit sht20_exit(void)
{
	i2c_del_driver(&sht20_driver);
}


MODULE_AUTHOR("Howard Lin <cdpda.teacher@gmail.com>");
MODULE_DESCRIPTION("SHT20 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");

module_init(sht20_init);
module_exit(sht20_exit);
