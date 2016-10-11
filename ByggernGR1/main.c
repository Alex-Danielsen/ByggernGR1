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
#include "him.h"
#include "oled.h"
#include "menu.h"
#include "can.h"
#include "mcp.h"
#include "spi.h"

//Defined values
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main(void)
{	
	
	volatile can_message newMessage = {
		.id = 0x00, 
		.length = 4,
		.data = "hei",
	};
	//Initialization:
	UART_init(MYUBRR);
	UART_parsePrint();
	mem_init();
	oled_init();
	menu_init();
	printf("Init complete\n");
	him_joyInit();
	can_init();
	//spi_transmit(4);
	
	//test can transmit
	can_send(&newMessage);
	_delay_ms(10);
	volatile can_message recMessage = can_recieve();
	printf("%s\n",&(recMessage.data));
	
	//menu_displayJoyStats();
	while(1)
	{
		//menu_browseMenu();
		
		spi_transmit(0x55);
		_delay_ms(10);
		spi_transmit(0);
		_delay_ms(10);
		
		
		
		
	}
	
	
	
	
}