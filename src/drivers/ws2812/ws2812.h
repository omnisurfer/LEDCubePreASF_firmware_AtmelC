/*
 * ws2812.h
 *
 * Created: 12/13/2015 8:12:18 PM
 *  Author: Daniel
 * Description: Driver for control of WS2812 intelligent LEDs (aka "NeoPixels"). Written for 8-bit AVR
 */ 


#ifndef WS2812_H_
#define WS2812_H_

#include "../../processor/processor.h"
//#include <avr/interrupt.h>
#include "../../processor/interrupts.h"

#define NUM_OF_BYTES_PER_LED	3

typedef enum
{
	Red,
	Green,
	Blue
}Color;

//struct to define one LEDs worth of bytes (3)
typedef struct WS2812_GRB_BYTES WS2812_GRB_BYTES;

struct WS2812_GRB_BYTES
{
	// {G7..G0}[2], {R7..R0}[1], {B7..B1}[0]
	uint8_t data[NUM_OF_BYTES_PER_LED];
};

/*Function prototypes */
void Ws2812WriteLEDBytes(WS2812_GRB_BYTES* ledBytes);
void Ws2812WriteResCode(void);

#endif /* WS2812_H_ */