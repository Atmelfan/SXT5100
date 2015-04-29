#include "screen.h"
#include "gfx_driver.h"

void update_clock(keyboard_keys key){
	if (key == KEYBORD_F2)
	{
		set_screen(&screen_console);
	}else if(key == KEYBORD_F3){
		PORTE.OUTTGL = (1 << 2);
	}
}

void setup_clock(){
	gfx_drawstring(62 ,0,"UTL",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"APL",GFX_UNDERLINE);
	gfx_drawstring(110,0,"BKL",GFX_UNDERLINE);
}

screen screen_clock = {
	.update = &update_clock,
	.setup = &setup_clock,
};