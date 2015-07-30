/*==============================================================================
 *
 *   Dynamic Display FND Module Header
 *
 *   File Name   	: Dynamic_FND.h
 *   Version        	: 1.0
 *   Date           	: 2013.01.03
 *	 Modified       	: 2013.01.03 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/

#ifndef __DYNAMIC_FND_H
#define __DYNAMIC_FND_H


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Dynamic_FND(void);
void Display_FND_ISR(void);
void Display_FND(void);

#endif

