/*
 * interrupts.c
 *
 * Created: 12/13/2015 8:49:25 PM
 *  Author: Daniel
 */ 

#include "interrupts.h"

void InitInterrupts()
{
	//set priority
	PMIC.CTRL |= PMIC_LOLVLEN_bm; //(PMIC_HILVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_LOLVLEN_bm);
	
	//enable interrupts
	sei();
	
	return;
}
