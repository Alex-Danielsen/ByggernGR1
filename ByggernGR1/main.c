/*
 * main.c
 *
 * Created: 30.08.2016 13:12:49
 *  Author: nikolasn
 */ 


//Include built in libs:
#include <avr/io.h>
#define F_CPU 4915200
#include <avr/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

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

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1


ISR(INT1_vect){
	printf("Interrupt occurred...");
	//volatile can_message recMessage = can_recieve();
	//printf("X: %d, Y: %d\n",(recMessage.data[0]), (recMessage.data[1]));
}


int main(void)
{	
	//Initialization:
	UART_init(MYUBRR);
	UART_parsePrint();
	mem_init();
	oled_init();
	menu_init();
	printf("Init complete\n");
	him_joyInit();
	can_init();
	
	/*  BEGIN INITIALIZATION OF INTERRUPTS */
	//Set to falling edge:
	MCUCR |= (1 << ISC11);
	//Enable interrupt on pin PD3:
	GICR |= (1 << INT1);
	//Enable interrupts - disable with cli()
	sei();
	/*  END INITIALIZATION OF INTERRUPTS */
	
	//BEGIN - CAN Transmit test:
	 can_message newMessage = {
		.id = 0x00,
		.length = 1,
		.data[0] = 23
	};
	
	can_send(&newMessage);
	_delay_ms(100);
	//volatile can_message recMessage = can_recieve();
	//printf("Data: %d\n",(recMessage.data[0]));
	//END - CAN Trasnmit test.
	
	while(1){
 		can_sendJoyPos(him_getJoyPos().x, him_getJoyPos().y);
 		_delay_ms(10);

	}	
}