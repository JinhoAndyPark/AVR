/*==============================================================================
 *
 *   DCmotor Control Module
 *
 *   File Name   	: DCmotor_Control.c
 *   Version        	: 1.0
 *   Date           	: 2013.01.15
 *	 Modified       	: 2013.01.15 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../define.h"
#include "DCmotor_Control.h"

//------------------------------------------------------------------------------
// * Using L298N(motor driver IC) 
// * Please, checking PIN of AVR
// * PORTC[0:7] -> FND A~Dp	,	PORTA[4:7] -> FND[1:4]
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//					===== Dynamic_FND 초기화 설정 =====
//------------------------------------------------------------------------------

void Init_DCmotor_Control(void)
{
	sbi(DDRB, 5);		//Output Positive
	sbi(DDRB, 6);		//Output Negative
}

void Spin_Positive(U08 Speed)
{
	SPIN_POSITIVE();
	OCR0 = Speed;
}

void Spin_Negative(U08 Speed)
{
	SPIN_NEGATIVE();
	OCR0 = Speed;
}

void Spin_Stop(void)
{
	SPIN_STOP();
	OCR0 = 0;
}

void Init_Encoder(void)		// 1st spin : 380p
{
	cbi(DDRB,7);
}

U08 Check_Dir(void)
{
	U08 Encoder,nDIR;
	Encoder = PINB & (1<<7);
	if(!Encoder)	nDIR = 0;
	else			nDIR = 1;
	
	return nDIR;
}

