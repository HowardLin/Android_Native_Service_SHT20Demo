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

#include <jni.h>
#include "com_cdpda_led_Linuxc.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define LED_TEST 3

#define DEVICE_BLTEST "/dev/led"

int fd;

JNIEXPORT jint JNICALL Java_com_cdpda_led_Linuxc_openled (JNIEnv *env, jclass mc)
{
	fd= open(DEVICE_BLTEST,O_RDONLY);
	return fd;
}

JNIEXPORT jint JNICALL Java_com_cdpda_led_Linuxc_closeled (JNIEnv *env, jclass mc)
{
 	close(fd);
	return 0;
}

JNIEXPORT jint JNICALL Java_com_cdpda_led_Linuxc_send (JNIEnv *env, jclass mc, jint a, jint b)
{
	ioctl(fd,a,b);
	return 0;
}

