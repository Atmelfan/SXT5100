#include "dogm.h"

uint8_t buffer[WIDTH*HEIGHT/8];

void gfx_init(){
	gfx_spi_init();


	gfx_clear();
}

void gfx_clear(){
	for (int i = 0; i < (WIDTH*HEIGHT/8); ++i)
	{
		buffer[i] = 0x00;
	}
}

void gfx_drawpoint(pixel_t x, pixel_t y){
	buffer[(y/8)*WIDTH + x] |= (1 << y % 8);
}

void gfx_drawline(pixel_t x1, pixel_t y1, pixel_t x2, pixel_t y2){
  // int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  // int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  // int err = (dx>dy ? dx : -dy)/2, e2;
 
  // for(;;){
  //   gfx_drawpoint(x0,y0);
  //   if (x0==x1 && y0==y1) break;
  //   e2 = err;
  //   if (e2 >-dx) { err -= dy; x0 += sx; }
  //   if (e2 < dy) { err += dx; y0 += sy; }
  // }
}

void gfx_drawbox(pixel_t x1, pixel_t y1, pixel_t x2, pixel_t y2){
	for (int i = x1; i <= x2; ++i)
	{
		gfx_drawpoint(i, y1);
		gfx_drawpoint(i, y2);
	}
	for (int i = y1; i <= y2; ++i)
	{
		gfx_drawpoint(x1, i);
		gfx_drawpoint(x2, i);
	}
}

void gfx_drawtext(pixel_t x, pixel_t y, char* s);
void gfx_drawtext_cursor(pixel_t x, pixel_t y, char* s, uint8_t cursor);