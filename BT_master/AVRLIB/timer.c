/*==============================================================================
 *
 *   Timer Module
 *
 *      File Name   	: timer.c
 *    	Version        	: 1.0
 *    	Date           	: 2012.12.24
 *	Modified       	: 2012.12.24 By Kim, Hyun-Jun
 *	Author         	: Kim, Hyun-Jun  (23rd)
 *	MPU_Type       	: ATmega128(16MHz)
 *	Compiler	: WINAVR use AVRstudio 4.18
 *	Copyright(c) ROLAB, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>
#include "../define.h"
#include "timer.h"

//------------------------------------------------------------------------------
//		===== SELECT mode =====
//*사용하고자 하는 기능을 define 해준다.  주석처리 시 nomal Timer
//------------------------------------------------------------------------------

#define TIMER0_USE_PWM		//TIMER0 을 PWM mode 로 사용
//#define TIMER2_USE_PWM		//TIMER2 을 PWM mode 로 사용

//------------------------------------------------------------------------------
//               			===== Timer Initialize =====
//------------------------------------------------------------------------------
void Init_Timer(void)         	// 타이머 초기화
{
		// 8비트 타이머
		Init_Timer0();           	//타이머0 초기화
		//Init_Timer2();           	//타이머2 초기화
		
        // 16비트 타이머
		Init_Timer1();           	//타이머1 초기화
		//Init_Timer3();           	//타이머3 초기화
}

//------------------------------------------------------------------------------
//               			===== Timer0 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer0(void)			// 타이머0 초기화
{
		
	#ifdef TIMER0_USE_PWM
		sbi( DDRB, 4 );		//OC0 enble
		TCNT0 = 0;
		TCCR0 = ( 1 << WGM01 ) | ( 1 << WGM00 )  | ( 0 << COM00 ) | ( 1 << COM01 ) 
				| ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		// FAST PWM mode 설정
		OCR0 = 100;

	#else                             
		sbi( TIMSK, TOIE0 );     	// 타이머0 오버플로어 ON
		TCNT0 = 0;					// 타이머0 상수
		
		TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 0 << CS02 );				// prescaler 설정
		
	#endif
}

//------------------------------------------------------------------------------
//               			===== Timer1 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer1(void)        	// 타이머1 초기화
{
	sbi( TIMSK, TOIE1 );     	// 타이머1 오버플로어 ON
	TCNT1 	= 0;          		// 타이머1 상수
	TCCR1B 	= ( 1 << CS10 ) | ( 1 << CS11 ) | ( 0 << CS12 );	// 타이머1 설정 (Normal-Mode,CLK/1)
}

//------------------------------------------------------------------------------
//               			===== Timer2 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer2(void)        	// 타이머2 초기화
{   
	#ifdef TIMER2_USE_PWM
		sbi( DDRB, 7 );		//OC0 enble
		TCCR2 = ( 1 << WGM21 ) | ( 1 << WGM20 ) | ( 0 << COM20 )| ( 1 << COM21 )
				| ( 0 << CS20 ) | ( 0 << CS21 ) | ( 0 << CS22 );	// FAST PWM mode 설정
		TCNT2 = 0;
		OCR2 = 0;

	#else
		sbi( TIMSK, TOIE2 );     	// 타이머2 오버플로어 ON
		TCNT2 = 0x00;				// 타이머2 상수
		
		TCCR2 = ( 0 << CS00 ) | ( 0 << CS01 ) | ( 0 << CS02 );				// prescaler 설정
	#endif
}

//------------------------------------------------------------------------------
//               			===== Timer3 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer3(void)        	// 타이머3 초기화
{
	sbi( ETIMSK, TOIE3 );    	// 타이머3 오버플로어 ON
	TCNT3 	= 0;          	// 타이머3 상수
	TCCR3B 	= ( 0 << CS30 ) | ( 0 << CS31 ) | ( 0 << CS32 );           	// 타이머3 설정 (Normal-Mode,CLK/1)
}


