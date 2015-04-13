#ifndef SCREEN
#define SCREEN
#include "keyboard.h"

typedef struct screen {
	/**
	* Function key descriptions.
	*/
	char* f1;
	char* f2;
	char* f3;
	/**
	* 
	*/
	void (*update)();
};

#endif