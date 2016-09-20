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
#include "oled.h"
#include "menu.h"

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
	oled_init();
	//menu_init();
	
	//Code:
	//char* yolo = "haha";
	//oled_printString("Yolo %i", 5);
	oled_printCharPtr("YOLOFISH");
	
	while(1)
	{
		
	}
	
	
	
	
}