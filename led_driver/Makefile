# Copyright (C) 2008 The Android Open Source Project
#
# CYESS Co.,Ltd howard.lin@cyess.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

KERNELDIR ?= /home/cdpda/qt210_ics_kernel3.0.8_adk

PWD := $(shell pwd)

    obj-m := led.o

modules:
	 $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
install:
	 cp led.ko /home/cadtc/root_mkfs/lib/modules/2.6.35.7/kernel
clean:
	 rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions
.PHONY: modules modules_install clean
