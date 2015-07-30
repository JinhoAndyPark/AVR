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

#define MAX_LEN		0x30

typedef struct rs232_context
{
	U16 isr_cnt;		// for counting # of data
	U16 b_start;		// valid interval for receiving data
	U08 rPacketData[MAX_LEN];
}UART_CONTEXT;

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Init_Uart(U08 Com, U32 Uart_Baud);				// �ʱ�ȭ_UART���
U08  Uart_Getch(U08 Com);                               	// 1���� ���� �޴´�
void Uart_Putch(U08 Com, U08 PutData);                   	// 1���� ���� ������.
void Uart_Print(U08 Com, char *UartPrintData);          	// ���ڿ��� ������.
void Uart_U08Bit_PutNum(U08 Com, U08 NumData );           	// 8bit ���ڷ� ���
void Uart_U08Bit_PutNum_Substance(U08 Com, U08 NumData);	// 8bit ���ڷ� ���(�������� ���� ǥ��)
void Uart_U10Bit_PutNum(U08 Com, U16 NumData);
void Uart_U10Bit_PutNum3(U08 Com, U16 NumData);
void Uart_U16Bit_PutNum_Substance(U08 Com, U16 NumData);	// 16bit ���ڷ� ���(1~1000�ڸ�)
void Uart_U16Bit_PutNum(U08 Com, U16 NumData );         	// 16bit ���ڷ� ���
void Uart_ByteToHexPutch(U08 Com, U08 ByteData);         	// Byte - > Hex�� ���
void Uart_WordToHexPutch(U08 Com, U16 WordData);		// Word - > Hex�� ���

#endif
