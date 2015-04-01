#ifndef SCREEN
#define SCREEN

typedef struct screen {
	/**
	* Function key descriptions.
	*/
	char[3] f1;
	char[3] f2;
	char[3] f3;
	/**
	* Called when the screen is refreshed(~1Hz), should return without
	* doing anything if nothing needs to be redrawn.
	*/
	void (*redraw)();
	/**
	* Called when a key is pressed.
	*/
	void (*keypress)();
};


#endif