/*
 * adc.c
 *
 * Created: 13.09.2016 13:59:30
 *  Author: nikolasn
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
INT0_vect(){
	//not in use
}

void adc_init(){
	//Enable INT0:
	GICR |= (1 << INT0);
	//Enable global interrupts:
	sei(); //To temporary pause interrupts do cli(), then sei() to reenable.
}



uint8_t adc_read(uint8_t chn){
	_delay_us(80);
	
	//Set start address for adc:
	volatile char *adcAddress = (char *) 0x1400;
	
	//If input is out of bounds, return 0:
	if(chn >4 || chn < 1) {
		return 0;
	}
	
	//Modify address to begin conversion:
	*adcAddress = 0x03 + chn ;
	_delay_us(80);
	
	//Return result of conversion from memory:
	return *adcAddress;
}