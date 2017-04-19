#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <string.h>
#include <time.h>
#include "keyboard.h"
#include "gfx_driver.h"
#include "screen.h"
//#include "apl.h"


time_t current_time;
screen* current_screen;
uint8_t ttr = 0;

void print_time(time_t* t){
	char str[9];
	struct tm* timeinfo = localtime(t);
	strftime((char*)&str, 9, "%T", timeinfo);
	gfx_drawstring(0,0,(char*)&str,GFX_NONE);
}

void set_screen(screen* scr){
	if (current_screen != NULL)
	{
		current_screen->close();
	}
	gfx_clear();
	print_time(&current_time);
	scr->setup();
	current_screen = scr;
	ttr = 0;
}

//Something woke up the processor, update screen and do stuff as necessary.
//Interrupts:
//  Clock update (1Hz)
//  Key pressed
void update(){
	//update time indicator
	time_t t;
	time(&t);
	if (current_time != t)
	{
		current_time = t;
		print_time(&t);
	}
	//Do whatever
	keyboard_keys key = keyboard_scan();
	if(key != KEYBORD_NONE){
		current_screen->update(key);
	}
}

void setClockTo32MHz() {
    CCP = CCP_IOREG_gc;              // disable register security for oscillator update
    OSC.CTRL = OSC_RC32MEN_bm;       // enable 32MHz oscillator
    while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // wait for oscillator to be ready
    CCP = CCP_IOREG_gc;              // disable register security for clock update
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc; // switch to 32MHz clock
}

static inline void rtc_init ( void ) {
	OSC_XOSCCTRL= OSC_XOSCSEL_32KHz_gc;
	OSC_CTRL |= OSC_XOSCEN_bm;   /* Set internal 32kHz as source. */
	while ( !( OSC_STATUS & OSC_XOSCRDY_bm ) ); /* Wait for the int. 32kHz oscillator to stabilize. */
	
	// Next 3 lines must be in this order.
	while( ( RTC_STATUS & 0x01 ) ); // Needed B 4 writing to RTC PER / CNT registers
	RTC_PER = (1024 - 1); // Period reg. value. Must subtract 1, 'cause zero value counted.
	RTC_CTRL = RTC_PRESCALER_DIV1_gc; // div by 1, so 1024Hz oscillator
	RTC_INTCTRL |=  RTC_OVFINTLVL_HI_gc; // Set Int. priority level to low in RTC. Must match what's in PMIC_CTRL
	/* Set external 32kHz oscillator as clock source for RTC and enable it. */
	CLK_RTCCTRL = CLK_RTCSRC_TOSC_gc | CLK_RTCEN_bm;

}


ISR(RTC_OVF_vect, ISR_NAKED)
{
	ttr++;
    system_tick();
    reti();
}

int main() 
{
	setClockTo32MHz();
	PORTE.DIRSET = (1 << 2);
	gfx_init();
	apl_init_mem();
	keyboard_init();
	//Set initial date
	struct tm date;
	date.tm_year = 2015-1900;
	date.tm_mon = 7-1;
	date.tm_mday = 18;
	date.tm_hour = 14;
	date.tm_min = 7;
	date.tm_sec = 00;
	date.tm_isdst = 0;
	set_system_time(mktime(&date));
	//Initialize clock screen
	set_screen(&screen_clock);
	rtc_init();
	PMIC_CTRL |= PMIC_HILVLEN_bm | PMIC_LOLVLEN_bm; //Enable RTC interrupts
	while(1){
		cli();
		update();
		//Sleep between interrupts
		while(RTC.STATUS & RTC_SYNCBUSY_bm);
		SLEEP.CTRL = SLEEP_SEN_bm + SLEEP_SMODE_PSAVE_gc;
		sei();
		sleep_cpu();
		//PORTE.OUTTGL = (1 << 2);
	}
	return 0;
}