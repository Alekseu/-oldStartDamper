/*
 * Stepper.h
 *
 *  Created on: 05 окт. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_STEPPER_H_
#define DRIVER_STEPPER_H_
#include"util/delay.h"
#include "Platform.h"


class Stepper
{
public:

	Stepper()
	{
		_impulse=IMPULSE_TIME;
		_currentStep=1;
	}

	void init()
	{
		STEP_MOTOR_DDR|=A_STEP_MOTOR|B_STEP_MOTOR|C_STEP_MOTOR|D_STEP_MOTOR;
		STEP_MOTOR_PORT&=~A_STEP_MOTOR|B_STEP_MOTOR|C_STEP_MOTOR|D_STEP_MOTOR;
	}




	void OneStep(bool rotation)
	{
		switch(_currentStep)
		{
		case 1:
			STEP_MOTOR_PORT |=A_STEP_MOTOR;
			_delay_us(_impulse);
			STEP_MOTOR_PORT &=~A_STEP_MOTOR;
			STEP_MOTOR_PORT &=~B_STEP_MOTOR;
			STEP_MOTOR_PORT &=~C_STEP_MOTOR;
			STEP_MOTOR_PORT &=~D_STEP_MOTOR;
			break;
		case 2:
			STEP_MOTOR_PORT |=B_STEP_MOTOR;
			_delay_us(_impulse);
			STEP_MOTOR_PORT &=~A_STEP_MOTOR;
			STEP_MOTOR_PORT &=~B_STEP_MOTOR;
			STEP_MOTOR_PORT &=~C_STEP_MOTOR;
			STEP_MOTOR_PORT &=~D_STEP_MOTOR;
			break;
		case 3:
			STEP_MOTOR_PORT |=C_STEP_MOTOR;
			_delay_us(_impulse);
			STEP_MOTOR_PORT &=~A_STEP_MOTOR;
			STEP_MOTOR_PORT &=~B_STEP_MOTOR;
			STEP_MOTOR_PORT &=~C_STEP_MOTOR;
			STEP_MOTOR_PORT &=~D_STEP_MOTOR;
			break;
		case 4:
			STEP_MOTOR_PORT |=D_STEP_MOTOR;
			_delay_us(_impulse);
			STEP_MOTOR_PORT &=~A_STEP_MOTOR;
			STEP_MOTOR_PORT &=~B_STEP_MOTOR;
			STEP_MOTOR_PORT &=~C_STEP_MOTOR;
			STEP_MOTOR_PORT &=~D_STEP_MOTOR;
			break;
		}

		if(rotation)
		{
			if(_currentStep++>=4)
			{
				_currentStep=1;
			}
		}
		else
		{
			if(_currentStep--<=1)
			{
				_currentStep=4;
			}
		}

	}

	void MultiStep(int steps, bool rotation)
	{
		for(int i=0;i<steps;i++)
		{
			OneStep(rotation);
		}
	}

private:
	int _impulse ;
	char _currentStep;
};



#endif /* DRIVER_STEPPER_H_ */
