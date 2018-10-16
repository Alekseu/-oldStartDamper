/*
 * AKPP.cpp
 *
 *  Created on: 16 окт. 2018 г.
 *      Author: hudienko_a
 */

#include "AKPP.h"
#include "../Driver/Platform.h"

AKPP* AKPP::pObject = 0;
int _timeCounter;

void INT1_vect(){
	AKPP::pObject->interruptWrapper();
}

void TIMER0_OVF_vect(void)
{
	if(_timeCounter++>=100)
	{
		_timeCounter=0;
		AKPP::pObject->timeInterrupt();
	}
	TCNT0=0x8A;
}

AKPP::AKPP()
{
	_mainCounter=0;
	_timeCounter=0;
	_speedPerHour=0;
	pObject = this;
}

void AKPP::init()
{

	GIDRO_BLOCK_DDR |=GIDRO_BLOCK;
	FORTH_GEAR_DDR|=FORTH_GEAR;
	GIDRO_BLOCK_PORT&=~GIDRO_BLOCK;
	FORTH_GEAR_PORT&=~FORTH_GEAR;

		DDRD  &= ~(0<<PD3);

		// External Interrupt(s) initialization
		// INT0: Off
		// INT1: On
		// INT1 Mode: Rising Edge
		GICR|=(1<<INT1) ;
		MCUCR|=(1<<ISC11) | (1<<ISC10) ;
		GIFR |=(1<<INTF1);


		// Timer/Counter 1 initialization
		// Clock source: System Clock
		// Clock value: Timer1 Stopped
		// Mode: Normal top=0xFFFF
		// OC1A output: Disconnected
		// OC1B output: Disconnected
		// Noise Canceler: Off
		// Input Capture on Falling Edge
		// Timer1 Overflow Interrupt: Off
		// Input Capture Interrupt: Off
		// Compare A Match Interrupt: Off
		// Compare B Match Interrupt: Off
		TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
		TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
		TCNT1H=0x00;
		TCNT1L=0x00;
		ICR1H=0x00;
		ICR1L=0x00;
		OCR1AH=0x00;
		OCR1AL=0x00;
		OCR1BH=0x00;
		OCR1BL=0x00;

		// Timer(s)/Counter(s) Interrupt(s) initialization
		TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<TOIE0);
}

void AKPP::interruptWrapper()
{
	_mainCounter++;
}

void  AKPP::timeInterrupt()
{
	_speedPerHour = ((_mainCounter/IMPULSE_COUNT_PER_CILOMETER)*3600);
	_mainCounter=0;
}

void AKPP::Processing()
{
	if(_speedPerHour<SPEED_GIDRO)
	{
		GIDRO_BLOCK_PORT&=~GIDRO_BLOCK;
	}
	else
	if(_speedPerHour>=SPEED_GIDRO)
	{
		GIDRO_BLOCK_PORT|=GIDRO_BLOCK;
	}

	if(_speedPerHour<SPEED_FORTH)
	{
		FORTH_GEAR_PORT&=~FORTH_GEAR;
	}
	else
		if(_speedPerHour>=SPEED_FORTH)
		{
			FORTH_GEAR_PORT|=FORTH_GEAR;
		}

}

