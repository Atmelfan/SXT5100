#include "screen.h"
#include "gfx_driver.h"
#include "apl.h"
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


char command[128] = {' ',0};
uint8_t mode = 0;
uint8_t indx = 0;

char* op;

#define STRIP(s) while(*s == ' ') s++
#define SKIP(s) while(!(isdigit(*s) || *s == '-')) s++

double vector[2][6];

double execute(char* s){
	for (int i = 0; i < 6; ++i)
	{
		vector[0][i] = vector[1][i] = 0;
	}
	char *t;
	uint8_t a = 0, x = 0, m = 0;
	while((isdigit(*s) || *s == '-') && a < 6){
		vector[0][a] = strtod(s, &t);
		STRIP(t);
		s = t;
		a++;
	}
	m=a;
	op = s;
	SKIP(s);
	while((isdigit(*s) || *s == '-') && x < 6){
		vector[1][x] = strtod(s, &t);
		STRIP(t);
		s = t;
		x++;
	}

	if(x>m)
		m=x;
	switch(*op){
		case '+':
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]=vector[1][i];
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]+=vector[1][i];
				}
			}
		break;
		case 1:
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]=-vector[1][i];
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]-=vector[1][i];
				}
			}
		break;
		case 14:
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]= vector[1][i] > 0 ? 1 : -1;
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]*=vector[1][i];
				}
			}
			
		break;
		case 15:
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]=1/vector[1][i];
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i]/=vector[1][i];
				}
			}
			
		break;
		case '*':
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i] = pow(M_E, vector[1][i]);
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i] = pow(vector[0][i], vector[1][i]);
				}
			}
			
		break;
		case 16:
			if(a == 0){
				for (int i = 0; i < x; ++i)
				{
					vector[0][i] = log(vector[1][i]);
				}
			}else{
				for (int i = 0; i < x; ++i)
				{
					vector[0][i] = log(vector[1][i]) / log(vector[0][i]);
				}
			}
			
		break;
		case '=':
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] == vector[0][i];
			}
		break;
		case 20:
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] != vector[0][i];
			}
		break;
		case 19:
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] >= vector[0][i];
			}
		break;
		case 18:
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] <= vector[0][i];
			}
		break;
		case '>':
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] > vector[0][i];
			}
		break;
		case '<':
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = vector[1][i] < vector[0][i];
			}
		break;
		case 12:
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = fmin(vector[1][i], vector[0][i]);
			}
		break;
		case 13:
			for (int i = 0; i < x; ++i)
			{
				vector[0][i] = fmax(vector[1][i], vector[0][i]);
			}
		break;
	}
	
	
	char buff[16];
	gfx_clearr(2);
	for (int i = 0; i < m; ++i)
	{

		dtostrf(vector[0][i], 4, 6,(char*)&buff);
		gfx_drawstring(128-strlen((char*)&buff)*6,2+i,(char*)&buff, GFX_NONE);
	}
	return 0;
}

void update_console(keyboard_keys key){
	if (key == KEYBORD_F3)
	{
		set_screen(&screen_clock);
		return;
	}else if (key == KEYBORD_EXE)
	{
		execute((char*)&command);
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
		if (indx < 20 && command[indx] != '\0')
		{
			indx++;
		}
	}else if (key == KEYBORD_DELETE)
	{
		for (int i = indx; i < 20-1; ++i)
		{
			command[i] = command[i+1];
		}
		command[20] = 0;
	}else{
		for (int i = 20; i > indx; --i)
		{
			command[i] = command[i-1];
		}
		command[indx] = keyboard_tochar(mode, key);
		if (indx < 20)
		{
			indx++;
			if(command[indx] == 0)
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
	//indx = 0;
	gfx_drawstring_cursor(0, 1, (char*)&command, indx, GFX_UNDERLINE);
	gfx_drawstring(62 ,0,"SHF",GFX_UNDERLINE);
	gfx_drawstring(86 ,0,"ALT",GFX_UNDERLINE);
	gfx_drawstring(110,0,"RET",GFX_UNDERLINE);
	//Check if external memeory is working
	if (apl_memtest() != APL_NO_ERROR)
	{
		gfx_drawstring(0,7,"Memory error",GFX_NONE);
	}
}

void close_console(){

}

screen screen_console = {
	.update = &update_console,
	.setup = &setup_console,
	.close = &close_console
};