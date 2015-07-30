/*==============================================================================
 *
 *   USART Communication Module
 *
 *   	File Name   	: uart.h
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

#ifndef __UART_H
#define __UART_H

#define	UART0	0
#define	UART1	1

#define	AVR_CLK	16000000L		// 16Mhz

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Uart(U08 Com, U32 Uart_Baud);				// 초기화_UART통신
U08  Uart_Getch(U08 Com);                           // 1개의 문자 받는다
void Uart_Putch(U08 Com, U08 PutData);              // 1개의 문자 보낸다.

#endif
