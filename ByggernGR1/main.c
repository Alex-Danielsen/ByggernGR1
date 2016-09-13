/*
 * main.c
 *
 * Created: 30.08.2016 13:12:49
 *  Author: nikolasn
 */ 


//Include built in libs:
#include <avr/io.h>
#include <avr/delay.h>

//Include files:
#include "uart.h"
#include "mem.h"
#include "adc.h"
#include "joy.h"

//Defined values
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main(void)
{	
	//Initialization:
	UART_init(MYUBRR);
	UART_parsePrint();
	mem_init();
	
	//Code:
	
	joy_cal();
	while(1){
		 
		 
		 
		//printf(" %d\n",joy_getDir());
		printf("Left: %d Right: %d Joy: %d\n",joy_getButtonValue(LEFT_BUTTON), joy_getButtonValue(RIGHT_BUTTON), joy_getButtonValue(JOYSTICK_BUTTON));
		printf("Left: %d Right: %d\n", joy_sliderLeft(), joy_sliderRight());
		_delay_ms(100);
	}
	
	
}