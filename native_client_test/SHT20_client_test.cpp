#define LOG_TAG "SHT20ServiceTest"

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <utils/Log.h>

#include "../libsht20service/SHT20Service.h"

using namespace android;

int main(int argc, char *argv[])
{
	LOGI("SHT20Service client is now starting");

       sp<IServiceManager> sm = defaultServiceManager();
       sp<IBinder> binder;
       sp<ISHT20Service> shw;

        do {
                binder = sm->getService(String16("com.cyess.sht20demo.SHT20ServiceInterface"));
                if (binder != 0)
                        break;
                LOGW("SHT20Service not published, waiting...");
                usleep(500000); // 0.5 s
        } while(true);
	
	LOGI("SHT20Service client is now trying");

        shw =interface_cast<ISHT20Service>(binder);
	int humidity=0,temperature=0;
    	int32_t ret;
	ret = shw->getHumidity(&humidity);

	ret = shw->getTemperature(&temperature);
	
	printf("Humidity:%.2f\n",(double)humidity/100);
	printf("Temperature:%.2f\n",(double)temperature/100);

	LOGI("SHT20Service client is now exiting");

	return(0);
}

