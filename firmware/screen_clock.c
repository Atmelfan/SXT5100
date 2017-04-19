#include "screen.h"
#include "gfx_driver.h"

void update_clock(keyboard_keys key){
	if (key == KEYBORD_F2){
		set_screen(&screen_console);
	}else if(key == KEYBORD_F1){
		set_screen(&screen_settings);
	}else if(key == KEYBORD_F3){
		set_screen(&screen_fs);
	}else if(key == KEYBORD_LEFT){

	}else if(key == KEYBORD_DELETE){
		
	}else if(key == KEYBORD_RIGHT){
		
	}
}

void setup_clock(){
	gfx_drawstring(62 ,0,"UTL",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"APL",GFX_UNDERLINE);
	gfx_drawstring(110,0,"FST",GFX_UNDERLINE);
	gfx_drawstring(0,7,"SERN IBN5100",GFX_CROSS);
	gfx_drawstring(128-7*6,7,"SXT5100",GFX_NONE);
}

void close_clock(){

}

screen screen_clock = {
	.update = &update_clock,
	.setup = &setup_clock,
	.close = &close_clock,
};