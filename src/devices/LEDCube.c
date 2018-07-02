/*
 * LEDCube.c
 *
 * Created: 2/28/2016 2:28:39 PM
 *  Author: Daniel
 */ 

 #include "LEDCube.h"

 void LEDCubePathCorrection_Switchback(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes);
 void LEDCubeOriginCorrection_BottomLeft(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes);

 uint8_t data0Temp = 0x00, data1Temp = 0x00, data2Temp = 0x00;

 void LEDCubeArrayRemap(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes)
 {		
 	//origin correction - done when moving up to next layer
 	switch(ledCubeDefinition->cubeOrigin)
 	{
	 	case(BOTTOM_LEFT):
	 	{
		 	LEDCubeOriginCorrection_BottomLeft(ledCubeDefinition, ws2812GrbBytes);
		 	break;
	 	}

	 	default:
	 	break;
 	}
		
	//path layout correction
	switch(ledCubeDefinition->cubePathLayout)
	{
		case(SWITCHBACK):
		{
			LEDCubePathCorrection_Switchback(ledCubeDefinition, ws2812GrbBytes);
			break;
		}

		default:
			break;
	}
		
	return;	
 }

 void LEDCubePathCorrection_Switchback(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes)
 {
	//outerloop based on number of layers
	for(int layerCount = 0; layerCount < ledCubeDefinition->cubeLayerCount; layerCount++)
	{				
		//loop based on number of lines in a layer
		for(int lineIndex = 0; lineIndex < ledCubeDefinition->cubeLayerLineCount; lineIndex++)
		{
			//LEDs on odd lines starting at 1
			if(lineIndex%2)
			{
				//loop "backwards"
				uint8_t oddLEDFwdIndexOffset = (layerCount * ledCubeDefinition->cubeLayerLineCount * ledCubeDefinition->cubeLayerLEDsPerLine) + lineIndex * ledCubeDefinition->cubeLayerLEDsPerLine,
						oddLEDRevIndexOffset = oddLEDFwdIndexOffset + (ledCubeDefinition->cubeLayerLEDsPerLine - 1);

				for(; oddLEDRevIndexOffset >= 0; oddLEDRevIndexOffset--, oddLEDFwdIndexOffset++)
				{
					if(oddLEDFwdIndexOffset > oddLEDRevIndexOffset)
					{
						break;
					}
				
					else
					{
						//temporarily store the contents of the buffer position about to be overwritten
						data0Temp = ws2812GrbBytes[oddLEDFwdIndexOffset].data[0];
						data1Temp = ws2812GrbBytes[oddLEDFwdIndexOffset].data[1];
						data2Temp = ws2812GrbBytes[oddLEDFwdIndexOffset].data[2];

						//overwrite the FwdIndex position with the contents of the RevIndex
						ws2812GrbBytes[oddLEDFwdIndexOffset].data[0] = ws2812GrbBytes[oddLEDRevIndexOffset].data[0];
						ws2812GrbBytes[oddLEDFwdIndexOffset].data[1] = ws2812GrbBytes[oddLEDRevIndexOffset].data[1];
						ws2812GrbBytes[oddLEDFwdIndexOffset].data[2] = ws2812GrbBytes[oddLEDRevIndexOffset].data[2];
					
						//place the temp contents into the RevIndex position
						ws2812GrbBytes[oddLEDRevIndexOffset].data[0] = data0Temp;
						ws2812GrbBytes[oddLEDRevIndexOffset].data[1] = data1Temp;
						ws2812GrbBytes[oddLEDRevIndexOffset].data[2] = data2Temp;
					}
				}
			}

			//LEDs on even lines, counting 0
			else
			{
				//loop "forwards", do nothing because these are already ordered correctly
			}
		}
	}
	 
	return;
 }

 void LEDCubeOriginCorrection_BottomLeft(LED_CUBE_DEFINITION *ledCubeDefinition, WS2812_GRB_BYTES *ws2812GrbBytes)
 {									
	//outerloop based on number of layers
	for(int layerCount = 0; layerCount < ledCubeDefinition->cubeLayerCount; layerCount++)
	{							
		//odd layers starting at "1" need correcting
		if(layerCount%2)
		{				
			//initialize indexes for current layer						
			uint8_t layerStartLine = layerCount * ledCubeDefinition->cubeLayerLineCount,
					layerStopLine = layerStartLine + (ledCubeDefinition->cubeLayerLineCount - 1);						
					
			/*
			Example at Layer 1:
			i = 0	layerStartLine = 4	layerStopLine = 7
			i = 1	layerStartLine = 5	layerStopLine = 6
			i = 2	layerStartLine = 6	layerStopLine = 5 (where it should stop)
			i = 3	layerStartLine = 7	layerStopLine = 4
			*/

			for(int i = 0; i < ledCubeDefinition->cubeLayerLineCount; layerStartLine++, layerStopLine--, i++)
			{												
				if(layerStartLine < layerStopLine)
				{
					uint8_t ledTopLineIndexOffset = layerStartLine * ledCubeDefinition->cubeLayerLEDsPerLine,
							ledBottomLineIndexOffset = layerStopLine * ledCubeDefinition->cubeLayerLEDsPerLine,
							ledTopLineIndexStopOffset = ledTopLineIndexOffset + (ledCubeDefinition->cubeLayerLEDsPerLine - 1);
								
					for(; ledTopLineIndexOffset <= ledTopLineIndexStopOffset; ledTopLineIndexOffset++, ledBottomLineIndexOffset++)
					{						
						//temporarily store the contents of the TopLineIndex position about to be overwritten
						data0Temp = ws2812GrbBytes[ledTopLineIndexOffset].data[0];
						data1Temp = ws2812GrbBytes[ledTopLineIndexOffset].data[1];
						data2Temp = ws2812GrbBytes[ledTopLineIndexOffset].data[2];

						//overwrite the TopLineIndex position with the contents from the BottomLineIndex
						ws2812GrbBytes[ledTopLineIndexOffset].data[0] = ws2812GrbBytes[ledBottomLineIndexOffset].data[0];
						ws2812GrbBytes[ledTopLineIndexOffset].data[1] = ws2812GrbBytes[ledBottomLineIndexOffset].data[1];
						ws2812GrbBytes[ledTopLineIndexOffset].data[2] = ws2812GrbBytes[ledBottomLineIndexOffset].data[2];

						//place the temp contents into the BottomLineIndex position
						ws2812GrbBytes[ledBottomLineIndexOffset].data[0] = data0Temp;
						ws2812GrbBytes[ledBottomLineIndexOffset].data[1] = data1Temp;
						ws2812GrbBytes[ledBottomLineIndexOffset].data[2] = data2Temp;																		
					}					
				}				
			}								
		}					
	}
	return;
 }