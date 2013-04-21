/*
 * Copyright (C) 2010 The Android Open Source Project
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
#define LOG_TAG "SHT20Service"
#include <stdint.h>
#include <math.h>
#include <sys/types.h>

#include <utils/SortedVector.h>
#include <utils/KeyedVector.h>
#include <utils/threads.h>
#include <utils/Atomic.h>
#include <utils/Errors.h>
#include <utils/RefBase.h>
#include <utils/String16.h>
#include <binder/Binder.h>
#include <binder/IServiceManager.h>

#include <sht20.h>

#include "SHT20Service.h"

namespace android {

status_t BnSHT20Service::onTransact(
    uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    LOGI("BnSHT20Service::onTransact()");
    switch(code) {
        case CONNECT: {
            CHECK_INTERFACE(ISHT20Service, data, reply);
            return NO_ERROR;
        } break;
	case GET_HUMIDITY: {
		CHECK_INTERFACE(ISHT20Service, data, reply);
		int out = 0;
		size_t outSize = 0;
		int32_t ret = getHumidity(&out);
		reply->writeNoException();
		reply->writeInt32(out);
		reply->writeInt32(ret);
	    return NO_ERROR;
	}
	case GET_TEMPERATURE: {
                CHECK_INTERFACE(ISHT20Service, data, reply);
                int out = 0;
                size_t outSize = 0;
                int32_t ret = getTemperature(&out);
                reply->writeNoException();
                reply->writeInt32(out);
                reply->writeInt32(ret);
            return NO_ERROR;
	}
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

static struct sht20_device_t *sSHT20Device = NULL;

SHT20Service::SHT20Service()
{
    sht20_module_t* module;

    LOGI("SHT20server::SHT20Service(): Trying to get stub object");

    if (hw_get_module(HUMIDITY_HARDWARE_MODULE_ID, (const hw_module_t**)&module) == 0) {
        LOGI("SHT20server::SHT20Service(): stub found.");
        if (sht20_open(&module->common, &sSHT20Device) == 0) {
            LOGI("SHT20server::SHT20Service(): ops found.");
            return;
        }
    }

    LOGE("SHT20server:;SHT20Service(): failed to get SHT20 stub");
    return;
}

SHT20Service::~SHT20Service()
{
}

void SHT20Service::instantiate() {
     LOGI("SHT20Service::instantiate()");
     defaultServiceManager()->addService(
             String16("com.cyess.sht20demo.SHT20ServiceInterface"), new SHT20Service());
}

int SHT20Service::getHumidity(int* humidity)
{
    LOGI("SHT20Service::getHumidity()");
    if (sSHT20Device == NULL) {
        LOGI("SHT20Service::getHumidity(): sSHT20Device was not fetched correctly.");
        return -1;
    } else {
        int ret = sSHT20Device->get_humidity(sSHT20Device,&humidity);
	LOGI("SHT20Service::getHumidity() RAW:%d",*humidity);
    }
    return 0;
}

int SHT20Service::getTemperature(int* temperature)
{
    LOGI("SHT20Service::getTemperature()");
    if (sSHT20Device == NULL) {
        LOGI("SHT20Service::getTemperature(): sSHT20Device was not fetched correctly.");
        return -1;
    } else {
        int ret = sSHT20Device->get_temperature(sSHT20Device,&temperature);
        LOGI("SHT20Service::getTemperature() RAW:%d",*temperature);
    }
    return 0;
}



}; // namespace android


