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

#define TIMER0_USE_PWM		//TIMER0 �� PWM mode �� ���
//#define TIMER2_USE_PWM		//TIMER2 �� PWM mode �� ���

//------------------------------------------------------------------------------
//               			===== Timer Initialize =====
//------------------------------------------------------------------------------
void Init_Timer(void)         	// Ÿ�̸� �ʱ�ȭ
{
		// 8��Ʈ Ÿ�̸�
		Init_Timer0();           	//Ÿ�̸�0 �ʱ�ȭ
		//Init_Timer2();           	//Ÿ�̸�2 �ʱ�ȭ
		
        // 16��Ʈ Ÿ�̸�
		Init_Timer1();           	//Ÿ�̸�1 �ʱ�ȭ
		//Init_Timer3();           	//Ÿ�̸�3 �ʱ�ȭ
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
		
		TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 0 << CS02 );				// prescaler ����
		
	#endif
}

//------------------------------------------------------------------------------
//               			===== Timer1 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer1(void)        	// Ÿ�̸�1 �ʱ�ȭ
{
	sbi( TIMSK, TOIE1 );     	// Ÿ�̸�1 �����÷ξ� ON
	TCNT1 	= 0;          		// Ÿ�̸�1 ���
	TCCR1B 	= ( 1 << CS10 ) | ( 1 << CS11 ) | ( 0 << CS12 );	// Ÿ�̸�1 ���� (Normal-Mode,CLK/1)
}

//------------------------------------------------------------------------------
//               			===== Timer2 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer2(void)        	// Ÿ�̸�2 �ʱ�ȭ
{   
	#ifdef TIMER2_USE_PWM
		sbi( DDRB, 7 );		//OC0 enble
		TCCR2 = ( 1 << WGM21 ) | ( 1 << WGM20 ) | ( 0 << COM20 )| ( 1 << COM21 )
				| ( 0 << CS20 ) | ( 0 << CS21 ) | ( 0 << CS22 );	// FAST PWM mode ����
		TCNT2 = 0;
		OCR2 = 0;

	#else
		sbi( TIMSK, TOIE2 );     	// Ÿ�̸�2 �����÷ξ� ON
		TCNT2 = 0x00;				// Ÿ�̸�2 ���
		
		TCCR2 = ( 0 << CS20 ) | ( 0 << CS21 ) | ( 0 << CS22 );				// prescaler ����
	#endif
}

//------------------------------------------------------------------------------
//               			===== Timer3 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer3(void)        	// Ÿ�̸�3 �ʱ�ȭ
{
	sbi( ETIMSK, TOIE3 );    	// Ÿ�̸�3 �����÷ξ� ON
	TCNT3 	= 0;          	// Ÿ�̸�3 ���
	TCCR3B 	= ( 0 << CS30 ) | ( 0 << CS31 ) | ( 0 << CS32 );           	// Ÿ�̸�3 ���� (Normal-Mode,CLK/1)
}

