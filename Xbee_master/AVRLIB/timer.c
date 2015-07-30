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
//*����ϰ��� �ϴ� ����� define ���ش�.  �ּ�ó�� �� nomal Timer
//------------------------------------------------------------------------------

//#define TIMER0_USE_PWM		//TIMER0 �� PWM mode �� ���
//#define TIMER2_USE_PWM		//TIMER2 �� PWM mode �� ���

//------------------------------------------------------------------------------
//               			===== Timer Initialize =====
//------------------------------------------------------------------------------
void Init_Timer(void)         	// Ÿ�̸� �ʱ�ȭ
{
		Init_Timer0();           	//Ÿ�̸�0 �ʱ�ȭ
}

//------------------------------------------------------------------------------
//               			===== Timer0 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer0(void)			// Ÿ�̸�0 �ʱ�ȭ
{
		
	#ifdef TIMER0_USE_PWM
		sbi( DDRB, 4 );		//OC0 enble
		TCNT0 = 0;
		TCCR0 = ( 1 << WGM01 ) | ( 1 << WGM00 )  | ( 0 << COM00 ) | ( 1 << COM01 ) 
				| ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		// FAST PWM mode ����
		OCR0 = 100;

	#else                             
		sbi( TIMSK, TOIE0 );     	// Ÿ�̸�0 �����÷ξ� ON
		TCNT0 = 0;		// Ÿ�̸�0 ��� 
		
		TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );				// prescaler ����
		
	#endif
}


