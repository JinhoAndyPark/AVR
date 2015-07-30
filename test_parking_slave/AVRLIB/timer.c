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

//#define TIMER0_USE_PWM		//TIMER0 을 PWM mode 로 사용
//#define TIMER2_USE_PWM		//TIMER2 을 PWM mode 로 사용

//------------------------------------------------------------------------------
//               			===== Timer Initialize =====
//------------------------------------------------------------------------------
void Init_Timer(void)         	// 타이머 초기화
{
		// 8비트 타이머
		Init_Timer0();           	//타이머0 초기화
}

//------------------------------------------------------------------------------
//               			===== Timer0 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer0(void)			// 타이머0 초기화
{                
	sbi( TIMSK, TOIE0 );     	// 타이머0 오버플로어 ON
	TCNT0 = 0;		// 타이머0 상수 
		
	TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );				// prescaler 설정
}

