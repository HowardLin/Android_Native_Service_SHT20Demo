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

#include <hardware/hardware.h>

#include <fcntl.h>
#include <errno.h>

#include <cutils/log.h>
#include <cutils/atomic.h>

#define HUMIDITY_HARDWARE_MODULE_ID "sht20"

struct sht20_module_t {
   struct hw_module_t common;

   int (*init_sht20)(struct sht20_device_t *dev);
};


struct sht20_device_t {
   struct hw_device_t common;

   int fd;              /* file descriptor of sht20 */

   /* supporting control APIs go here */
   int (*get_humidity)(struct sht20_device_t *dev,int** val);
   int (*get_temperature)(struct sht20_device_t *dev,int** val);
};

static inline int sht20_open(const struct hw_module_t* module,
        struct sht20_device_t** device) {
    return module->methods->open(module,
            HUMIDITY_HARDWARE_MODULE_ID, (struct hw_device_t**)device);
}


