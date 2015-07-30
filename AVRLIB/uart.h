/*==============================================================================
 *
 *   USART Communication Module
 *
 *        File Name   		: Uart.c
 *        Version        	: 1.2
 *        Date           	: 2005.10.10
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
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

void Init_Uart(U8 Com, U32 Uart_Baud);					// 초기화_UART통신
U8   Uart_Getch(U8 Com);                               	// 1개의 문자 받는다
void Uart_Putch(U8 Com, U8 PutData);                   	// 1개의 문자 보낸다.
void Uart_Print(U8 Com, char *UartPrintData);          	// 문자열을 보낸다.
void Uart_U16Bit_PutNum(U8 Com, U16 NumData );         	// 16bit 숫자로 출력
void Uart_U8Bit_PutNum(U8 Com, U8 NumData );           	// 8bit 숫자로 출력
void Uart_U8Bit_PutNum_Substance( U8 Com, U8 NumData );	// 8bit 숫자로 출력(실질적인 수만 표시)
void Uart_ByteToHexPutch(U8 Com, U8 ByteData);         	// Byte - > Hex로 출력

#endif
