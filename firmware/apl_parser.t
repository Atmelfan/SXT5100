#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "apl.h"

enum apl_type {
	APL_VECTOR,
	APL_MATRIX,
	APL_STRING,
	APL_LAMBDA
};

struct apl_value {
	apl_type type;
	union {
		uint16_t size;
		uint8_t rows,cols;
	};
	void* ptr;
}

struct apl_stack
{
	uint16_t size;
	void* stack;
};




/*
⍝ b ← + / 2 × a ⋄
⍝ b ← + / 2 × ⋄ 1 2 3
⍝ b ← + / 2 ⋄ × 1 2 3
⍝ b ← + / ⋄ 2 × 1 2 3
⍝ b ← + ⋄ / 2 × 1 2 3
⍝ b ← + ⋄ / 2 4 6
⍝ b ← ⋄ + / 2 4 6
⍝ b ⋄ ← + / 2 4 6
⍝ b ⋄ ← 12
⍝ ⋄ b ← 12
⍝ ⋄ 12
⋄ ⍝ 12
*/

/*
⍝ b ← + / 2 × a ⋄
⍝ b ← + / 2 × ⋄ 1 2 3
⍝ b ← + / 2 ⋄ × 1 2 3
⍝ b ← + / ⋄ 2 × 1 2 3
⍝ b ← + ⋄ / 2 × 1 2 3
⍝ b ← + ⋄ / 2 4 6
⍝ b ← ⋄ + / 2 4 6
⍝ b ⋄ ← + / 2 4 6
⍝ b ⋄ ← 12
⍝ ⋄ b ← 12
⍝ ⋄ 12
⋄ ⍝ 12
*/

void execute_stack(){

}

void parse_token(){

}

char* move(char *s){
	
	return s;
}