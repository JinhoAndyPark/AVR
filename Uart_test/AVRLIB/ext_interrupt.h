/*==============================================================================
 *
 *   External Interrupt Module
 *
 *        File Name   		: ext_interrupt.h
 *        Version        	: 1.2
 *        Date           	: 2005.12.11
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By Yoonseok Pyo
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __EXT_INTERRUPT_H 
#define __EXT_INTERRUPT_H

#define 	INT0	0
#define 	INT1	1
#define 	INT2	2
#define 	INT3	3
#define 	INT4	4
#define 	INT5	5
#define 	INT6	6
#define 	INT7	7

//------------------------------------------------------------------------------
//                       ===== 외부인터럽트 포트 설정 =====
//------------------------------------------------------------------------------

#define   EXT0_PORT_SETUP()   cbi(DDRD, 0);  sbi(PORTD, 0);
#define   EXT1_PORT_SETUP()   cbi(DDRD, 1);  sbi(PORTD, 1);
#define   EXT2_PORT_SETUP()   cbi(DDRD, 2);  sbi(PORTD, 2);
#define   EXT3_PORT_SETUP()   cbi(DDRD, 3);  sbi(PORTD, 3);

#define   EXT4_PORT_SETUP()   cbi(DDRE, 4);  sbi(PORTE, 4);
#define   EXT5_PORT_SETUP()   cbi(DDRE, 5);  sbi(PORTE, 5);
#define   EXT6_PORT_SETUP()   cbi(DDRE, 6);  sbi(PORTE, 6);
#define   EXT7_PORT_SETUP()   cbi(DDRE, 7);  sbi(PORTE, 7);


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Ext_Interrupt(U08 INT);

#endif

