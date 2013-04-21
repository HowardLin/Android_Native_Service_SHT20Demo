package com.cyess.sht20demo;


import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.os.IBinder;
import android.os.Message;
import android.os.RemoteException;
import android.os.Handler;
import android.os.ServiceManager;

import android.util.Log;

public class SHT20Activity extends Activity {
	
	private static final String LOG_TAG = "SHT20DemoAPP";
  	private SHT20ServiceInterface mSHT20Service;	  
  	private Long startTime;
	public static final int GET_TEMPERATURE	= 1;
	public static final int GET_HUMIDITY=2;
  	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_sht20);

		startTime = System.currentTimeMillis();
		handler.removeCallbacks(updateTimer);
		handler.postDelayed(updateTimer, 1500);
	}
	
	private Runnable updateTimer = new Runnable() {
        public void run() {
        	Message ledUpdate = Message.obtain(handler, GET_TEMPERATURE);
    		
    		if(handler != null) {
    			handler.sendMessage(ledUpdate);
    		}
        		handler.postDelayed(this, 1200);
        }
    };
     	@Override
	public void onPause() {
                handler.removeCallbacks(updateTimer);
	    	super.onPause();
		finish();
	 }
    private Handler handler = new Handler() {
    	@Override
    	public void handleMessage(Message msg) {
    		TextView view;
    		
			switch(msg.what)
			{				
				case GET_TEMPERATURE:
				
				int humidity;
				int temperature;

		                IBinder helloworld = ServiceManager.getService("com.cyess.sht20demo.SHT20ServiceInterface");
		                if(helloworld != null) {
		                    Log.e(LOG_TAG, "hello "+helloworld.toString());
		                } else {
		                    Log.e(LOG_TAG, "hello service not found ");
		                }
				mSHT20Service = SHT20ServiceInterface.Stub.asInterface(helloworld);
				try{
					 humidity=mSHT20Service.getHumidity();
					 Log.e(LOG_TAG,String.valueOf((float)humidity/100));
				} catch(RemoteException e) {
					 Log.e(LOG_TAG, "Error");
		                    return;
				}
				try{
					 temperature=mSHT20Service.getTemperature();
					 Log.e(LOG_TAG,String.valueOf((float)temperature/100));
				} catch(RemoteException e) {
					 Log.e(LOG_TAG, "Error");
		                    return;
				}

														
				ProgressBar progressBar = (ProgressBar) findViewById(R.id.progressBarTemperature);
				view = (TextView)findViewById(R.id.textTemperature);								
							
				progressBar.setProgress((int)temperature/100);	
				view.setText("Temperature:" + Float.toString((float)temperature/100));
				view.setTextColor(getResources().getColor(R.color.orange));

				progressBar = (ProgressBar) findViewById(R.id.progressBarHumidity);
                                view = (TextView)findViewById(R.id.textHumidity);

                                progressBar.setProgress((int)humidity/100);
                                view.setText("Humidity:" + Float.toString((float)humidity/100));
                                view.setTextColor(getResources().getColor(R.color.orange));

						
				break;
			default:
				break;
			}	//switch
    	} //handleMessage
    }; //handler


}
