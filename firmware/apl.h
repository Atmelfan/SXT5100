#include <avr/io.h>
#include "complex.h"
#ifndef APL_H
#define APL_H


typedef enum {
	APL_NO_ERROR = 0,
	APL_MEM_ERROR,
	APL_DIM_ERROR,
	APL_OUTAMEM
}apl_error;

typedef enum {
	APL_VECTOR,	//Array of floats (vector/matrix)
	APL_STRING
}apl_type;

typedef struct {
	apl_type type;
	uint16_t width;
	uint16_t height;
	char chars[0];
	complex_t vars[0];
}apl_object;

/*
 * Macros to calculate size of a vector or string object 
 */
#define APL_OBJECT_STRING_SIZE(length) (sizeof(apl_object) + (length)*sizeof(char))
#define APL_OBJECT_VECTOR_SIZE(length) (sizeof(apl_object) + (length)*sizeof(complex_t))

/**
 * Initializes external memory/stack used by APL
 */
void apl_init_mem();

/**
 * returns APL_MEM_ERROR if external memory isn't working for whatever reasons.
 * APL_NO_ERROR if fine.
 */
uint8_t apl_memtest();

#endif

