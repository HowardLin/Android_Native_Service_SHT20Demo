LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src) \
	src/com/cyess/sht20demo/SHT20ServiceInterface.aidl

LOCAL_PACKAGE_NAME := SHT20Demo

LOCAL_REQUIRED_MODULES := libsht20service
LOCAL_JNI_SHARED_LIBRARIES := libsht20service

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
