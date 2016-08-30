/*
 * main.c
 *
 * Created: 30.08.2016 13:12:49
 *  Author: nikolasn
 */ 


//Include built in libs:
#include <avr/io.h>

//Include files:
#include "uart.h"

//Defined values
#define FOSC 4915200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main(void)
{	
	//Initialization:
	UART_init(MYUBRR);
	UART_parsePrint();
	
	//Code:
	
	
	
	
	
	//D
    while(1)
    {
        //TODO:: Please write your application code 
		UART_transmit('a');
    }
}

