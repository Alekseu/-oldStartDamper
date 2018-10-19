/*
 * ColdStarter.h
 *
 *  Created on: 19 окт. 2018 г.
 *      Author: hudienko_a
 */

#ifndef ENGINELOGICS_COLDSTARTER_H_
#define ENGINELOGICS_COLDSTARTER_H_

#include "../Driver/Stepper.h"
#include "../Driver/Adc.h"

//todo Добавить отслеживание оборотов
//todo добавить подстройку положения заслонки в зависимости от температуры и оборотов

class ColdStarter
{
public:

	ColdStarter()
	{
		counter=0;
		continue_=true;
		current_stap =0;
		adc=0;
		_proAdc=0;
	}

	void init()
	{
		_step.init();
		adc_init();
		if(!SearchStart()) {while(true);}

		if(!SearchEnd()){ SearchStart(); while(true);}

		//возврат на старт
		_step.MultiStep(counter,false);
	}

	void Processing()
	{
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

private:
	Stepper _step;
	//общее колличество шаов 180градусов
	int counter;
	bool continue_;
	int current_stap;
	int adc;
	int _proAdc;

	bool SearchStart()
	{
		continue_=true;
		counter=0;
		//поиск стартового положения
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

		//поиск стопового положения
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


};


#endif /* ENGINELOGICS_COLDSTARTER_H_ */
