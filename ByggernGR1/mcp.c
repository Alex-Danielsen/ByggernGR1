/*
 * mcp.c
 *
 * Created: 04.10.2016 15:06:14
 *  Author: nikolasn
 */ 

#include "spi.h"



void mcp_init(){
	
	// Initialize SPI
	spi_init();
	
	// Data direction of Chip Select pin
	DDRB |= (1 << DDB4);
	// Set CS high
	PORTB |= (1 << DDB4);
	
	//Highly recommended to reset after power on
	mcp_reset();
	
	
	
}


char mcp_read(char address){
	PORTB &= !(1 << DDB4);
	spi_transmit(0x03);
	spi_transmit(address);
	spi_transmit(0x00);
	PORTB |= (1 << DDB4);
	return SPDR;
}

void mcp_write(char address, char data){
	PORTB &= !(1 << DDB4);
	spi_transmit(0x02);
	spi_transmit(address);
	spi_transmit(data);
	PORTB |= (1 << DDB4);
	
}

void mcp_requestSend(uint8_t transmitBuffers){ 
	//transmit buffers individual bits decides which buffers to use
	//For example, 111 uses all of the bits, while 000 uses none
	//order is TB2, TB1, TB0
	PORTB &= !(1 << DDB4);
	instruction = 0x80+transmitBuffers; //convert to correct instruction format: 10000(TB2)(TB1)(TB0) 
	spi_transmit(instruction);
	PORTB |= (1 << DDB4);
}

char mcp_readStatus(){
	PORTB &= !(1 << DDB4);
	spi_transmit(0xA0); //command to read status
	spi_transmit(0x00); //anything - just send something to get info back on the bus
	PORTB |= (1 << DDB4);
	return SPDR;
}

void mcp_bitModify(char address, char mask, char data){
	PORTB &= !(1 << DDB4);
	spi_transmit(0x05);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	PORTB |= (1 << DDB4); 
}

void mcp_reset(){
	PORTB &= !(1 << DDB4);
	spi_transmit(0xC0);
	PORTB |= (1 << DDB4);
}