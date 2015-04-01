#ifndef DOGM_H_
#define DOGM_H_

#include <avr/io.h>

#define HEIGHT 64
#define WIDTH 128

typedef uint8_t pixel_t;

void gfx_init();
void gfx_clear();

#define DOG_RST		1
#define DOG_A0		2
#define DOG_SO		4
#define DOG_SCL		3
#define DOG_CS		0

#define SET_IO(pin) PORTD_OUTSET = (1 << (pin))
#define CLR_IO(pin) PORTD_OUTCLR = (1 << (pin))
#define SET_DIR(pin) PORTD_DIRSET = (1 << (pin))


#endif