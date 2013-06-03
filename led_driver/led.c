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


#include <linux/module.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <linux/device.h>
#include <asm/mach/map.h>

#define LED_ON 1
#define LED_OFF 0
static struct class *chrdev_sys_class = NULL;
static int led_major = 0;
static int led_gpios[] = {0,1,2,3 };
MODULE_AUTHOR("Howard Lin");
MODULE_LICENSE("Dual BSD/GPL");

#define GPH0CON (S5P_VA_GPIO + 0xC00)
#define GPH0DAT (S5P_VA_GPIO + 0xC04)
int led_open (struct inode *inode, struct file *filp)
{
 	printk (KERN_INFO "LED  device opened\n");
 	return 0;
}
ssize_t led_read(struct file *file, char __user *buff, size_t count, loff_t *offp)
{
	return 0;
}
ssize_t led_write(struct file *file, const char __user *buff, size_t count, loff_t *offp)
{
 	return 0;
}
 
static int led_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	int ret=0;
	int num;
	 switch (cmd)
	{
		case LED_ON:
		printk("%u\n",arg);
	        gpio_set_value(S5PV210_GPH0(led_gpios[arg]),1);
	        printk("GPH0DAT %x\n",readl(GPH0DAT));
		break;
		case LED_OFF:
		printk("%u\n",arg);
                gpio_set_value(S5PV210_GPH0(led_gpios[arg]),0);
	        printk("GPH0DAT %x\n",readl(GPH0DAT));
                break;
		default:
			break;
	}
 return 0;
}

static int led_release(struct inode *node, struct file *file)
{
  	printk (KERN_INFO "LED  device closed\n");
 	return 0;
}
static void led_setup_cdev(struct cdev *dev, int minor,
			   struct file_operations *fops)
{
     int err, devno = MKDEV(led_major, minor);
    
     cdev_init(dev, fops);
     dev->owner = THIS_MODULE;
     dev->ops = fops;
     err = cdev_add (dev, devno, 1);

    /*Create sys class*/
    chrdev_sys_class = class_create(THIS_MODULE,"led");
    if (IS_ERR(chrdev_sys_class)) {
    }
    /*Register sysfs*/
    device_create(chrdev_sys_class,
                  NULL,
                  MKDEV(led_major,0),
                  NULL,
                  "led");


    /* Fail gracefully if need be */
    if (err)
	printk (KERN_NOTICE "Error %d adding simple%d", err, minor);
}

static struct file_operations led_remap_ops = {
 	 .owner   = THIS_MODULE,
	 .open    = led_open,
	 .release = led_release,
	 .read    = led_read,
	 .write   = led_write,
	 .unlocked_ioctl   = led_ioctl, 
};
static struct cdev LedDevs;

static int led_init(void)
{
	int result,i;
	static void __iomem *pmic_addr;
	u32 GPH0;
	dev_t dev = MKDEV(led_major, 0);        
	if (led_major)
		  result = register_chrdev_region(dev, 1, "led"); 
	else {
		  result = alloc_chrdev_region(&dev, 0, 1, "led"); 
		  led_major = MAJOR(dev);
	}
	
	if (result < 0) {
		printk(KERN_WARNING "led: unable to get major %d\n", led_major);
		return result;
	}

	if (led_major == 0)
		led_major = result;
	
	printk("<1>GPIO_TESTdrv!\n");

	//Howard disable QT210 PMIC EINT pin, and set this pin to GPIO mode
	pmic_addr = ioremap(S5P_PA_SYSCON+0x0000E81C,8);
 	printk("PS_HOLD_CONTROL_OFFSET %x\n",readl(pmic_addr));
	writel(0x5000,pmic_addr);
        printk("PS_HOLD_CONTROL_OFFSET %x\n",readl(pmic_addr));

	for(i=0;i<ARRAY_SIZE(led_gpios);i++) {
		GPH0 = S5PV210_GPH0(led_gpios[i]);
		result = gpio_request(GPH0,"led");
		if(result) {
			printk(KERN_ERR "led: Error to gpio_request GPH%d\n",i);
			goto err_req;
		}
		s3c_gpio_setpull(GPH0,S3C_GPIO_PULL_DOWN);
		gpio_direction_output(GPH0,0);
		gpio_set_value(GPH0,0);
	        printk("GPH0CON %x\n",readl(GPH0CON));
	}

	printk("GPH0CON %x\n",readl(GPH0CON));
        printk("GPH0DAT %x\n",readl(GPH0DAT));
	led_setup_cdev(&LedDevs, 0, &led_remap_ops);
	printk("LED  device installed, with major %d\n", led_major);
	return 0;

err_req:
	while(--i>0)
		gpio_free(S5PV210_GPH0(led_gpios[i]));
	return result;
}

static void led_cleanup(void)
{
	int i;
	dev_t dev = MKDEV(led_major, 0);
	for(i=0;i<ARRAY_SIZE(led_gpios);i++) {
	gpio_free(S5PV210_GPH0(led_gpios[i]));
	}
	  /* unregister class */
        device_destroy(chrdev_sys_class, dev);
        class_destroy(chrdev_sys_class);
	cdev_del(&LedDevs);
	unregister_chrdev_region(MKDEV(led_major, 0), 1);
	printk("LED device uninstalled\n");
}

module_init(led_init);
module_exit(led_cleanup);
