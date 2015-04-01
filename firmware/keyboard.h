#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <avr/io.h>

typedef enum {
	//ROW 1
	KEYBORD_NONE 	= 0,	// (null)
	KEYBORD_LEFT 	= 1,	// <
	KEYBORD_DELETE 	= 2,	// X
	KEYBORD_RIGHT 	= 3,	// >
	KEYBORD_F1 		= 4,	// F1
	KEYBORD_F2 		= 5,	// F2
	KEYBORD_F3 		= 6,	// F3
	KEYBORD_RESET 	= 7,	// (reset)
	//ROW 2
	KEYBORD_7	 	= 8,	// 7
	KEYBORD_8	 	= 9,	// 8
	KEYBORD_9	 	= 10,	// 9
	KEYBORD_ADD 	= 11,	// +
	KEYBORD_MUL 	= 12,	// x
	KEYBORD_EXP		= 13,	// *
	KEYBORD_LFP 	= 14,	// (
	KEYBORD_RFP 	= 15,	// )
	//ROW 3
	KEYBORD_4	 	= 16,	// 4
	KEYBORD_5	 	= 17,	// 5
	KEYBORD_6	 	= 18,	// 6
	KEYBORD_SUB 	= 19,	// -
	KEYBORD_DIV 	= 20,	// %
	KEYBORD_LOG		= 21,	// (*)
	KEYBORD_CRC 	= 22,	// o
	KEYBORD_LSH 	= 23,	// /
	//ROW 4
	KEYBORD_1	 	= 24,	// 1
	KEYBORD_2	 	= 25,	// 2
	KEYBORD_3	 	= 26,	// 3
	KEYBORD_0	 	= 27,	// 0
	KEYBORD_DOT 	= 28,	// .
	KEYBORD_NEG		= 29,	// ^-
	KEYBORD_SPACE 	= 30,	// (space)
	KEYBORD_EXE 	= 31,	// EXE
}keyboard_keys;

/**
* Initialize keyboard
*/
void keyboard_init();

/**
* Scans and returns the first pressed key or 0 if no key was pressed.
*/
keyboard_keys keyboard_scan();


#endif



