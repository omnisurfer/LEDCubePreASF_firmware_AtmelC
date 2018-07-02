/*
 * LEDCube.h
 *
 * Created: 2/28/2016 11:25:23 AM
 *  Author: Daniel
 *  Purpose: Defines how the LED cube is physically arranged.
 */ 


#ifndef LEDCUBE_H_
#define LEDCUBE_H_

#include "../processor/processor.h"
#include "../drivers/ws2812/ws2812.h"

/*
	Cube Origin defines where the 0,0 coordinate is located on the first layer.
*/
typedef enum
{
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	TOP_LEFT,
	TOP_RIGHT	
} CubeOrigin;

/*
	Cube Climb Direction defines how the data signal gets to the next layer in the cube stack. If the origin is at the floor of the cube, then it must "climb" to ceiling.
*/
typedef enum
{
	FLOOR_TO_CEILING,
	CEILING_TO_FLOOR	
} CubeClimbDirection;

/*
	Cube Physical Layout defines how the data signal on the cube is physically wired.
	-SWITCHBACK: At the end of a line in the layer, the count reverses counting from the "end" until it reaches the "beginning" of the next line.
		i.e. 4x4 (16 LEDs) Layer with origin at bottom left.

		12--15
		8--->
		<---4
		0--->

	-COMB: At the end of a line in the layer, the count returns to the "beginning" of the next line and counts up toward the "end" of that line. Like a typewriter carriage return.
		i.e. 4x4 Layer with origin at bottom left.

		11--15
		8--->
		4--->
		0--->
*/
typedef enum
{
	SWITCHBACK,
	COMB	
} CubePathLayout;

/*
	Cube Travel Direction defines if the next LED from origin occurs to the right or left.
*/
typedef enum
{
	LEFT_TO_RIGHT,
	RIGHT_TO_LEFT	
} CubeTravelDirection;

typedef enum
{
	NONE
} CubeBridging;

typedef enum
{
	RENDER_PENDING	
}ArrayContainerStatus;

typedef struct LED_CUBE_DEFINITION LED_CUBE_DEFINITION;

struct LED_CUBE_DEFINITION
{
	CubeOrigin cubeOrigin;
	CubeClimbDirection cubeClimbDirection;
	CubePathLayout cubePathLayout;
	CubeTravelDirection cubeTravelDirection;
	CubeBridging cubeBridging;

	uint8_t cubeLayerLEDsPerLine;
	uint8_t cubeLayerLineCount;
	uint8_t cubeLayerCount;	
};

typedef struct LED_CUBE_ARRAY_CONTAINER LED_CUBE_ARRAY_CONTAINER;

struct LED_CUBE_ARRAY_CONTAINER
{
	WS2812_GRB_BYTES ledBytes;
	ArrayContainerStatus containerStatus;
};

void LEDCubeArrayRemap(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes);

#endif /* LEDCUBE_H_ */