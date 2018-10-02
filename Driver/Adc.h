/*
 * Adc.h
 *
 *  Created on: 17 сент. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

#include <avr/io.h>

void adc_init()
{
	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128

}

uint16_t adc_read(uint8_t ch)
{
	 //Select ADC Channel ch must be 0-7
	   ch=ch&0b00000111;
	   ADMUX|=ch;

	   //Start Single conversion
	   ADCSRA|=(1<<ADSC);

	   //Wait for conversion to complete
	   while(!(ADCSRA & (1<<ADIF)));

	   ADCSRA|=(1<<ADIF);

	   return(ADC);
}


#endif /* DRIVER_ADC_H_ */
