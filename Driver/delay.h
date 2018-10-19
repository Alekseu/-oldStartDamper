/*
 * delay.h
 *
 *  Created on: 19 окт. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_DELAY_H_
#define DRIVER_DELAY_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Platform.h"

volatile long _timerCounter=0;
volatile unsigned int _timerLedTime =0;
volatile unsigned char temp=0;

ISR( TIMER0_OVF_vect)
{
	TCNT0=0x9C;
	if(_timerCounter > 0 && temp==0)
	{
		_timerCounter--;
		//LED_PORT^=LED;
	}
	else
	{
		temp=1;
	}

	if(_timerLedTime++>=300)
	{
		_timerLedTime=0;
		LED_PORT^=LED;
	}

}

void delay_init()
{
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 8000,000 kHz
	TCCR0=(0<<CS02) | (1<<CS01) | (0<<CS00);
	TCNT0=0x9C;


	TIMSK|= (1<<TOIE0);

}

void delay_us(unsigned int us)
{
	_timerCounter = us;
	temp=0;
	while(temp==0){__asm("nop");}
}

void delay_ms(unsigned int ms)
{
	_timerCounter = ms*10;
	temp=0;
	while(temp==0){__asm("nop");}
}

#endif /* DRIVER_DELAY_H_ */
