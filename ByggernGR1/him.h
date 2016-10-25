/*
 * him.h
 *
 * Created: 13.09.2016 16:49:41
 *  Author: nikolasn
 */ 


#ifndef JOY_H_
#define JOY_H_

//---TYPEDEFS---
//Struct for joystick values:
typedef struct {
	uint8_t x;
	uint8_t y;
} him_joyPos;

//Enum for joystick direction:
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} him_joyDir;

//Enum for buttons on USB Board:
typedef enum {
	leftTouchButton,
	rightTouchButton,
	joyButton
} him_buttons;

//---FUNCTIONS---
void him_joyInit();

void him_joyCal();

uint8_t him_getButtonValue(him_buttons button);

him_joyPos him_getJoyPos();

him_joyDir him_getJoyDir();

int him_getLeftSlider();

int him_getRightSlider();

him_joyDir him_getPreviousDir();

void him_setPreviousDir(him_joyDir dir);

#endif /* JOY_H_ */