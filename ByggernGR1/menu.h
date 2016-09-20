/*
 * menu.h
 *
 * Created: 20.09.2016 16:30:30
 *  Author: nikolasn
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef struct menu_t menu_t;

//Menu struct:
struct menu_t{
	menu_t* parrent;
	char name[20];
	uint8_t numOfChilds;
	menu_t** child;
};
//Functions:
void menu_init(); //Completed

void menu_openMenu(menu_t* arg); //Completed

void menu_printIndicator(uint8_t row); //Completed


#endif /* MENU_H_ */