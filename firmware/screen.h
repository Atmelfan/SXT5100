#ifndef SCREEN
#define SCREEN
#include "keyboard.h"

typedef struct {
	/**
	* Called to setup screen alternatives and stuff
	*/
	void (*setup)();
	/**
	* Called
	*/
	void (*update)(keyboard_keys key);
} screen;


extern void set_screen(screen* scr);

extern screen screen_clock;
extern screen screen_console;

#endif