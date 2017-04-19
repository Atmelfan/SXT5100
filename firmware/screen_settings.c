#include "screen.h"
#include "gfx_driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

uint8_t setting_index = 0;
uint8_t selected = 0;
struct tm *info;


uint16_t bkl_onchange(uint16_t current){
	PORTE.OUTTGL = (1 << 2);
	return !((PORTE.IN & (1 << 2)) != 0);
}

struct setting
{
	char* name;
	char* (*disp_value)();
	void (*on_edit)();
	void (*on_save)();
	void (*on_key)();	
};


struct {
	char* name;
	uint16_t deflt;
	uint16_t value;
	uint16_t (*onchange)(uint16_t);
}settings[] = {
	{"Year", 	 2015, 	2015,	NULL},
	{"Month", 		0,	0,		NULL},
	{"Day", 		1,	1,		NULL},
	{"Hour", 		0,	0,		NULL},
	{"Minute", 		0,	0,		NULL},
	{"Second", 		0,	0,		NULL},
	{"Backlight", 	0,	0,		&bkl_onchange},
};

#define NUM_SETTINGS 7
char val[6] = {0};

void draw(){


	uint8_t style = GFX_NONE;
	void cell(){
		style = GFX_NONE;
	}
	for (int i = 0; i < NUM_SETTINGS; ++i)
	{
		
		itoa(settings[i].value, (char*)&val, 10);
		if(i == setting_index){
			style = selected ? GFX_INVERT : GFX_UNDERLINE;
		}else{
			
			cell();
		}
		gfx_drawstring(0,1+i,settings[i].name, style);
		gfx_drawstring(100,1+i,(char*)&val, style);
	}
}

void update_settings(keyboard_keys key){
	

	if (key == KEYBORD_F3)
	{
		setting_index = 0;
		selected = 0;
		set_screen(&screen_clock);
		return;
	}if (key == KEYBORD_F2)
	{
		setting_index = 0;
		selected = 0;
		set_screen(&screen_clock);
		info->tm_year = settings[0].value - 1900;
		info->tm_mon = settings[1].value -1;
		info->tm_mday = settings[2].value;
		info->tm_hour = settings[3].value;
		info->tm_min = settings[4].value;
		info->tm_sec = settings[5].value;
		set_system_time(mktime(info));
		return;
	}
	else if(key == KEYBORD_DELETE)
	{
		selected = !selected;
	}

	if(!selected)
	{

		if (key == KEYBORD_LEFT && setting_index > 0)
		{
			setting_index--;
		}
		else if (key == KEYBORD_RIGHT && setting_index < NUM_SETTINGS-1)
		{
			setting_index++;
		}
	}else{
		if (key == KEYBORD_LEFT)
		{
			if(settings[setting_index].onchange != NULL){
				settings[setting_index].value = settings[setting_index].onchange(settings[setting_index].value);
			}else
				settings[setting_index].value--;
		}
		else if (key == KEYBORD_RIGHT)
		{
			if(settings[setting_index].onchange != NULL){
				settings[setting_index].value = settings[setting_index].onchange(settings[setting_index].value);
			}else
				settings[setting_index].value++;
		}
		else if(key == KEYBORD_F1)
		{
			settings[setting_index].value = settings[setting_index].deflt;
		}
	}
	draw();
}

void setup_settings(){
	gfx_drawstring(62 ,0,"RST",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"SET",GFX_UNDERLINE);
	gfx_drawstring(110,0,"RET",GFX_UNDERLINE);
	time_t t;
	time(&t);
	info = localtime(&t);
	settings[0].value = 1900+info->tm_year;
	settings[1].value = info->tm_mon+1;
	settings[2].value = info->tm_mday;
	settings[3].value = info->tm_hour;
	settings[4].value = info->tm_min;
	settings[5].value = info->tm_sec;
	draw();
}

void close_settings(){
	
}

screen screen_settings = {
	.update = &update_settings,
	.setup = &setup_settings,
	.close = &close_settings
};