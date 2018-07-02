/*
 * port_hal.c
 *
 * Created: 7/26/2015 2:34:23 PM
 *  Author: Daniel
 */ 

#include "port_hal.h"

bool WritePort(PortName portName, char data)
{
	//which port to write to
	switch(portName)
	{				
		case PORT_A:
		PORTA.OUT = data;
		break;

		case PORT_B:
		PORTB.OUT = data;
		break;

		case PORT_C:
		PORTC.OUT = data;
		break;

		case PORT_D:
		PORTD.OUT = data;
		break;
		
		case PORT_E:
		PORTE.OUT = data;
		break;
		
		case PORT_F:
		PORTE.OUT = data;
		break;
		
		case PORT_R:
		PORTR.OUT = data;
		break;
						
		default:
		break;
	}
	return 0;
}

char ReadPort(PortName portName)
{	
	//which port to write to
	switch(portName)
	{
		case PORT_A:
		return PORTA.IN;
		break;

		case PORT_B:
		return PORTB.IN;
		break;

		case PORT_C:
		return PORTC.IN;
		break;

		default:
		break;
	}
	return 0x00;
}

bool WritePin(PortName portName, PortPin pinName, bool state)
{
	switch(portName)
	{		
		case PORT_A:
			if(state)					
				PORTA.OUT |= (0x01 << pinName);
				
			else
				PORTA.OUT &= ~(0x01 << pinName);											
		break;
		
		case PORT_B:
			if(state)
				PORTB.OUT |= (0x01 << pinName);
			else
				PORTB.OUT &= ~(0x01 << pinName);
				
		break;
		
		case PORT_C:
			if(state)
				PORTC.OUT |= (0x01 << pinName);
			else
				PORTC.OUT &= ~(0x01 << pinName);
				
		break;
		
		case PORT_D:
			if(state)
				PORTD.OUT |= (0x01 << pinName);
			else
				PORTD.OUT &= ~(0x01 << pinName);
				
		break;
		
		case PORT_E:
			if(state)
				PORTE.OUT |= (0x01 << pinName);
			else
				PORTE.OUT &= ~(0x01 << pinName);
				
		break;
		
		case PORT_F:
			if(state)
				PORTF.OUT |= (0x01 << pinName);
			else
				PORTF.OUT &= ~(0x01 << pinName);
				
		break;
						
		case PORT_R:					
			if(state)			
				PORTR.OUT |= (0x01 << pinName);								
			else
				PORTR.OUT &= ~(0x01 << pinName);							
		break;
										
		default:
			return true;
		break;				
	}

	return false;
}

bool ReadPin(PortName portName, PortPin pinName)
{			
	switch(portName)
	{
		case PORT_A:
			return PORTA.IN & (0x01 << pinName);
		break;
		
		case PORT_B:
			return PORTB.IN & (0x01 << pinName);
		break;
		
		case PORT_C:
			return PORTC.IN & (0x01 << pinName);
		break;
		
		case PORT_D:
			return PORTD.IN & (0x01 << pinName);
		break;
		
		case PORT_E:
			return PORTE.IN & (0x01 << pinName);
		break;
		
		case PORT_F:
			return PORTF.IN & (0x01 << pinName);
		break;
		
		case PORT_R:
			return PORTR.IN & (0x01 << pinName);
		break;
		
		default:
			return false;
		break;		
	}		
}

bool SetPortPinDirection(PortName portName, PortPin pinName, PortDirection direction)
{
	switch (portName)
	{
		case PORT_A:
			if(direction == PORT_OUTPUT)			
				PORTA.DIR |= (0x01 << pinName);			
			else
				PORTA.DIR &= ~(0x01 << pinName);		
			return true;
		break;
		
		case PORT_R:
			if(direction == PORT_OUTPUT)
				PORTR.DIR |= (0x01 << pinName);
			else
				PORTR.DIR &= ~(0x01 << pinName);		
			return true;
		break;
		
		default:
		break;
	}
	return false;
}