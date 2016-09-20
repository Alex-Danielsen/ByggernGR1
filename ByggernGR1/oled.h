/*
 * oled.h
 *
 * Created: 20.09.2016 11:06:33
 *  Author: nikolasn
 */ 


#ifndef OLED_H_
#define OLED_H_

void oled_init(); //Completed

void oled_reset(); //Completed

void oled_goHome(); //Completed

void oled_goToRow(uint8_t row); //Completed

void oled_goToColumn(uint8_t column); //Completed

void oled_clearRow(uint8_t Row); //Completed

void oled_goToPos(uint8_t row, uint8_t column);

void oled_printChar(char character); //Completed

void oled_printString(char string[]); //Completed

void oled_command(uint8_t c); //Completed

void oled_data(uint8_t d); //Completed

void oled_printNewLine(); //Completed









#endif /* OLED_H_ */