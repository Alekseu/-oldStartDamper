/*
 * main.cpp
 *
 *  Created on: 30 рту. 2018 у.
 *      Author: hudienko_a
 */
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>

//#include"EngineLogics/Benzo.h"
//Benzo _benz;

int main(void)
{

	//_benz.init();
	DDRC =0xFF;
	PORTC=0x00;

	int _impulse = 2;
	int _out_impulse = 1;


	for(;;)
	{
		//_benz.processing();
		PORTC |=(1<<5);
		_delay_ms(_impulse);
		PORTC &=~(1<<5);
		_delay_ms(_out_impulse);

		PORTC |=(1<<4);
		_delay_ms(_impulse);
		PORTC &=~(1<<4);
		_delay_ms(_out_impulse);

		PORTC |=(1<<3);
		_delay_ms(_impulse);
		PORTC &=~(1<<3);
		_delay_ms(_out_impulse);

		PORTC |=(1<<2);
		_delay_ms(_impulse);
		PORTC &=~(1<<2);
		_delay_ms(_out_impulse);


	}

return 0;
} //main ends here


