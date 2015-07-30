/*==============================================================================
 *
 *   DCmotor Control Module Header
 *
 *   File Name   	: DCmotor_Control.h
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

#ifndef __DCMOTOR_CONTROL_H
#define __DCMOTOR_CONTROL_H


//------------------------------------------------------------------------------
//                       ===== Define Using PIN =====
//------------------------------------------------------------------------------

#define SPIN_POSITIVE()		sbi(PORTB, 5);	cbi(PORTB, 6);
#define SPIN_NEGATIVE()		sbi(PORTB, 6);	cbi(PORTB, 5);
#define SPIN_STOP()			sbi(PORTB, 5);	sbi(PORTB, 6);

//#define EN_PWM0()			sbi(PORTB, 4)
//#define DIS_PWM0()			cbi(PORTB, 5)


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_DCmotor_Control(void);
void Spin_Positive(U08 Speed);
void Spin_Negative(U08 Speed);
void Spin_Stop(void);
void Init_Encoder(void);
U08 Check_Dir(void);

#endif