/*==============================================================================
 *
 *   Main Header File
 *
 *    	File Name   	: main.h
 *    	Version        	: 1.0
 *    	Date           	: 2013.10.30
 *	Modified       	: 2013.10.30 By Park, Jin-Ho
 *	Author         	: By Park, Jin-Ho  (27th)
 *	MPU_Type       	: ATmega128(16MHz)
 *	Compiler		: WINAVR use AVRstudio 4.18
 *	Copyright(c) ROLAB, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

#ifndef __MAIN_H
#define __MAIN_H


#define CW				0
#define CCW				1

//------------------------------------------------------------------------------
//                 		=== Include Headerfile ===
//------------------------------------------------------------------------------

//-----------------------------	Common Header File -----------------------------

#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header

#include "define.h"
					

//-----------------------------	AVRLIB Header File -----------------------------

//#include "AVRLIB/io.h"			// ATmega128 ��/��� ����
#include "AVRLIB/ext_interrupt.h"		// ATmega128 �ܺ����ͷ�Ʈ ����
#include "AVRLIB/timer.h"			// ATmega128 Ÿ�̸� ����
#include "AVRLIB/uart.h"			// ATmega128 UART ��� ����
#include "AVRLIB/adc.h"			// ATmega128 ADC ����
//#include "AVRLIB/spi.h"			// ATmega128 SPI ��� ����
//#include "AVRLIB/twi.h"			// ATmega128 TWI ��� ����
//#include "AVRLIB/eeprom.h"			// ATmega128 eeprom �޸� ����

//-----------------------------	APPLIB Header File -----------------------------

//#include "APPLIB/sensor_adc.h"	// ���� ����� adc ���� ���
//#include "APPLIB/sensor_calc.h"	// ���� ��� �Լ� ���
//#include "APPLIB/sensor_sonic.h"	// ����(���ܼ�) ����
//#include "APPLIB/sensor_ir.h"		// ����(������) ����

//#include "APPLIB/data_ir.h"		// IR ������ ����Ÿ ���� ����
//#include "APPLIB/data_packet2.h"	// 2����Ʈ ����Ÿ ��Ŷ ���� �� �м�
//#include "APPLIB/data_packet5.h"	// 5����Ʈ ����Ÿ ��Ŷ ���� �� �м�

//#include "APPLIB/lcd_hlcd158.h"	// LCD(HLCD158) ����
//#include "APPLIB/lcd_text.h"		// LCD(16*2) ����
//#include "APPLIB/lcd_text4bit.h"	// LCD(12*4) ���� :: 4��Ʈ����Ÿ����

//#include "APPLIB/motor_step.h"	// ����(STEP) ����
//#include "APPLIB/motor_dc.h"		// ����(DC) ����
//#include "APPLIB/motor_ax.h"		// ����(AX) ����
//#include "APPLIB/motor_dx.h"		// ����(DX) ����
//#include "APPLIB/motor_dx_set.h"	// ����(DX) ����
//#include "APPLIB/motor_step_table.h"	// ����(STEP) ���������̺�

//#include "APPLIB/ansi.h"		// ANSI Terminal Contorol
//#include "APPLIB/ansi_menu.h"		// ANSI MENU

//#include "APPLIB/segment_hex.h"         // 7-Segment
//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Main_Init(void);

#endif
