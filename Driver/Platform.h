/*
 * Platform.h
 *
 *  Created on: 17 сент. 2018 г.
 *      Author: hudienko_a
 */

#ifndef DRIVER_PLATFORM_H_
#define DRIVER_PLATFORM_H_

#include<avr/io.h>

#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED (1<<7)

//обороты двигателя
#define ENGINE_SPEED_PORT PORTD
#define ENGINE_SPEED_DDR DDRD
#define ENGINR_SPEED (1<<2)

//скорость
#define SPEED_PORT PORTD
#define SPEED_DDR DDRD
#define SPEED (1<<3)

//контрольная лампа давления масла
#define OIL_PRESSURE_PORT PORTD
#define OIL_PRESSURE_PIN PIND
#define OIL_PRESSURE_DDR DDRD
#define OIL_PRESSURE_WARNING (1<<4)

//реле бензонасоса
#define BENZO_PORT PORTD
#define BENZO_DDR DDRD
#define BENZO (1<<5)

//блокировка гидротрансформатора
#define GIDRO_BLOCK_PORT PORTD
#define GIDRO_BLOCK_DDR DDRD
#define GIDRO_BLOCK (1<<6)

//управление 4-й передачей
#define FORTH_GEAR_PORT PORTD
#define FORTH_GEAR_DDR DDRD
#define FORTH_GEAR (1<<7)


//температура двигателя
#define MOTOR_TEMP_PORT PORTC
#define MOTOR_TEMP_DDR DDRC
#define MOTOR_TEMP (1<<0)
#define MOTOR_TEMP_CH 0

//датчик положения дроссельной заслонки
#define DROSSEL_LAVEL_PORT PORTC
#define DROSSEL_LAVEL_DDR  DDRC
#define DROSSEL_LAVEL (1<<1)
#define DROSSEL_LAVEL_CH 1


//настройки шагового двигателя управления заслонкой холодного пуска
#define IMPULSE_TIME 900
#define STEP_MOTOR_PORT PORTD
#define STEP_MOTOR_DDR DDRD
#define A_STEP_MOTOR (1<<0)
#define B_STEP_MOTOR (1<<1)
#define C_STEP_MOTOR (1<<2)
#define D_STEP_MOTOR (1<<3)


#endif /* DRIVER_PLATFORM_H_ */
