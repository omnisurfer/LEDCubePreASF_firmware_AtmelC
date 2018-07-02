
/*
 * Assembler.s
 *
 * Created: 10/31/2015 5:08:05 PM
 *  Author: Daniel
 */ 

 //http://www.avrfreaks.net/forum/inline-asm-port-definitions
    
#include "avr/io.h"

.global porta_pin0_high
porta_pin0_high:		
		ldi	r24,0x01
		sts	PORTA_OUT,r24

		ldi	r24,0x00
		sts	PORTA_OUT,r24

		ldi	r24,0x01
		sts	PORTA_OUT,r24

		ldi	r24,0x00
		sts	PORTA_OUT,r24

		ldi	r24,0x01
		sts	PORTA_OUT,r24
		ret		

.global porta_pin0_low
porta_pin0_low:
		ldi	r24,0x00
		sts	PORTA_OUT,r24
		ret
