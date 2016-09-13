/*
 * joy.h
 *
 * Created: 13.09.2016 16:49:41
 *  Author: nikolasn
 */ 


#ifndef JOY_H_
#define JOY_H_

//Struct for joystick values:
typedef struct {
	int8_t x;
	int8_t y;
} joy_pos;

//Enum for joystick direction:
typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} joy_dir;

//Enum for buttons on USB Board
typedef enum {
	LEFT_BUTTON,
	RIGHT_BUTTON,
	JOYSTICK_BUTTON
} joy_buttons;

void joy_init();

void joy_cal();

uint8_t joy_getButtonValue(joy_buttons button);

joy_pos joy_getPos();

joy_dir joy_getDir();

int joy_sliderLeft();
int joy_sliderRight();


#endif /* JOY_H_ */