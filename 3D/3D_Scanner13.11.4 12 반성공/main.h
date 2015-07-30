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

//#include "AVRLIB/io.h"			// ATmega128 입/출력 제어
#include "AVRLIB/ext_interrupt.h"		// ATmega128 외부인터럽트 제어
#include "AVRLIB/timer.h"			// ATmega128 타이머 제어
#include "AVRLIB/uart.h"			// ATmega128 UART 통신 제어
#include "AVRLIB/adc.h"			// ATmega128 ADC 제어
//#include "AVRLIB/spi.h"			// ATmega128 SPI 통신 제어
//#include "AVRLIB/twi.h"			// ATmega128 TWI 통신 제어
//#include "AVRLIB/eeprom.h"			// ATmega128 eeprom 메모리 제어

//-----------------------------	APPLIB Header File -----------------------------

//#include "APPLIB/sensor_adc.h"	// 폴링 방식의 adc 검출 모듈
//#include "APPLIB/sensor_calc.h"	// 센서 계산 함수 모듈
//#include "APPLIB/sensor_sonic.h"	// 센서(적외선) 제어
//#include "APPLIB/sensor_ir.h"		// 센서(초음파) 제어

//#include "APPLIB/data_ir.h"		// IR 리모콘 데이타 수신 제어
//#include "APPLIB/data_packet2.h"	// 2바이트 데이타 패킷 생성 및 분석
//#include "APPLIB/data_packet5.h"	// 5바이트 데이타 패킷 생성 및 분석

//#include "APPLIB/lcd_hlcd158.h"	// LCD(HLCD158) 제어
//#include "APPLIB/lcd_text.h"		// LCD(16*2) 제어
//#include "APPLIB/lcd_text4bit.h"	// LCD(12*4) 제어 :: 4비트데이타전송

//#include "APPLIB/motor_step.h"	// 모터(STEP) 제어
//#include "APPLIB/motor_dc.h"		// 모터(DC) 제어
//#include "APPLIB/motor_ax.h"		// 모터(AX) 제어
//#include "APPLIB/motor_dx.h"		// 모터(DX) 제어
//#include "APPLIB/motor_dx_set.h"	// 모터(DX) 셋팅
//#include "APPLIB/motor_step_table.h"	// 모터(STEP) 가감속테이블

//#include "APPLIB/ansi.h"		// ANSI Terminal Contorol
//#include "APPLIB/ansi_menu.h"		// ANSI MENU

//#include "APPLIB/segment_hex.h"         // 7-Segment
//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Main_Init(void);

#endif
