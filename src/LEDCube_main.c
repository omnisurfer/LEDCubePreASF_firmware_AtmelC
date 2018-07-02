/*
 * LEDCube.c
 *
 * Created: 10/31/2015 4:30:30 PM
 *  Author: Daniel
 */ 
#include <string.h>

#include "processor/processor.h"
#include "processor/interrupts.h"
#include "processor/sysclk.h"

#include "drivers/ws2812/ws2812.h"

#include "utilities/port_hal.h"
#include "utilities/timers.h"

#include "devices/LEDCube.h"


void InitTimer(void);

//void InitInterrupts(void);

#define CUBE_LAYER_LEDS_PER_LINE	4
#define CUBE_LAYER_LINES			4
#define CUBE_LAYER_COUNT			4
#define NUM_OF_LEDS_PER_CUBE		CUBE_LAYER_COUNT * CUBE_LAYER_LEDS_PER_LINE * CUBE_LAYER_LINES

int main(void)
{
	//init IRQ
	InitInterrupts();
	
	//init Clock
	InitSysClk();
	
	//
	//init Board
	//init_board()
	
	//init Peripherals
	InitTimer();
		
	//DEBUG - Set PORTR direction - 0, 7 output		
	SetPortPinDirection(PORT_A, PIN_0, PORT_OUTPUT);
	SetPortPinDirection(PORT_A, PIN_7, PORT_OUTPUT);
								
	uint8_t counter = 0;	
	
	LED_CUBE_DEFINITION LEDCube =
	{
		.cubeOrigin = BOTTOM_LEFT,		
		.cubeClimbDirection = FLOOR_TO_CEILING,
		.cubePathLayout = SWITCHBACK,
		.cubeTravelDirection = LEFT_TO_RIGHT,
		.cubeBridging = NONE,
		.cubeLayerLEDsPerLine = CUBE_LAYER_LEDS_PER_LINE,
		.cubeLayerLineCount = CUBE_LAYER_LINES,
		.cubeLayerCount = CUBE_LAYER_COUNT
	};
			
	WS2812_GRB_BYTES ledCubeArrayWorkingBuffer[CUBE_LAYER_COUNT * CUBE_LAYER_LEDS_PER_LINE * CUBE_LAYER_LINES] = 
	{	
		//{{0}}		
		//Layer 1
		{{0x7f, 0x00, 0x00}}, 
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},

		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},

		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},

		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		
		//Layer 2
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},

		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},

		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},

		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},

		//Layer 3
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},

		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},

		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},

		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},

		//Layer 4
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},
		{{0x7f, 0x00, 0x00}},

		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},
		{{0x00, 0x7f, 0x00}},

		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},
		{{0x00, 0x00, 0x7f}},

		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}},
		{{0x7f, 0x7f, 0x7f}}		
	};

	WS2812_GRB_BYTES ledCubeArrayOutputBuffer[CUBE_LAYER_COUNT * CUBE_LAYER_LEDS_PER_LINE * CUBE_LAYER_LINES] =
	{
		{{0}}
	};	
		
	uint8_t red = 0, blue = 0, green = 255, ledWalkCount = 0;

	#pragma region TEST
	/*test*/
	if(true)
	{

	}
	#pragma endregion

	while(1)		
	{		
		if(counter > 8)															
		{
			counter = 0;									

			//write from the ledCubeArrayOneLayerWorkingBuffer filled with a test pattern
			if(false)
			{						
				//copy working buffer to output buffer
				memcpy(ledCubeArrayOutputBuffer, ledCubeArrayWorkingBuffer, sizeof(ledCubeArrayWorkingBuffer));
							
				//remap the just made array
				LEDCubeArrayRemap(&LEDCube, ledCubeArrayOutputBuffer);
									
				//write the array to the LEDs - this may be too slow...
				for(int ledCount = 0; ledCount < NUM_OF_LEDS_PER_CUBE; ++ledCount)
				{
					WS2812_GRB_BYTES ledBytes;
					ledBytes.data[0] = ledCubeArrayOutputBuffer[ledCount].data[0];
					ledBytes.data[1] = ledCubeArrayOutputBuffer[ledCount].data[1];
					ledBytes.data[2] = ledCubeArrayOutputBuffer[ledCount].data[2];					

					Ws2812WriteLEDBytes(&ledBytes);
				}
					
				Ws2812WriteResCode();
			}

			//Start moving a red LED from left to right 0,0 to 4,4. One is added so the 15th LED can be cleared (15+1 = 16 counts)
			if(true)
			{
				if(ledWalkCount <= NUM_OF_LEDS_PER_CUBE)
				{
					//clear the array and initialize first pixel as green
					if(ledWalkCount == 0)
					{
						ledCubeArrayWorkingBuffer[0].data[0] = green;
						ledCubeArrayWorkingBuffer[0].data[1] = red;
						ledCubeArrayWorkingBuffer[0].data[2] = blue;
					}
					
					else if(ledWalkCount < NUM_OF_LEDS_PER_CUBE)
					{
						ledCubeArrayWorkingBuffer[ledWalkCount].data[0] = ledCubeArrayWorkingBuffer[ledWalkCount-1].data[0];
						ledCubeArrayWorkingBuffer[ledWalkCount].data[1] = ledCubeArrayWorkingBuffer[ledWalkCount-1].data[1];
						ledCubeArrayWorkingBuffer[ledWalkCount].data[2] = ledCubeArrayWorkingBuffer[ledWalkCount-1].data[2];												

						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[0] = 0;
						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[1] = 0;
						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[2] = 0;
					}
					
					else
					{
						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[0] = 0;
						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[1] = 0;
						ledCubeArrayWorkingBuffer[ledWalkCount-1].data[2] = 0;
					}
					
					//copy working buffer to output buffer
					memcpy(ledCubeArrayOutputBuffer, ledCubeArrayWorkingBuffer, sizeof(ledCubeArrayWorkingBuffer));

					//remap the just made array
					LEDCubeArrayRemap(&LEDCube, ledCubeArrayOutputBuffer);
					
					//write the array to the LEDs - this may be too slow...
					for(int ledCount = 0; ledCount < NUM_OF_LEDS_PER_CUBE; ++ledCount)
					{
						WS2812_GRB_BYTES ledBytes;
						ledBytes.data[0] = ledCubeArrayOutputBuffer[ledCount].data[0];
						ledBytes.data[1] = ledCubeArrayOutputBuffer[ledCount].data[1];
						ledBytes.data[2] = ledCubeArrayOutputBuffer[ledCount].data[2];

						Ws2812WriteLEDBytes(&ledBytes);
					}
					
					Ws2812WriteResCode();
					
					++ledWalkCount;
					
					if(ledWalkCount > NUM_OF_LEDS_PER_CUBE)
						ledWalkCount = 0;
				}				
			}																												
		}
		
		if(timerTick)		
		{
			timerTick = false;
			counter++;
		}
	}
}