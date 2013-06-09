package com.cdpda.led;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class cdpda_led extends Activity {
	 private Button mButton1; 
	    private Button mButton2;
	    private Button mButton3;
	    
	    public  int state1 = 0,state2=0;      
	    public  int led_on = 1; 
		public  int led_off = 0;
		public  int fd = 0;
		private Button.OnClickListener button1_listener= new Button.OnClickListener()
		{
			public void onClick(View v)
	        {
	      	  if(state1==0)
	      	  {
	      		  mButton1.setText("Close LED 3");
	      		  state1=1;
	      		 Linuxc.send(led_on, 0);
	      	  }
	      	  else if (state1==1)
	      	  {
	      		  mButton1.setText("Light Led 3");
	      		  state1=0;
	      		  Linuxc.send(led_off, 0);
	      	  }
	        }
		};
		private Button.OnClickListener button2_listener= new Button.OnClickListener(){
			  public void onClick(View v)
	          {
	        	  if(state2==0)
	        	  {
	        		  mButton2.setText("Close LED 4");
	        		  state2=1;
	        		  Linuxc.send(led_on, 1);
	              }
	        	  else if(state2==1)
	        	  {
	        		  mButton2.setText("Light LED 4");
	        		  state2=0;
	        		  Linuxc.send(led_off, 1);
	        	  }
	            }
		};
		private Button.OnClickListener button3_listener= new Button.OnClickListener(){
			 public void onClick(View v)
	         {
	       	   Linuxc.closeled();
	       	   finish();
	           }
		};
	
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mButton1 =(Button) findViewById(R.id.myButton1);
        mButton2 =(Button) findViewById(R.id.myButton2);
        mButton3 =(Button) findViewById(R.id.myButton3);
       
     
        
      fd = Linuxc.openled();
     // fd=1;
        if (fd < 0){
        	setTitle("open device false!");
        	finish(); 
        }
        else {
        	setTitle("open device success!");
        }
        
        mButton1.setOnClickListener(button1_listener);
        mButton2.setOnClickListener(button2_listener);
        mButton3.setOnClickListener(button3_listener);
       
    }
}