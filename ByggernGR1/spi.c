/*
 * spi.c
 *
 * Created: 04.10.2016 14:11:30
 *  Author: nikolasn
 */ 
#include <avr/io.h>

void spi_init(){
	// set data direction on SPI pins
	DDRB |= (1 << DDB5)|(1 << DDB7);
	// Enable SPI
	SPCR |= (1 << SPE);
	// Set mode to "Master"
	SPCR |= (1 << MSTR);
	// Set clock rate to fck/16
	SPCR |= (1 << SPR0);
	
}



void spi_transmit(char data){
	
	// Inputs data, start transmission
	SPDR = data;
	
	// Checks transmission complete flag
	while(!SPSR & (1 << SPIF)){}
	
}


