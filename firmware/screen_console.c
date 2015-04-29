#include "screen.h"
#include "gfx_driver.h"

char command[128];
uint8_t mode = 0;
uint8_t indx = 0;

void update_console(keyboard_keys key){
	if (key == KEYBORD_F3)
	{
		set_screen(&screen_clock);
		return;
	}else if (key == KEYBORD_F1)
	{
		if (mode == 1)
			mode = 0;
		else
			mode = 1;
	}else if (key == KEYBORD_F2)
	{
		if (mode == 2)
			mode = 0;
		else
			mode = 2;
	}else if (key == KEYBORD_LEFT)
	{
		if (indx > 0)
		{
			indx--;
		}
	}else if (key == KEYBORD_RIGHT)
	{
		if (indx < 21 && command[indx] != '\0')
		{
			indx++;
		}
	}else if (key == KEYBORD_DELETE)
	{
		command[indx] = ' ';
	}else{
		command[indx] = keyboard_tochar(mode, key);
		if (indx < 21)
		{
			indx++;
			command[indx] = ' ';
		}
	}
	switch(mode)
	{
		case 1:
			gfx_drawstring_cursor(0, 1, (char*)&command, indx, GFX_INVERT);
			break;
		case 2: 
			gfx_drawstring_cursor(0, 1, (char*)&command, indx, GFX_INVERT | GFX_UNDERLINE);
			break;
		default:
			gfx_drawstring_cursor(0, 1, (char*)&command, indx, GFX_UNDERLINE);
			break;
	}

}

void setup_console(){
	mode = 0;
	gfx_drawstring(62 ,0,"SHF",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"ALT",GFX_UNDERLINE);
	gfx_drawstring(110,0,"RET",GFX_UNDERLINE);
}

screen screen_console = {
	.update = &update_console,
	.setup = &setup_console,
};