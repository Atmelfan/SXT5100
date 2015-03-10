#ifndef DOGM_H_
#define DOGM_H_

#include <avr/io.h>

#define HEIGHT 64
#define WIDTH 128

typedef pixel_t uint8_t;

void gfx_init();
void gfx_clear();
void gfx_drawpoint(pixel_t x, pixel_t y);
void gfx_drawline(pixel_t x1, pixel_t y1, pixel_t x2, pixel_t y2);
void gfx_drawbox(pixel_t x1, pixel_t y1, pixel_t x2, pixel_t y2);
void gfx_drawtext(pixel_t x, pixel_t y, char* s);
void gfx_drawtext_cursor(pixel_t x, pixel_t y, char* s, uint8_t cursor);

#define DOG_RST		1
#define DOG_A0		2
#define DOG_SO		4
#define DOG_SCL		3
#define DOG_CS		0

#define SET_IO(pin) PORTD_OUTSET = (1 << (pin))
#define CLR_IO(pin) PORTD_OUTCLR = (1 << (pin))
#define SET_DIR(pin) PORTD_DIRSET = (1 << (pin))
void gfx_spi_init(){
	/*Setup io*/
	SET_DIR(DOG_RST);
	SET_DIR(DOG_A0);
	SET_DIR(DOG_SO);
	SET_DIR(DOG_SCL);
	SET_DIR(DOG_CS);
	/*Select dog*/
	SET_IO(DOG_RST);//Set reset high (no reset)
	SET_IO(DOG_CS);//Select dogm
	/*Initialize dog*/
	gfx_spi_write_cmd(0x40);
	gfx_spi_write_cmd(0xA1);
	gfx_spi_write_cmd(0xC0);
	gfx_spi_write_cmd(0xA6);
	gfx_spi_write_cmd(0xA2);
	gfx_spi_write_cmd(0x2F);
	gfx_spi_write_cmd(0xF8);
	gfx_spi_write_cmd(0x00);
	gfx_spi_write_cmd(0x27);
	gfx_spi_write_cmd(0x81);
	gfx_spi_write_cmd(0x16);
	gfx_spi_write_cmd(0xAC | 0x01);
	gfx_spi_write_cmd(0x00 | 0x01);
	gfx_spi_write_cmd(0xAF);
}

void gfx_spi_write_cmd(uint8_t byte){
	CLR_IO(DOG_A0);//Select dogm
	while(byte){
		SET_IO(DOG_SCL);
		if(byte & 0x80)
			SET_IO(DOG_SO);
		else
			CLR_IO(DOG_SO);
		//delay
		CLR_IO(DOG_SCL);
		byte <<= 1;
		//delay
	}
}

void gfx_spi_write_dat(uint8_t byte){
	SET_IO(DOG_A0);//Select dogm
	while(byte){
		SET_IO(DOG_SCL);
		if(byte & 0x80)
			SET_IO(DOG_SO);
		else
			CLR_IO(DOG_SO);
		//delay
		CLR_IO(DOG_SCL);
		byte <<= 1;
		//delay
	}
}

#endif