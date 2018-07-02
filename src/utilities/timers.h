/*
 * timers.h
 *
 * Created: 12/13/2015 9:11:16 PM
 *  Author: Daniel
 * Description: Provides an interrupt driven timer.
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "../processor/processor.h"
#include "../processor/interrupts.h"

volatile bool timerTick;

void InitTimer(void);

#endif /* TIMERS_H_ */