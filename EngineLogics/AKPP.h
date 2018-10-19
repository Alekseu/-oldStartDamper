///*
// * AKPP.h
// *
// *  Created on: 16 окт. 2018 г.
// *      Author: hudienko_a
// */
//
//#ifndef ENGINELOGICS_AKPP_H_
//#define ENGINELOGICS_AKPP_H_
//
//#include <avr/io.h>
//#include <avr/interrupt.h>
//
//extern "C" void INT1_vect(void) __attribute__ ((signal));
//extern "C" void TIMER0_OVF_vect(void) __attribute__ ((signal));
//
//#define IMPULSE_COUNT_PER_CILOMETER 40
//
//#define SPEED_GIDRO 45
//#define SPEED_FORTH 85
//
//class AKPP
//{
//public:
//
//	AKPP();
//
//	void init();
//
//
//	void interruptWrapper();
//	void timeInterrupt();
//
//	void Processing();
//
//
//private:
//	static AKPP* pObject;
//	int _mainCounter;
//	int _speedPerHour;
//	friend void INT1_vect(void);
//	friend void TIMER0_OVF_vect(void);
//
//};
//
//
//#endif /* ENGINELOGICS_AKPP_H_ */
