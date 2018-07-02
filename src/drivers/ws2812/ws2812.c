/*
 * ws2812.c
 *
 * Created: 12/13/2015 8:12:30 PM
 *  Author: Daniel
 */ 
#include "ws2812.h"

void Ws2812HighCode(void);
void Ws2812LowCode(void);
void Ws2812WriteResCode(void);

void Ws2812WriteLEDBytes(struct WS2812_GRB_BYTES* ledBytes)
{	
	uint8_t data;
			
		//disable interrupts
		cli();
		
		for(int ledByteCount = 0; ledByteCount < NUM_OF_BYTES_PER_LED; ledByteCount++)
		{	
			data = ledBytes->data[ledByteCount];
			/*
			Data format is G7..G0, R7..R0, B7..B0
			High bit is sent first.
			*/
				
			///*			
			//~8.8uS - ~11.3uS
			if(data & (0x80))
				Ws2812HighCode();
			else
				Ws2812LowCode();
				
			if(data & (0x40))
				Ws2812HighCode();
			else
				Ws2812LowCode();	
				
			if(data & (0x20))
				Ws2812HighCode();
			else
				Ws2812LowCode();
			
			if(data & (0x10))
				Ws2812HighCode();
			else
				Ws2812LowCode();
			
			if(data & (0x08))
				Ws2812HighCode();
			else
				Ws2812LowCode();
			
			if(data & (0x04))
				Ws2812HighCode();
			else
				Ws2812LowCode();
				
			if(data & (0x02))
				Ws2812HighCode();
			else
				Ws2812LowCode();
			
			if(data & (0x01))
				Ws2812HighCode();			
			else
				Ws2812LowCode();			
		}
		
		//enable interrupts
		sei();
		
	return;
}

void Ws2812WriteResCode()
{
	//delay to latch in data, in uS
	for(int timer = 0; timer < 50; timer++)
	{
		for(int innerTimer = 0; innerTimer < 5; innerTimer++)
		{
			asm("NOP");
			asm("NOP");
			asm("NOP");
		}
	}
	return;
}

void Ws2812HighCode()
{
	//High section - Timing @ 32MHz clock
	PORTA_OUT |= 0x01;	//~100ns
	
	asm("NOP");			//~30ns per NOP
	asm("NOP");
	asm("NOP");	
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");	
	
	//Low section
	PORTA_OUT &= 0xFE;	//~100ns
		
	asm("NOP");
	asm("NOP");
	asm("NOP");	
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");	

	return;
}

void Ws2812LowCode()
{
	//High section - Timing @ 32MHz clock
	PORTA_OUT |= 0x01;	//~100ns
	//PORTA_OUT &= 0xFE;	
	//PORTA_OUT |= 0x01;	
	//PORTA_OUT &= 0xFE;
	
	asm("NOP");			//~30ns per NOP
	asm("NOP");			
	asm("NOP");
				
	asm("NOP");			
	asm("NOP");			
	asm("NOP");			
	
	asm("NOP");			
	asm("NOP");		
	
	//Low section
	PORTA_OUT &= 0xFE;	//~100ns
		
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	asm("NOP");
	asm("NOP");
	
	asm("NOP");
	return;
}