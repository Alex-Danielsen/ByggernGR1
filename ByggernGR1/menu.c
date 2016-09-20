/*
 * menu.c
 *
 * Created: 20.09.2016 16:30:19
 *  Author: nikolasn
 */ 

//Include libraries:
#include "string.h"
#include "oled.h"
#include "menu.h"

//Define global variables:
menu_t* currentMenu;
uint8_t menuIndex;

menu_t settingsMenu;

//Define menus:
menu_t* mainMenuChildren[] = {&settingsMenu};
menu_t mainMenu = {
	.name = "MainMenu",
	.parrent = NULL,
	.numOfChilds = 0,
	.child = mainMenuChildren,
};

menu_t* settingsMenuChildren[] = {};
menu_t settingsMenu = {
	.name = "Settings",
	.parrent = &mainMenu,
	.numOfChilds = 0,
	.child = settingsMenuChildren,
};

void menu_openMenu(menu_t* arg){
	oled_goHome();
	
	//Print menu name on line 1:
	if(arg->parrent == NULL){
		//oled_printString("ROOT/%s \n", arg->name);
		oled_printCharPtr("ROOT/");
		oled_printCharPtr(arg->name);
		oled_printNewLine();
	}
	else{
		//oled_printString("%d/%d \n", arg->parrent->name, arg->name);
		oled_printCharPtr(arg->parrent->name);
		oled_printCharPtr("/");
		oled_printCharPtr(arg->name);
		oled_printNewLine();
	}
	
	//Print sub menus:
	for(uint8_t i = 0; i < arg->numOfChilds; i++){
		//oled_printString("-%d \n", arg->child[i]->name);
		oled_printCharPtr(arg->child[i]->name);
		oled_printNewLine();
	}
	currentMenu = arg;
}


void menu_init(){
	//Load mainMenu:
	menu_openMenu(&mainMenu);
	
	//Set menuIndex to 0:
	menuIndex = 0;
	
	//Print indicator on screen:
	//menu_printIndicator(menuIndex);
}


void menu_printIndicator(uint8_t row){
	//Go to end of specified row:
	oled_goToPos(row, 115);
	//Print indicator (<) in this position:
	oled_printChar('<');
}