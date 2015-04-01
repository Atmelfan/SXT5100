#include "keyboard.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DEBUG 0

#define COLS PORTA
#define COLS_INT_vect PORTA_INT0_vect
#define ROWS PORTD


void keyboard_wait_async(){
	//Set all rows to low so that columns gets pulled low when pressed
	ROWS.OUTCLR = 0x0f;
	//Enable interrupts
	PMIC.CTRL |= PMIC_LOLVLEN_bm;
	sei();
}

//Wake up and let whatever is running scan the keyboard.
EMPTY_INTERRUPT(COLS_INT_vect);

keyboard_keys keyboard_scan(){
	for (int row = 0; row < 4; ++row)
	{
		//Set row to low
		ROWS.OUTSET = 0x0f;
		ROWS.OUTCLR = (1 << row);
		//Read columns
		uint8_t cols = COLS.IN;
		if(cols != 0xff){
			//If >1 column is low, debounce and call handler.
			_delay_ms(10);
			for (int col = 0; col < 8; ++col)
			{
				if(cols & (1 << col)){
					return row*8 + col;
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