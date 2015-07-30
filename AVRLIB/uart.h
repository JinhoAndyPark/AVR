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

void Init_Uart(U8 Com, U32 Uart_Baud);					// �ʱ�ȭ_UART���
U8   Uart_Getch(U8 Com);                               	// 1���� ���� �޴´�
void Uart_Putch(U8 Com, U8 PutData);                   	// 1���� ���� ������.
void Uart_Print(U8 Com, char *UartPrintData);          	// ���ڿ��� ������.
void Uart_U16Bit_PutNum(U8 Com, U16 NumData );         	// 16bit ���ڷ� ���
void Uart_U8Bit_PutNum(U8 Com, U8 NumData );           	// 8bit ���ڷ� ���
void Uart_U8Bit_PutNum_Substance( U8 Com, U8 NumData );	// 8bit ���ڷ� ���(�������� ���� ǥ��)
void Uart_ByteToHexPutch(U8 Com, U8 ByteData);         	// Byte - > Hex�� ���

#endif
