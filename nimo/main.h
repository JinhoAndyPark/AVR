/*==============================================================================
 *
 *   Main Header File
 *
 *    	File Name   	: main.h
 *    	Version        	: 1.0
 *    	Date           	: 2012.12.24
 *	Modified       	: 2012.12.24 By Kim, Hyun-Jun
 *	Author         	: Kim, Hyun-Jun  (23rd)
 *	MPU_Type       	: ATmega128(16MHz)
 *	Compiler		: WINAVR use AVRstudio 4.18
 *	Copyright(c) ROLAB, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

#ifndef __MAIN_H
#define __MAIN_H

//------------------------------------------------------------------------------
//                 		=== Include Headerfile ===
//------------------------------------------------------------------------------

//-----------------------------	Common Header File -----------------------------

#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header

#include "define.h"					

#include "AVRLIB/timer.h"			// ATmega128 타이머 제어
#include "AVRLIB/uart.h"			// ATmega128 UART 통신 제어
#include "AVRLIB/adc.h"			// ATmega128 ADC 제어
#include "APPLIB/lcd_text.h"		// LCD(16*2) 제어
#include "APPLIB/motor_ax.h"		// 모터(AX) 제어



void Init_Main(void);

#endif