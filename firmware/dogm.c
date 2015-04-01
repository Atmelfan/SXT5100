#include "dogm.h"

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
}

void spi_write(char byte){
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

void gfx_spi_write_cmd(uint8_t byte){
	CLR_IO(DOG_A0);//Select dogm
	spi_write(byte);
}

void gfx_spi_write_dat(uint8_t byte){
	SET_IO(DOG_A0);//Select dogm
	spi_write(byte);
}

void gfx_init(){
	gfx_spi_init();
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

	gfx_clear();
}

void gfx_clear(){
	//TODO
}
