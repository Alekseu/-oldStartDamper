/*
 * main.cpp
 *
 *  Created on: 30 авг. 2018 г.
 *      Author: hudienko_a
 */
#include <avr/io.h>
#include <util/delay.h>

//todo ƒобавить отслеживание оборотов
//todo добавить подстройку положени€ заслонки в зависимости от температуры и оборотов

//#include"EngineLogics/Benzo.h"
#include "Driver/Stepper.h"
#include "Driver/Adc.h"
#include "EngineLogics/AKPP.h"


//Benzo _benz;
Stepper _step;
AKPP _akpp;
//общее колличество шаов 180градусов
int counter=0;
bool continue_=true;

bool SearchStart()
{
	continue_=true;
	counter=0;
	//поиск стартового положени€
		while(continue_)
		{
			if((PINC &(1<<0))==0 )
			{
				PORTC&=~(1<<2);
				continue_ = false;
			}
			else
			{
				PORTC|=(1<<2);
			}

			if(!continue_) break;

			if(counter++>=700)
			{
				break;
			}
			_step.MultiStep(2,false);
		}

		if(counter>=700) return false;
		return true;
}

bool SearchEnd()
{
	counter=0;
	continue_ = true;
	PORTC|=(1<<2);

	//поиск стопового положени€
	while(continue_)
	{

		if((PINC &(1<<1))==0 )
		{
			PORTC&=~(1<<2);
			continue_ =false;
		}
		else
		{
			PORTC|=(1<<2);
		}

		if(!continue_) break;

		if(counter++>=700)
		{
			break;
		}
		_step.MultiStep(2,true);
	}

	if(counter++>=700) return false;

	counter = counter*2;
	return true;
}

int main(void)
{
	_akpp.init();
	//_benz.init();
	DDRC=0xFF;
	PORTC=0x00;
	DDRC &= ~(1 << 0);
	DDRC &= ~(1 << 1);
	DDRC &= ~(1 << 5);
	PORTC |= (1 << 0);
	PORTC |= (1 << 1);
	PORTC &=~(1 << 5);

	PORTC|=(1<<2);


	DDRD =0xFF;
	PORTD=0x00;
	_step.init();
	adc_init();

	int current_stap =0;
	int adc=0;
	int _proAdc=0;

	if(!SearchStart()) {while(true);}

	if(!SearchEnd()){ SearchStart(); while(true);}

	//возврат на старт
	_step.MultiStep(counter,false);

	for(;;)
	{
		_akpp.Processing();
		//_benz.processing();
		if((PINC &(1<<0))==0 || (PINC &(1<<1))==0 )
		{
			PORTC&=~(1<<2);
		}
		else
		{
			PORTC|=(1<<2);
		}

		_proAdc = adc_read(5);

		adc = (_proAdc*1.22);

		if(current_stap<adc  && (adc-current_stap)>10 && (PINC &(1<<1))!=0 )
		{
			_step.MultiStep(2,true);
			current_stap+=2;
		}
		else if(current_stap>adc && (current_stap-adc)>10 && (PINC &(1<<0))!=0 )
		{
			_step.MultiStep(2,false);
			current_stap-=2;
		}


	}

return 0;
} //main ends here


