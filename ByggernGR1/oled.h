/*
 * oled.h
 *
 * Created: 20.09.2016 11:06:33
 *  Author: nikolasn
 */ 


#ifndef OLED_H_
#define OLED_H_

//---LIBRARIES---
#include <stdint.h>

//---FUNCTIONS---
void oled_init();

void oled_reset();

void oled_goHome();

void oled_goToRow(uint8_t row);

void oled_goToColumn(uint8_t column);

void oled_clearRow(uint8_t Row);

void oled_goToPos(uint8_t row, uint8_t column);

void oled_printChar(char character);

void oled_command(uint8_t c);

void oled_data(uint8_t d);

void oled_printNewLine();

void oled_printf(const char* fmt, ...);

uint8_t oled_getCurrentRow();

void oled_clearAll();

void oled_clearRestOfRowGivenRow(uint8_t row);

void oled_clearRestOfRow();

void oled_printCharPtr(char* string); //NOT IN USE?

void oled_printString(const char *format, ...); //NOT IN USE?

#endif /* OLED_H_ */