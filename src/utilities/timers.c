/*
 * timers.c
 *
 * Created: 12/13/2015 9:11:26 PM
 *  Author: Daniel
 */ 

#include "timers.h"

void InitTimer()
{
	//Interrupt on overflow
	TCC0.INTCTRLA = TC_OVFINTLVL_LO_gc;
	
	//select Timer0 clock source as Div1024 (32MHz / 1024 = 31.25kHz) and enable counter
	TCC0.CTRLA |= TC_CLKSEL_DIV1024_gc;
	
	//clear the counter
	TCC0.CNT = 0x0000;
	
	//set period to 322 counts ~10ms (322 * (32MHz/1024)^-1)
	TCC0.PER = 0x0142;
	
	timerTick = false;

	return;
}

//Interrupt Handler for TC0 OVERFLOW
ISR(TCC0_OVF_vect)
{
	timerTick = true;	
	//PORTA.OUTTGL = 0x80;
}