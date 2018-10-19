/*
 * main.cpp
 *
 *  Created on: 30 рту. 2018 у.
 *      Author: hudienko_a
 */
#include <avr/io.h>
#include "Driver/delay.h"
#include "Driver/lcd.h"
#include"Driver/Adc.h"

volatile int _mainInt0Count=0;
volatile int _mainInt1Count=0;

volatile unsigned int _int0Count=0;
volatile unsigned char _timer1Counter=0;

volatile unsigned int _int1Count=0;
volatile unsigned char _timer2Counter=0;

ISR(INT0_vect)
{
	_int0Count++;
}

ISR(INT1_vect)
{
	_int1Count++;
}

ISR( TIMER1_OVF_vect) //100ms
{
	TCNT1H=0xCF2C >> 8;
	TCNT1L=0xCF2C & 0xff;

	//LED_PORT^=LED;

	if(_timer1Counter++>=5)
	{
		_timer1Counter=0;
		_mainInt0Count = _int0Count*120;
		_int0Count=0;
	}

	if(_timer2Counter++>=10)
	{
		_timer2Counter=0;
		_mainInt1Count = (_int1Count*60)*60;
		_int1Count=0;
	}

}

void writeByte(char b)
{
	while (!(UCSRA & (1 << UDRE)));
			UDR = b;
}


int main(void)
{

//	DDRC=0xFF;
//	PORTC=0x00;
//	DDRC &= ~(1 << 0);
//	DDRC &= ~(1 << 1);
//	DDRC &= ~(1 << 5);
//	PORTC |= (1 << 0);
//	PORTC |= (1 << 1);
//	PORTC &=~(1 << 5);
//	PORTC|=(1<<2);


	//DDRD =0xFF;
	//PORTD=0x00;

	// Port D initialization
	// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=Out Bit0=Out
	DDRD=(1<<DDD7) | (1<<DDD6) | (1<<DDD5) | (1<<DDD4) | (0<<DDD3) | (0<<DDD2) | (1<<DDD1) | (1<<DDD0);
	// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=0 Bit0=0
	PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

	LED_DDR|=LED;
	LED_PORT&=~LED;


	delay_init();

	// External Interrupt(s) initialization
	// INT0: On
	// INT0 Mode: Falling Edge
	// INT1: On
	// INT1 Mode: Falling Edge
	GICR|=(1<<INT1) | (1<<INT0);
	MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
	GIFR=(1<<INTF1) | (1<<INTF0);


	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 125,000 kHz
	// Mode: Normal top=0xFFFF
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer Period: 0,1 s
	// Timer1 Overflow Interrupt: On
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
	TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (1<<CS11) | (1<<CS10);
	TCNT1H=0xCF;
	TCNT1L=0x2C;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
	OCR1BL=0x00;

	TIMSK|= (1<<TOIE1);

	UBRRL=103;
	UCSRB=(1<<TXEN)|(1<<RXEN);
	UCSRC=(1<<URSEL)|(3<<UCSZ0);

	sei();

	lcd_init();
	lcd_clear();

	adc_init();
	int _proAdc;

	for(;;)
	{
		_proAdc = adc_read(5);

		lcd_gotoxy(0,0);
		lcd_str("Int0: ");
		lcd_gotoxy(35,0);
		lcd_putchar((_mainInt0Count/10000%10)+0x30);
		lcd_putchar((_mainInt0Count/1000%10)+0x30);
		lcd_putchar((_mainInt0Count/100%10)+0x30);
		lcd_putchar((_mainInt0Count/10%10)+0x30);
		lcd_putchar((_mainInt0Count%10)+0x30);

		lcd_gotoxy(0,1);
		lcd_str("Int1: ");
		lcd_gotoxy(35,1);
		lcd_putchar((_mainInt1Count/10000%10)+0x30);
		lcd_putchar((_mainInt1Count/1000%10)+0x30);
		lcd_putchar((_mainInt1Count/100%10)+0x30);
		lcd_putchar((_mainInt1Count/10%10)+0x30);
		lcd_putchar((_mainInt1Count%10)+0x30);


		lcd_gotoxy(0,3);
		lcd_str("Adc0: ");
		lcd_gotoxy(35,3);
		lcd_putchar((_proAdc/10000%10)+0x30);
		lcd_putchar((_proAdc/1000%10)+0x30);
		lcd_putchar((_proAdc/100%10)+0x30);
		lcd_putchar((_proAdc/10%10)+0x30);
		lcd_putchar((_proAdc%10)+0x30);

		delay_ms(300);

	}

return 0;
} //main ends here


