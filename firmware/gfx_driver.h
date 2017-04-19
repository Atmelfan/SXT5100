#ifndef GFX_DRIVER_H_
#define GFX_DRIVER_H_

#include <avr/io.h>

#define HEIGHT 64
#define WIDTH 128
#define LEFT_ADJ(l) (WIDTH - l*6) 

typedef uint8_t pixel_t;

#define GFX_NONE 0
typedef enum 
{
	GFX_INVERT		= (1 << 0),
	GFX_UNDERLINE	= (1 << 1),
	GFX_CROSS		= (1 << 2)
}style;

void gfx_init();
void gfx_clear();
void gfx_clearr(uint8_t);
void gfx_drawchar(uint8_t x, uint8_t row, char c, uint8_t style);
void gfx_drawstring(uint8_t x, uint8_t row, char* s, uint8_t style);
void gfx_drawstring_cursor(uint8_t x, uint8_t row, char* s, uint8_t cursor, uint8_t style);

#define DOG_BL 		2
#define DOG_A0		6
#define DOG_SO		5
#define DOG_SCL		7
#define DOG_CS		4

#define SET_IO(pin) PORTE_OUTSET = (1 << (pin))
#define CLR_IO(pin) PORTE_OUTCLR = (1 << (pin))
#define SET_DIR(pin) PORTE_DIRSET = (1 << (pin))
#define CLR_DIR(pin) PORTE_DIRCLR = (1 << (pin))

#endif