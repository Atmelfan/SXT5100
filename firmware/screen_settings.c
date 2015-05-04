#include "screen.h"
#include "gfx_driver.h"
#include <stdio.h>

uint8_t setting_index = 0;

struct {
	char* name;
	uint16_t deflt;
	uint16_t value;
}settings[] = {
	{"Year", 2015, 	2015},
	{"Month", 	0,	0},
	{"Day", 	1,	1},
	{"Hour", 	0,	0},
	{"Minute", 	0,	0},
	{"Second", 	0,	0}
};

void update_settings(keyboard_keys key){
	if (key == KEYBORD_F3)
	{
		set_screen(&screen_clock);
		return;
	}
}

void setup_settings(){
	gfx_drawstring(62 ,0,"SHF",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"ALT",GFX_UNDERLINE);
	gfx_drawstring(110,0,"RET",GFX_UNDERLINE);
	gfx_drawstring(0, 1, "todo", GFX_NONE);
}

void close_settings(){

}

screen screen_settings = {
	.update = &update_settings,
	.setup = &setup_settings,
	.close = &close_settings
};