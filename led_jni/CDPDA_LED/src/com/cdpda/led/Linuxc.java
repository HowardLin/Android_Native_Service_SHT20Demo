package com.cdpda.led;
import android.util.Log;

public class Linuxc {

	static {
        try {
            Log.i("JNI", "Trying to load libled.so");
            System.loadLibrary("led"); 
        }
        catch (UnsatisfiedLinkError ule) {
            Log.e("JNI", "WARNING: Could not load libled.so");
        }}
	public static native int openled();
	public static native int closeled();
	public static native int send(int led_num, int on_off);
}
