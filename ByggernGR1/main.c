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
	
	DDRA |= (1 << DDA0);
	//PORTA |= (1 << DDA0);
	char temp = 'a';
	//D
    while(1)
    {
        //TODO:: Please write your application code 
		//printf("Hello world!");
		
		temp = UART_recieve();
		switch(temp){
		
			case 'a':{
				PORTA |= (1 << DDA0);
				break;
			}
			case 'b':{
				PORTA &= !(1 << DDA0);
				break;
			}
			
		}
		
	}
}

