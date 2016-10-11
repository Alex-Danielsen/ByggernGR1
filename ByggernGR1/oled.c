/*
 * oled.c
 *
 * Created: 20.09.2016 11:06:23
 *  Author: nikolasn
 */ 

//Include libraries:
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "font_4x6.h"

//Global variables for working row and column:
uint8_t currentRow, currentColumn;


//Define address and size for fonts:
//const unsigned char* font = (unsigned char*)font_4x6;
uint8_t charWidth = 4;






void oled_command(uint8_t c){
	//Define commandAdr to point at beginning of OLED's command address space:
	volatile char *commandAdr = (char *) 0x1000;
	
	//Write input command (c) to address space:
	*commandAdr = c;
}

void oled_data(uint8_t d){
	//Define dataAdr to point at beginning of OLED's data address space:
	volatile char *dataAdr = (char *) 0x1200;
	
	//Write input data (d) to address space:
	*dataAdr = d;
}

void oled_init(){
	//Enable ext ram:
	MCUCR |= (1 << SRE);
	//Mask out pins PC7-PC4:
	SFIOR |= (1 << XMM2);
	
	//Start of datasheet's recommended initialization:
	oled_command(0xAE); //Display off
	
	oled_command(0xA1); //Segment remap
	
	oled_command(0xDA); //Common pads hardware: alternative
	oled_command(0x12);
	
	oled_command(0xC8); //Common output scan direction: com63~com0
	
	oled_command(0xA8); //Multiplex ration mode: 63
	oled_command(0x3F);
	
	oled_command(0xD5); //Display divide ratio/oscillator frequency mode
	oled_command(0x80); 
	
	oled_command(0x81); //Set contrast value to 80.
	oled_command(0x50);
	
	oled_command(0xD9); //Set pre-charge period
	oled_command(0x21);
	
	oled_command(0x20); //Set memory addressing mode to page addressing mode.
	oled_command(0x00);
	
	oled_command(0xDB); //VCOM deselect level mode
	oled_command(0x30);
	
	oled_command(0xAD); //Master configuration
	oled_command(0x00);
	
	oled_command(0xA4); //Out follows RAM content
	
	oled_command(0xA6); //Set normal display
	
	oled_command(0xAF); //Display on
	//End of datasheet's recommended initialization.
	
	oled_command(0xB0); //Set row start address.
	
	oled_command(0x00); //Set lower column start address as low as possible.
	
	oled_command(0x10); //Set higher column start address as low as possible.
	
	oled_reset();
	oled_goHome();
	
}



void oled_goToRow(uint8_t row){
	oled_command(0xB0 + row);
	currentRow = row;
}

void oled_clearRow(uint8_t row){
	oled_goToRow(row);
	for(uint8_t i = 0; i < 128; i++){
		oled_data(0x00);
	}
}

void oled_clearRestOfRowGivenRow(uint8_t row) {
	oled_goToRow(row);
	for(uint8_t i = currentColumn; i < 128; i++){
		oled_data(0x00);
	}
}

void oled_clearRestOfRow() {
	for(uint8_t i = currentColumn; i < 128; i++){
		oled_data(0x00);
	}
}

void oled_goToColumn(uint8_t column){ 
	uint8_t msb = column & 0b11110000;
	msb /= 0b10000;
	uint8_t lsb = column & 0b00001111;
	oled_command(msb+0b00010000);
	oled_command(lsb);
	currentColumn = column;
}

void oled_goHome(){
	oled_goToRow(0);
	oled_goToColumn(0);
	currentColumn = 0;
	currentRow = 0;
}

void oled_reset(){
	for(uint8_t i = 0; i < 8; i++){
		oled_clearRow(i);
	}
		
}

void oled_goToPos(uint8_t row, uint8_t column){
	oled_goToColumn(column);
	oled_goToRow(row);
}

void oled_printNewLine(){
	for(uint8_t i = currentColumn; i < 128; i++){
		oled_data(0x00);
	}
	currentColumn = 0;
}

void oled_printChar(char character){
	if(character == '\n'){
		oled_printNewLine();
	}
	else{
		for(uint8_t i = 0; i < charWidth; i++){
			char byte = pgm_read_byte(&font_4x6[character-32][i]);
			oled_data(byte);
		}
		if ((currentColumn+charWidth)>127){
			currentColumn = 0;
		}
		else{
			currentColumn += charWidth;
		}
		
		
	}
}


static FILE oled_outf = FDEV_SETUP_STREAM(oled_printChar, NULL, _FDEV_SETUP_WRITE);

void oled_printf(const char* fmt, ...){
	va_list v;
	va_start(v, fmt);
	vfprintf(&oled_outf, fmt, v);
	va_end(v);
}

uint8_t oled_getCurrentRow(){
	return currentRow;
}

void oled_clearAll(){
	for(uint8_t i = 0; i < 8; i++){
		oled_clearRow(i);
	}
}


//I DONT THINK WE USE THESE?

#define BUFFERLENGTH 50

char buffer[BUFFERLENGTH];

void oled_printCharPtr(char* string)
{
	for(uint8_t i = 0; i < strlen(string); i++){
		oled_printChar(buffer[i]);
	}
}


void oled_printString(const char *format, ...){ //NOT WORKING

	va_list args;
	va_start(args, format);

	sprintf(buffer, format, args);
	
	va_end(args);
	
	for(uint8_t i = 0; i < strlen(buffer); i++){
		oled_printChar(buffer[i]);
	}
	
}