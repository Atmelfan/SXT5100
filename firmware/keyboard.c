#include "keyboard.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define DEBUG 0

#define COLS PORTA
#define COLS_INT_vect PORTA_INT0_vect
#define ROWS PORTD

volatile char pressed = 0;

const char chars[][3] PROGMEM = {
	{'7','Q',20},//0
	{'8','W','<'},//1
	{'9','E',18},//2
	{'+','R','='},//3
	{14,'T',19},//4
	{'*','Y','>'},//5
	{'(','U','O'},//6
	{')','I','P'},//7

	{'4','A',13},//8
	{'5','S',12},//9
	{'6','D',11},//10
	{'-','F',10},//11
	{15,'G',';'},//12
	{16,'H','~'},//13
	{17,'J',9},//14
	{'/','K','L'},//15

	{'1','Z',7},//16
	{'2','X',5},//17
	{'3','C',6},//18
	{'0','V','j'},//19
	{'.','B',','},//20
	{1,'N','"'},//21
	{' ','M',3},//22
	{0,'?',2},//23
};

int8_t keyboard_tonum(keyboard_keys key){
	if (key >= 8 && key <  11)
	{
		return key-1;
	}
	if (key >= 16 && key <  19)
	{
		return key-12;
	}
	if (key >= 24 && key <  27)
	{
		return key-23;
	}
	if (key == 27)
	{
		return 0;
	}
	return -1;
}


char keyboard_tochar(uint8_t mode, keyboard_keys key){
	if (key < 8)
	{
		return '?';
	}
	return pgm_read_byte(&(chars[key - 8][mode]));
}

void keyboard_wait_async(){
	//Set all rows to low so that columns gets pulled low when pressed
	ROWS.OUTCLR = 0x0f;
	sei();
}

//Wake up and let whatever is running scan the keyboard.
ISR(COLS_INT_vect){
	pressed = 1;
}

char keyboard_pressed(){
	if (pressed)
	{
		pressed = 0;
		return 1;
	}
	return 0;
} 

keyboard_keys keyboard_scan(){
	for (int row = 0; row < 4; ++row)
	{
		//Set row to low
		ROWS.OUTSET = 0x0f;
		ROWS.OUTCLR = (1 << row);
		_delay_us(10);
		//Read columns
		uint8_t cols = ~COLS.IN;
		if(cols != 0x00){
			//If >1 column is low, debounce and call handler.
			_delay_ms(100);
			cols = ~COLS.IN;
			for (int col = 0; col < 8; ++col)
			{
				if(cols & (1 << col) && !(row == 0 && col == 7)){
					//PORTE.OUTTGL = (1 << 2);
					keyboard_wait_async();
					return row*8+col;
				}
			}
		}
	}
	keyboard_wait_async();
	return 0;
}

/**
* Initialize keyboard
*/
void keyboard_init(){
	//Set all 8 column lines to inputs.
	COLS.DIR = 0x00;
	//Set all 4 row lines to outputs.
	ROWS.DIR = 0x0f;
	//Enable pin change interrupt on all column lines(couldn't be bothered doing multi pin assignment...)
	COLS.PIN0CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN1CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN2CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN3CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN4CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN5CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN6CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	COLS.PIN7CTRL = PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc;
	//Trigger INT0 for all pin changes.
	COLS.INT0MASK = 0xff;
	COLS.INTCTRL = PORT_INT0LVL_LO_gc;
	//Setup interrupt on key press.
	keyboard_wait_async();
}