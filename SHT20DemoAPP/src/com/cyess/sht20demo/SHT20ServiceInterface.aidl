package com.cyess.sht20demo;

interface SHT20ServiceInterface {
	void  connect();
    int  getHumidity();
    int  getTemperature();
}
