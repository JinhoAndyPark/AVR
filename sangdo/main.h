/*==============================================================================
 *
 *   Main Header File
 *
 *    	File Name   	: main.h
 *    	Version        	: 1.4
 *    	Date           	: 2006.07.27
 *		Modified       	: 2007.01.09 By Pyo, Yoon-Seok
 *		Author         	: Pyo, Yoon-Seok  (ROBIT 1st, Kwangwoon University)
 *		MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: IAR Eebedded Workbench 4.1
 *		Copyright(c) 2007 ROBIT, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

#ifndef __MAIN_H
#define __MAIN_H

//------------------------------------------------------------------------------
//                 		=== Include Headerfile ===
//------------------------------------------------------------------------------

//-----------------------------	Common Header File -----------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "define.h"
					

//-----------------------------	AVRLIB Header File -----------------------------

#include "timer.h"			// ATmega128 Ÿ�̸� ����
#include "uart.h"			// ATmega128 UART ��� ����
#include "adc.h"			// ATmega128 ADC ����

//-----------------------------	APPLIB Header File -----------------------------

#include "sensor_adc.h"	// ���� ����� adc ���� ���
#include "motor_ax.h"		// ����(AX) ����

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Main(void);

#endif
