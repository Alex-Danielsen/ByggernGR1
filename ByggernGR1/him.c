/*
 * him.c
 *
 * Created: 13.09.2016 16:49:52
 *  Author: nikolasn
 */ 

#include <avr/io.h>

#include "adc.h"
#include "him.h"

uint8_t xInitPos, yInitPos;
him_joyDir previousJoyDir;

void him_joyInit(){
	him_joyCal();
	previousJoyDir = him_getJoyDir();
	
	
}

void him_joyCal(){
	xInitPos = adc_read(1); //x-axis @ channel 2.
	yInitPos = adc_read(2); //y-axis @ channel 1.
}


him_joyPos him_getJoyPos(){
	him_joyPos arg;
	
	arg.x = (adc_read(1));// - xInitPos) * 100 / xInitPos;
	arg.y = (adc_read(2));// - yInitPos) * 100 / yInitPos;
	
	return arg;
}


him_joyDir him_getJoyDir(){
	him_joyPos arg = him_getJoyPos();
	int8_t newArgY =  (arg.y - yInitPos) * 100 / yInitPos;
	int8_t newArgX = (arg.x - xInitPos) * 100 / xInitPos;
	if( abs(newArgX) < 30 && abs(newArgY) < 30){return NEUTRAL;}
	else if (abs(newArgX) < 95 && abs(newArgY) < 95 || 
			(abs(newArgX) > 80 && abs(newArgY) > 80))
			{return previousJoyDir;}
		
	if(abs(newArgX)>abs(newArgY)){
		if(arg.x > 0){return RIGHT;}
		else{return LEFT;}
	}
	
	else{
		if(newArgY > 0){return UP;}
		else{return DOWN;}
	}
}

uint8_t him_getButtonValue(him_buttons button) {
	if(button == leftTouchButton) {
		return PINB & (1 << PINB2);
	}
	if(button == rightTouchButton) {
		return PINB &(1 << PINB3);
	}
	if(button == joyButton) {
		return PINB & (1 << PINB0);
	}
}

int him_getLeftSlider() {
	return adc_read(3);
}
int him_getRightSlider() {
	return adc_read(4);
}

him_joyDir him_getPreviousDir(){
	return previousJoyDir;
}

void him_setPreviousDir(him_joyDir dir){
	previousJoyDir = dir;
}