/*
 * Servo.h
 *
 *  Created on: 17 сент. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_SERVO_H_
#define DRIVER_SERVO_H_
#include<avr/io.h>


void servo_init()
{
	DDRB |= (1 << 1); // Set PB1 as output

	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM12)  | (1<<WGM13) | (1<<CS11);

	ICR1 = 25000;    //period = 20 ms   ICR1 = (time[us] * F_CPU[MHz] / prescaler) - 1

}


void set_servo(int pol)
{
	OCR1A = pol;
}



#endif /* DRIVER_SERVO_H_ */
