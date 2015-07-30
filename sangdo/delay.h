/*==============================================================================
 *
 *   Define Header File
 *
 *        File Name   		: Delay.h
 *        Version        	: 1.1
 *        Date           	: 2005.07.02
 *        Author         	: Kooksun Lee (ROLAB 20th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By L.K.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __DELAY_H
#define __DELAY_H

//-------------------------------------------------------------------------------
//							Include Header Files
//-------------------------------------------------------------------------------
#include <iom128.h>
#include "Define.h"

//-------------------------------------------------------------------------------
//							Function Declaration
//--------------------------------------------------------------------------------
void Delay_us(U16 time_us);
void Delay_ms(U16 time_ms);
void Delay(U16 time);

#endif
