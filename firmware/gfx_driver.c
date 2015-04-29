#include "gfx_driver.h"
#include "gfx_font.h"
#include <util/delay.h>

void spi_init(){
	/*Setup io*/
	SET_DIR(DOG_A0);
	SET_DIR(DOG_SO);
	SET_DIR(DOG_SCL);
	SET_DIR(DOG_CS);
	/*Select dog*/
	CLR_IO(DOG_CS);//Select dogm
	CLR_IO(DOG_SCL);
	CLR_IO(DOG_CS);//Select dogm
}

/*
*Stupid me connected A0(output) to MISO which is made to a input by HW SPI...
*So I have to bitbang everything, how fun!
*/
void spi_write(char byte){
#if HW_REVISION == 2
	CLR_IO(DOG_CS);//Select dogm
	for (int i = 0; i < 8; ++i){
		if(byte & 0x80)
			SET_IO(DOG_SO);
		else
			CLR_IO(DOG_SO);
		byte <<= 1;


		SET_IO(DOG_SCL);
		_delay_us(20);
		CLR_IO(DOG_SCL);
		_delay_us(20);
	}
	SET_IO(DOG_CS);
	CLR_IO(DOG_SO);
	_delay_us(50);
#else
	//Use HW SPI for rev 3
#endif
}

void spi_write_cmd(uint8_t byte){
	CLR_IO(DOG_A0);//Select dogm
	spi_write(byte);
}

void spi_write_dat(uint8_t byte){
	SET_IO(DOG_A0);//Select dogm
	spi_write(byte);
}

void gfx_init(){
	spi_init();
	/*Initialize dog*/
	spi_write_cmd(0x40);
	spi_write_cmd(0xA1);
	spi_write_cmd(0xC0);
	spi_write_cmd(0xA6);
	spi_write_cmd(0xA2);
	spi_write_cmd(0x2F);
	spi_write_cmd(0xF8);
	spi_write_cmd(0x00);
	spi_write_cmd(0x27);
	spi_write_cmd(0x81);
	spi_write_cmd(0x16);
	spi_write_cmd(0xAC);
	spi_write_cmd(0x00);
	spi_write_cmd(0xAF);

	gfx_clear();
}

void set_page(uint8_t page){
	spi_write_cmd(0xB0 + page);
}

void set_column(uint8_t column){
	spi_write_cmd(0x10 + ((column >> 4) & 0x0F));
	spi_write_cmd(0x00 + ((column >> 0) & 0x0F));
}


void gfx_clear(){
	for (int p = 0; p < 8; ++p)
	{
		set_page(p);
		set_column(0);
		for (int i = 0; i < 128; ++i)
		{
			spi_write_dat(0x00);
		}
	}
	
}

void gfx_drawchar(uint8_t x, uint8_t row, char c, uint8_t style){
	set_page(row);
	set_column(x);
	for (int i = 0; i < 6; ++i)
	{
		uint8_t p = pgm_read_byte(&(apl_font[(uint8_t)c][i]));
		if (style & GFX_UNDERLINE)
		{
			p |= 0x80;
		}
		if (style & GFX_INVERT)
		{
			p = ~p;
		}
		spi_write_dat(p);
	}
}

void gfx_drawstring(uint8_t x, uint8_t row, char* s, uint8_t style){
	set_page(row);
	set_column(x);
	while(*s){
		char c = *s;
		for (int i = 0; i < 6; ++i)
		{
			uint8_t p = pgm_read_byte(&(apl_font[(uint8_t)c][i]));
			if (style & GFX_UNDERLINE)
			{
				p |= 0x80;
			}
			if (style & GFX_INVERT)
			{
				p = ~p;
			}
			spi_write_dat(p);
		}
		s++;
	}
}

void gfx_drawstring_cursor(uint8_t x, uint8_t row, char* s, uint8_t cursor, uint8_t style){
	char* start = s;
	set_page(row);
	set_column(x);
	while(*s){
		char c = *s;
		for (int i = 0; i < 6; ++i)
		{
			uint8_t p = pgm_read_byte(&(apl_font[(uint8_t)c][i]));
			if((s - start == cursor))
			{
				if (style & GFX_UNDERLINE)
				{
					p |= 0x80;
				}
				if (style & GFX_INVERT)
				{
					p = ~p;
				}
			}
			spi_write_dat(p);
		}
		s++;

	}
}

