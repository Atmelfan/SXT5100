#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include <avr/io.h>

//Spelled keyboard wrong, too lazy to fix.
typedef enum {
	//ROW 1					   char_________shift char__alt char
	KEYBORD_NONE 	= 0,	// \0			\0			\0
	KEYBORD_LEFT 	= 1,	// \0			\0			\0
	KEYBORD_DELETE 	= 2,	// \0			\0			\0
	KEYBORD_RIGHT 	= 3,	// \0			\0			\0
	KEYBORD_F1 		= 4,	// \0			\0			\0
	KEYBORD_F2 		= 5,	// \0			\0			\0
	KEYBORD_F3 		= 6,	// \0			\0			\0
	KEYBORD_RESET 	= 7,	// \0			\0			\0
	//ROW 2
	KEYBORD_7	 	= 8,	// 7			Q 			=/=
	KEYBORD_8	 	= 9,	// 8			W 			<
	KEYBORD_9	 	= 10,	// 9			E 			<=
	KEYBORD_ADD 	= 11,	// +			R 			=
	KEYBORD_MUL 	= 12,	// x			T 			>=
	KEYBORD_EXP		= 13,	// *			Y 			>
	KEYBORD_LFP 	= 14,	// (			U 			O
	KEYBORD_RFP 	= 15,	// )			I 			P
	//ROW 3
	KEYBORD_4	 	= 16,	// 4			A 			Ceil
	KEYBORD_5	 	= 17,	// 5			S 			Floor
	KEYBORD_6	 	= 18,	// 6			D 			
	KEYBORD_SUB 	= 19,	// -			F
	KEYBORD_DIV 	= 20,	// %			G 			;
	KEYBORD_LOG		= 21,	// (*)			H 			~
	KEYBORD_CRC 	= 22,	// o (circle)	J 			
	KEYBORD_LSH 	= 23,	// /			K 			L
	//ROW 4
	KEYBORD_1	 	= 24,	// 1 			Z 			Epsilon
	KEYBORD_2	 	= 25,	// 2 			X 			
	KEYBORD_3	 	= 26,	// 3			C 			Union
	KEYBORD_0	 	= 27,	// 0			V 			j
	KEYBORD_DOT 	= 28,	// .			B 			,
	KEYBORD_NEG		= 29,	// ^-(negate) 	N 			"
	KEYBORD_SPACE 	= 30,	// (space) 		M 			Comment
	KEYBORD_EXE 	= 31,	// EXE 			f 			Assign
}keyboard_keys;

int8_t keyboard_tonum(keyboard_keys key);
/**
* Initialize keyboard
*/
void keyboard_init();
/**
* Returns 1 if a key has been pressed since this method was last called, 0 otherwise.
*/

char keyboard_pressed();
/**
* Scans and returns the first pressed key or 0 if no key was pressed.
*/
keyboard_keys keyboard_scan();
/**
*
*/
char keyboard_tochar(uint8_t mode, keyboard_keys key);


#endif



