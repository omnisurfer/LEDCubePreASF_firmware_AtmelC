/*
 * port_hal.h
 *
 * Created: 7/26/2015 2:35:45 PM
 *  Author: Daniel
 *	Description: Basic port abstraction to make manipulating the IO ports easier. Should not be used for timing critical code. Almost 1/16 slower than writing ports directly.
 */ 

#ifndef PORT_HAL_H_
#define PORT_HAL_H_

#include "../processor/processor.h"

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
	PORT_E,
	PORT_F,
	PORT_R

} PortName;

typedef enum
{
	PIN_0 = 0x00,
	PIN_1,
	PIN_2,
	PIN_3,

	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7
} PortPin;

typedef enum
{
	PORT_INPUT,
	PORT_OUTPUT	
} PortDirection;

bool WritePort(PortName portName, char data);

char ReadPort(PortName portName);

bool WritePin(PortName portName, PortPin pinName, bool state);

bool ReadPin(PortName portName, PortPin pinName);

bool SetPortPinDirection(PortName portName, PortPin pinNames, PortDirection direction);

#endif /* PORT_HAL_H_ */