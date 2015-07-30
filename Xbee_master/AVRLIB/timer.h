/*==============================================================================
 *
 *   Timer Module
 *
 *      File Name   	: timer.h
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

#ifndef __TIMER_H
#define __TIMER_H

#define PWM_ENABLE()		TCCR0 = ( 1 << WGM01 ) | ( 1 << WGM00 ) | ( 1 << COM01 ) | ( 1 << CS01 )
#define PWM_DISABLE()		TCCR0 = ( 0 << WGM01 ) | ( 0 << WGM00 ) | ( 1 << COM01 ) | ( 1 << CS01 )

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void	Init_Timer(void);
void	Init_Timer0(void);


#endif

