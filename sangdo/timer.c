/*==============================================================================
 *
 *   Timer Module
 *
 *        File Name   		: timer.c
 *        Version        	: 1.1
 *        Date           	: 2005.12.11
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/
#include "main.h"
#include "define.h"
#include "timer.h"

//------------------------------------------------------------------------------
//               			===== Timer Initialize =====
//------------------------------------------------------------------------------
void Init_Timer(void)         	// 타이머 초기화
{
		// 8비트 타이머
		Init_Timer0();           	//타이머0 초기화
		//Init_Timer2();           	//타이머2 초기화
		
        // 16비트 타이머
		//Init_Timer1();           	//타이머1 초기화
		//Init_Timer3();           	//타이머3 초기화
}

//------------------------------------------------------------------------------
//               			===== Timer0 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer0(void)			// 타이머0 초기화
{                             
	sbi( TIMSK, TOIE0 );     	// 타이머0 오버플로어 ON
	TCNT0 = 131;				// 타이머0 상수
	TCCR0 = 0x07;				// 타이머0 설정 (Normal-Mode,CLK/1)
}

//------------------------------------------------------------------------------
//               			===== Timer1 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer1(void)        	// 타이머1 초기화
{
	sbi( TIMSK, TOIE1 );     	// 타이머1 오버플로어 ON
	TCNT1 	= 0x0000;          	// 타이머1 상수
	TCCR1B 	= 0x00;           	// 타이머1 설정 (Normal-Mode,CLK/1)
}

//------------------------------------------------------------------------------
//               			===== Timer2 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer2(void)        	// 타이머2 초기화
{                             
	sbi( TIMSK, TOIE2 );     	// 타이머2 오버플로어 ON
	TCNT2 = 0x00;				// 타이머2 상수
	TCCR2 = 0x00;				// 타이머2 설정 (Normal-Mode,CLK/1)
}

//------------------------------------------------------------------------------
//               			===== Timer3 Initialize =====
//------------------------------------------------------------------------------
void Init_Timer3(void)        	// 타이머3 초기화
{
	sbi( ETIMSK, TOIE3 );    	// 타이머3 오버플로어 ON
	TCNT3 	= 0x0000;          	// 타이머3 상수
	TCCR3B 	= 0x00;           	// 타이머3 설정 (Normal-Mode,CLK/1)
}
