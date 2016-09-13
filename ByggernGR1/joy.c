/*
 * joy.c
 *
 * Created: 13.09.2016 16:49:52
 *  Author: nikolasn
 */ 

#include <avr/io.h>

#include "adc.h"
#include "joy.h"

uint8_t xInitPos, yInitPos;

void joy_init(){
	
	
}

void joy_cal(){
	xInitPos = adc_read(1); //x-axis @ channel 1.
	yInitPos = adc_read(2); //y-axis @ channel 2.
}

uint8_t joy_button(uint8_t button){
	
	
}

joy_pos joy_getPos(){
	joy_pos arg;
	
	arg.x = (adc_read(1) - xInitPos) * 100 / xInitPos;
	arg.y = (adc_read(2) - yInitPos) * 100 / yInitPos;
	
	return arg;
}


joy_dir joy_getDir(){
	joy_pos arg = joy_getPos();
	
	if( abs(arg.x) < 5 && abs(arg.y) < 5){return NEUTRAL;}
		
	if(abs(arg.x)>abs(arg.y)){
		if(arg.x > 0){return RIGHT;}
		else{return LEFT;}
	}
	
	else{
		if(arg.y > 0){return UP;}
		else{return DOWN;}
	}
}

uint8_t joy_getButtonValue(joy_buttons button) {
	if(button == LEFT_BUTTON) {
		return PINB & (1 << PINB2);
	}
	if(button == RIGHT_BUTTON) {
		return PINB &(1 << PINB3);
	}
	if(button == JOYSTICK_BUTTON) {
		return PINB & (1 << PINB0);
	}
}

int joy_sliderLeft() {
	return adc_read(2);
}
int joy_sliderRight() {
	return adc_read(3);
}