/*
 * menu.h
 *
 * Created: 20.09.2016 16:30:30
 *  Author: nikolasn
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef void (*menuAction)(void);

//STRUCTS/ENUMS:
typedef struct menu_t menu_t;
struct menu_t{
	menu_t* parent;
	char name[20];
	uint8_t numOfChildren;
	menu_t** child;
	menuAction action;
};

//FUNCTIONS::
void menu_init();

void menu_openMenu(menu_t* arg);

void menu_printIndicator(uint8_t row);

void menu_displayJoyStats();

#endif /* MENU_H_ */