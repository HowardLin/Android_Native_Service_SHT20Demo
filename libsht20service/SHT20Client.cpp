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
#define LOG_TAG "BpSHT20Service"
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


#include "SHT20Service.h"

namespace android {

class BpSHT20Service: public BpInterface<ISHT20Service>
{
public:
    BpSHT20Service(const sp<IBinder>& impl)
        : BpInterface<ISHT20Service>(impl)
    {
	LOGI("BpSHT20Service::BpSHT20Service()");
    }

    virtual int getHumidity(int* humidity)
    {
	LOGI("BpSHT20Service::getHumidity()");
        Parcel data, reply;
        data.writeInterfaceToken(ISHT20Service::getInterfaceDescriptor());
        status_t status = remote()->transact(BnSHT20Service::GET_HUMIDITY, data, &reply);
	if (status != NO_ERROR) {
            LOGD("getHumidity() could not contact remote: %d\n", status);
            return -1;
        }
	int32_t err = reply.readExceptionCode();
	*humidity = reply.readInt32();;
	if (err < 0) {
            LOGD("getHumidity() caught exception %d\n", err);
            return -1;
        }
        return 0;
    }

    virtual int getTemperature(int* temperature)
    {
        LOGI("BpSHT20Service::getTemperature()");
        Parcel data, reply;
        data.writeInterfaceToken(ISHT20Service::getInterfaceDescriptor());
        status_t status = remote()->transact(BnSHT20Service::GET_TEMPERATURE, data, &reply);
        if (status != NO_ERROR) {
            LOGD("getTemperature() could not contact remote: %d\n", status);
            return -1;
        }
        int32_t err = reply.readExceptionCode();
        *temperature = reply.readInt32();;
        if (err < 0) {
            LOGD("getTemperature() caught exception %d\n", err);
            return -1;
        }
        return 0;
    }

};

IMPLEMENT_META_INTERFACE(SHT20Service, "com.cyess.sht20demo.SHT20ServiceInterface");

};
