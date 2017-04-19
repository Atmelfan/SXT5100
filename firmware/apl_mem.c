#include "apl.h"
#include <avr/io.h>

#define APL_STACK_START 0x4000;

//The apl stack and heap resides in the external memory
void apl_init_mem(){
	//Setup external memory...
	PORTH.DIR = /*WE*/(1<<0)|/*OE*/(1<<1)|/*LE*/(1<<2)|/*CS1*/(1<<4)|/*CS2*/(1<<5);
	PORTH.OUT = /*WE*/(1<<0)|/*OE*/(1<<1)|/*CS1*/(1<<4)|/*CS2*/(1<<5);
	PORTK.DIR = 0xFF;
	//ALE multiplexing, 3port mode.
	EBI.CTRL = EBI_SRMODE_ALE1_gc | EBI_IFMODE_3PORT_gc;
	EBI.CS0.BASEADDR = 0x0000;          								// Set CS0 range to 0x000000 - 0x007FFF(32K)
    EBI.CS0.CTRLA = EBI_CS_MODE_SRAM_gc | EBI_CS_ASIZE_32KB_gc;	    // SRAM mode, 32k address space	

	EBI.CS1.BASEADDR = 0x8000;          								// Set CS0 range to 0x008000 - 0x00FFFF(32K)
    EBI.CS1.CTRLA = EBI_CS_MODE_SRAM_gc | EBI_CS_ASIZE_32KB_gc;	
}


uint8_t apl_memtest(){
	uint8_t* testw = (uint8_t*)0xFFFF;
	*testw = 0xAA;
	uint8_t t = *testw;
	if (t == 0xAA)
	{
		return APL_NO_ERROR;	
	}
	return APL_MEM_ERROR;//Write or read failed
}


/*
   [#######|########|#######|###############|###]
*/

apl_object* stack_ptr = APL_STACK_START;


apl_object* apl_get_stackpointer(){
	return stack_ptr;
}

void apl_set_stackpointer(void* stack_pointer){
	stack_ptr = stack_pointer;
}

apl_object* apl_alloc_vector(uint16_t width, uint16_t height){
	//Initialize new apl object at current stack position
	apl_object* nw = stack_ptr;
	nw->type = APL_VECTOR;
	nw->width = width;
	nw->height = height;
	//Increase stack pointer by object size
	stack_ptr += APL_OBJECT_VECTOR_SIZE(width*height);
	return nw;
}

apl_object* apl_alloc_string(uint16_t length){
	//Initialize new apl object at current stack position
	apl_object* nw = stack_ptr;
	nw->type = APL_STRING;
	nw->width = length;
	nw->height = 1;
	//Increase stack pointer by object size
	stack_ptr += APL_OBJECT_STRING_SIZE(length);
	return nw;
}



