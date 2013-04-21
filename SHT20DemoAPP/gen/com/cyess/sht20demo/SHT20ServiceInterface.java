/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: Z:\\NAS2\\SHT20Demo\\src\\com\\cyess\\sht20demo\\SHT20ServiceInterface.aidl
 */
package com.cyess.sht20demo;
public interface SHT20ServiceInterface extends android.os.IInterface
{
/** Local-side IPC implementation stub class. */
public static abstract class Stub extends android.os.Binder implements com.cyess.sht20demo.SHT20ServiceInterface
{
private static final java.lang.String DESCRIPTOR = "com.cyess.sht20demo.SHT20ServiceInterface";
/** Construct the stub at attach it to the interface. */
public Stub()
{
this.attachInterface(this, DESCRIPTOR);
}
/**
 * Cast an IBinder object into an com.cyess.sht20demo.SHT20ServiceInterface interface,
 * generating a proxy if needed.
 */
public static com.cyess.sht20demo.SHT20ServiceInterface asInterface(android.os.IBinder obj)
{
if ((obj==null)) {
return null;
}
android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
if (((iin!=null)&&(iin instanceof com.cyess.sht20demo.SHT20ServiceInterface))) {
return ((com.cyess.sht20demo.SHT20ServiceInterface)iin);
}
return new com.cyess.sht20demo.SHT20ServiceInterface.Stub.Proxy(obj);
}
@Override public android.os.IBinder asBinder()
{
return this;
}
@Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
{
switch (code)
{
case INTERFACE_TRANSACTION:
{
reply.writeString(DESCRIPTOR);
return true;
}
case TRANSACTION_connect:
{
data.enforceInterface(DESCRIPTOR);
this.connect();
reply.writeNoException();
return true;
}
case TRANSACTION_getHumidity:
{
data.enforceInterface(DESCRIPTOR);
int _result = this.getHumidity();
reply.writeNoException();
reply.writeInt(_result);
return true;
}
case TRANSACTION_getTemperature:
{
data.enforceInterface(DESCRIPTOR);
int _result = this.getTemperature();
reply.writeNoException();
reply.writeInt(_result);
return true;
}
}
return super.onTransact(code, data, reply, flags);
}
private static class Proxy implements com.cyess.sht20demo.SHT20ServiceInterface
{
private android.os.IBinder mRemote;
Proxy(android.os.IBinder remote)
{
mRemote = remote;
}
@Override public android.os.IBinder asBinder()
{
return mRemote;
}
public java.lang.String getInterfaceDescriptor()
{
return DESCRIPTOR;
}
@Override public void connect() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_connect, _data, _reply, 0);
_reply.readException();
}
finally {
_reply.recycle();
_data.recycle();
}
}
@Override public int getHumidity() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getHumidity, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
@Override public int getTemperature() throws android.os.RemoteException
{
android.os.Parcel _data = android.os.Parcel.obtain();
android.os.Parcel _reply = android.os.Parcel.obtain();
int _result;
try {
_data.writeInterfaceToken(DESCRIPTOR);
mRemote.transact(Stub.TRANSACTION_getTemperature, _data, _reply, 0);
_reply.readException();
_result = _reply.readInt();
}
finally {
_reply.recycle();
_data.recycle();
}
return _result;
}
}
static final int TRANSACTION_connect = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
static final int TRANSACTION_getHumidity = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
static final int TRANSACTION_getTemperature = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
}
public void connect() throws android.os.RemoteException;
public int getHumidity() throws android.os.RemoteException;
public int getTemperature() throws android.os.RemoteException;
}
