#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/sleep.h>
#include <string.h>
#include "time.h"
#include "dogm.h"
 
void setClockTo32MHz() {
    CCP = CCP_IOREG_gc;              // disable register security for oscillator update
    OSC.CTRL = OSC_RC32MEN_bm;       // enable 32MHz oscillator
    while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // wait for oscillator to be ready
    CCP = CCP_IOREG_gc;              // disable register security for clock update
    CLK.CTRL = CLK_SCLKSEL_RC32M_gc; // switch to 32MHz clock
}

time_t ck = 0;

ISR( RTC_OVF_vect ) {
	//Update time & display
	ck++;
	char* s = ctime(&ck);
	gfx_drawstring(STR_LEFT_ADJ(s, COLS), 0, s);
}


static inline void rtc_init ( void ) {
	OSC_XOSCCTRL= OSC_XOSCSEL_32KHz_gc;
	OSC_CTRL |= OSC_XOSCEN_bm;   /* Set internal 32kHz as source. */
	while ( !( OSC_STATUS & OSC_XOSCRDY_bm ) ); /* Wait for the int. 32kHz oscillator to stabilize. */
	PMIC_CTRL |= PMIC_LOLVLEN_bm; // Set Int. priority level to low in PMIC
	// Next 3 lines must be in this order.
	while( ( RTC_STATUS & 0x01 ) ); // Needed B 4 writing to RTC PER / CNT registers
	RTC_PER = (1024 - 1); // Period reg. value. Must subtract 1, 'cause zero value counted.
	RTC_CTRL = RTC_PRESCALER_DIV1_gc; // div by 1, so 1.024 kHz oscillator
	RTC_INTCTRL |=  RTC_OVFINTLVL_LO_gc; // Set Int. priority level to low in RTC. Must match what's in PMIC_CTRL
	/* Set internal 1.024 kHz oscillator as clock source for RTC and enable it. */
	CLK_RTCCTRL = CLK_RTCSRC_TOSC_gc | CLK_RTCEN_bm;

}

int main() 
{
	setClockTo32MHz();
	gfx_init();
	gfx_drawstring_ext(0,ROWS-1, "GPA Robotics  SXT5100", 0);
	PORTC_DIRSET = (1 << 0);
	rtc_init();
	while(1){
		while(RTC.STATUS & RTC_SYNCBUSY_bm);
		SLEEP.CTRL = SLEEP_SEN_bm + SLEEP_SMODE_PSAVE_gc;
		sei();
		sleep_cpu();
	}
	return 0;
}