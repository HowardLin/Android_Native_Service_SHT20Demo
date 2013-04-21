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

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

namespace android {

class ISHT20Service : public IInterface
{
public:
	 DECLARE_META_INTERFACE(SHT20Service);

   enum {
        CONNECT = IBinder::FIRST_CALL_TRANSACTION,
        GET_HUMIDITY,
	GET_TEMPERATURE
   };
    virtual int getHumidity(int* humidity) =0;
    virtual int getTemperature(int* temperature) =0;
};


class BnSHT20Service: public BnInterface<ISHT20Service>
{
public:
    virtual status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
};

class SHT20Service : public BnSHT20Service
{
public:
    static void instantiate();
    virtual int getHumidity(int* humidity);
    virtual int getTemperature(int* temperature);

private:
    SHT20Service();
    virtual ~SHT20Service();
};   
 
}   
