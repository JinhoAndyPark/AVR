/*==============================================================================
 *
 *   Packet Making Header
 *
 *   File Name   	: Stepmotor.h
 *   Version        	: 1.0
 *   Date           	: 2013.05.26
 *	 Modified       	: 2013.05.26 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/
#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#include <avr/io.h>			//ATmega128 I/O Header
#include <util/delay.h>
#include "../define.h"

#define FORWARD			0
#define BACKWARD		1

#define STPULSEWIDE		400
#define STEP05MM		320

void X_StepMotor_Move_1step( U08 Direction );
void Y_StepMotor_Move_1step( U08 Direction );
void Position_Homing(void);
void Moving_StartPoint(void);
void Moving_XYCoordinate(U08 XCd, U08 YCd);

#endif
