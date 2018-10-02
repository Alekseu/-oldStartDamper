/*
 * Benzo.h
 *
 *  Created on: 17 сент. 2018 г.
 *      Author: hudienko_a
 */

#ifndef ENGINELOGICS_BENZO_H_
#define ENGINELOGICS_BENZO_H_
#include<util/delay.h>
#include "../Driver/Platform.h"


class Benzo
{
public:

	Benzo()
	{
		first_start=0;
	}


	void init()
	{
		BENZO_DDR |=BENZO;
		BENZO_PORT&=~BENZO;

		OIL_PRESSURE_DDR&=~OIL_PRESSURE_WARNING;
		OIL_PRESSURE_PORT|=OIL_PRESSURE_WARNING;

		if((OIL_PRESSURE_PIN & BENZO)==0 && first_start==0)
		{
			BENZO_PORT|=BENZO;
			_delay_ms(10000);
			BENZO_PORT&=~BENZO;
		}
	}


	void processing()
	{
		if(!(OIL_PRESSURE_PIN & BENZO))
		{
			BENZO_PORT|=BENZO;
		}
		else
		{
			BENZO_PORT&=~BENZO;
		}
	}

private:
	unsigned char first_start;
};




#endif /* ENGINELOGICS_BENZO_H_ */
