/*
 * menu.c
 *
 * Created: 20.09.2016 16:30:19
 *  Author: nikolasn
 */ 

//INCLUDES:
#include "string.h"
#include "oled.h"
#include "menu.h"
#include "him.h"
#include <util/delay.h>

//FUNCTIONS:
void menu_displayJoyStats(void);

//VARIABLES:
menu_t* currentMenu;
//Menu stack
//const int MAXSIZE = 8; //MAXSIZE must equal value in menuIndex[...]
#define MAXSIZE 8
uint8_t menuIndex[MAXSIZE];
int8_t  menuTop= -1;

uint8_t isEmpty(){
	if(menuTop== -1) {return -1;}
	else return 0;
}

uint8_t isFull(){
	if(menuTop == MAXSIZE) return 1;
	else return 0;
}

uint8_t menuPop() {
	int data;
	
	if(!isEmpty()) {
		data = menuIndex[menuTop];
		menuTop = menuTop-1;
		return data;
	}
	else{
		printf("Stack is empty! Cannot retrieve data \n");
	}
	
}

uint8_t menuPeek() {
	return menuIndex[menuTop];
}

void menuPush(uint8_t data) {
	if(!isFull()) {
		menuTop = menuTop + 1;
		menuIndex[menuTop] = data;
	}
	else{
		printf("Menu index stack is full, please use less sub folders.\n");
	}
}

	

//MENUS:
menu_t settingsMenu;
menu_t calibrateMenu;
menu_t calibrateMoreMenu;
menu_t testMenu;
menu_t Program;

//Main menu:
menu_t* mainMenuChildren[] = {&settingsMenu, &calibrateMenu, &testMenu};
menu_t mainMenu = {
	.name = "MainMenu",
	.parent = NULL,
	.numOfChildren = 3,
	.child = mainMenuChildren,
};

//Settings menu:
menu_t* settingsMenuChildren[] = {NULL};
menu_t settingsMenu = {
	.name = "Settings",
	.parent = &mainMenu,
	.numOfChildren = 0,
	.child = settingsMenuChildren,
};

//Calibrate menu:
menu_t* calibrateMenuChildren[] = {&calibrateMoreMenu};
menu_t calibrateMenu = {
	.name = "Calibrate",
	.parent = &mainMenu,
	.numOfChildren = 1,
	.child = calibrateMenuChildren,
};

//Calibrate More menu:
menu_t calibrateMoreMenu = {
	.name = "Calibrate More",
	.parent = &calibrateMenu,
	.child = NULL,
};

//Test menu:
menu_t testMenu = {
	.name = "Test",
	.parent = &mainMenu,
	.child = NULL,
	.action = menu_displayJoyStats,
};



//Program:

menu_t Program = {
	.name = "Test",
	.parent = &settingsMenu,
	.action = menu_displayJoyStats,
};



//FUNCTIONS:
void menu_init(){
	//Load mainMenu:
	menu_openMenu(&mainMenu);
	
	//Set menuIndex to 1:
	menuPush(1);
	
	//Print indicator on screen:
	menu_printIndicator(menuPeek());
}

void menu_openMenu(menu_t* arg){
	oled_clearAll();
	oled_goHome();
	
	//Print menu name on line 1:
	if(arg->parent == NULL){
		oled_printf("ROOT/%s \n", arg->name);
	}
	else{
		oled_printf("%s/%s \n", arg->parent->name, arg->name);
	}
	//Print sub menus:
	for(uint8_t i = 0; i < arg->numOfChildren; i++){
		if(arg->child[i]->child != NULL) {
			oled_printf("+ %s \n", arg->child[i]->name);
		}
		else {
			oled_printf("  %s \n", arg->child[i]->name);
		}
		
	}
	currentMenu = arg;
	//menuIndex = 1;
}

void menu_printIndicator(uint8_t row){
	//Remove previous indicator:
	oled_goToPos(oled_getCurrentRow(), 115);
	oled_printChar(' ');
	//Go to end of specified row:
	oled_goToPos(row, 115);
	//Print indicator (<) in this position:
	oled_printChar('<');
}

void menu_browseMenu(){
	him_joyDir joyDir = him_getJoyDir();
	if(joyDir != him_getPreviousDir()){
		//printf("Current Menu: ");
		if(joyDir == DOWN && menuPeek() < currentMenu->numOfChildren){
			uint8_t curr = menuPop();
			menuPush(curr+1);
			printf("down\n");
		}
		if(joyDir == UP && menuPeek() > 1){
			uint8_t curr = menuPop();
			menuPush(curr-1);
			printf("up\n");
		}
		if(joyDir == RIGHT){
			if(currentMenu->child[menuPeek()-1]->child != NULL && currentMenu->child[menuPeek()-1]->numOfChildren != 0){
				menu_openMenu(currentMenu->child[menuPeek()-1]);
				menuPush(1);
			}
			else if(currentMenu->child[menuPeek()-1]->action != NULL){
				currentMenu->child[menuPeek()-1]->action();
			}
		}
		if(joyDir == LEFT && (currentMenu->parent) != NULL){
			//menuIndex = currentMenu->parent
			menuPop();
			menu_openMenu(currentMenu->parent);
		}
		him_setPreviousDir(joyDir);
	}
		
	menu_printIndicator(menuPeek());
}

void menu_displayJoyStats(){
	him_joyPos arg;
	oled_clearAll();
	oled_goHome();
	while(1){
		arg = him_getJoyPos();
		oled_printf("X: %d, Y: %d",arg.x, arg.y);
		oled_clearRestOfRow();
		_delay_ms(10);
		oled_goHome();
		if(him_getButtonValue(joyButton)) {
			menu_openMenu(currentMenu);
			break;
		}
	}
}
