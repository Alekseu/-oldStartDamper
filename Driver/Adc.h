/*
 * Adc.h
 *
 *  Created on: 17 сент. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

#include <avr/io.h>
#include<util/delay.h>

#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))


void adc_init()
{
//	ADMUX=(1<<REFS0);                         // For Aref=AVcc;
//	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128

	// ADC initialization
	// ADC Clock frequency: 750,000 kHz
	// ADC Voltage Reference: AVCC pin
	ADMUX=ADC_VREF_TYPE;
	ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADFR) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);
	SFIOR=(0<<ACME);

}

uint16_t adc_read(uint8_t ch)
{
//	 //Select ADC Channel ch must be 0-7
//	   ch=ch&0b00000111;
//	   ADMUX|=ch;
//
//	   //Start Single conversion
//	   ADCSRA|=(1<<ADSC);
//
//	   //Wait for conversion to complete
//	   while(!(ADCSRA & (1<<ADIF)));
//
//	   ADCSRA|=(1<<ADIF);
//
//	   return(ADC);

	ADMUX=ch | ADC_VREF_TYPE;
	// Delay needed for the stabilization of the ADC input voltage
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=(1<<ADSC);
	// Wait for the AD conversion to complete
	while ((ADCSRA & (1<<ADIF))==0);
	ADCSRA|=(1<<ADIF);
	return ADCW;
}


#endif /* DRIVER_ADC_H_ */
