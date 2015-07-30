/*==============================================================================
 *
 *   USART Communication Module
 *
 *   	File Name   	: uart.c
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

#include <avr/io.h>
#include "../define.h"
#include "uart.h"

#define UART0_RX_INT_ENABLE			// �������ͷ�Ʈ0 Ȱ��ȭ
//#define UART1_RX_INT_ENABLE			// �������ͷ�Ʈ1 Ȱ��ȭ

//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: ����ϴ� �ӵ��� �ø��� ����� �ʱ�ȭ �Ѵ�.
//------------------------------------------------------------------------------
void Init_Uart(U08 Com, U32 Uart_Baud)
{
	U16 Temp_UBRR;

	Temp_UBRR = AVR_CLK/(16L * Uart_Baud) - 1;   	// ��� ������Ʈ ����
													// U2X = 0 �϶� (�Ϲݸ��)
	
    //---------------------------- UART0 �ʱ�ȭ --------------------------------
	if( Com == UART0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// ����,�۽� ���º�Ʈ �ʱ�ȭ
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		// ����,�۽� ��� Ȱ��ȭ
		UCSR0C = (3<<UCSZ00);				// START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRE, 0 );                         // RXD0 �� �Է����� ����
		sbi( DDRE, 1 );                         // TXD0 �� ������� ����
		
		#ifdef UART0_RX_INT_ENABLE			// UART0_RX_INT_ENABLE �����ø�
			UCSR0B |=  (1<<RXCIE0);	             	// �������ͷ�Ʈ0 Ȱ��ȭ
		#endif
	}
	
    //---------------------------- UART1 �ʱ�ȭ --------------------------------
	if( Com == UART1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// ����,�۽� ���º�Ʈ �ʱ�ȭ
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// ����,�۽� ��� Ȱ��ȭ
		UCSR1C = (3<<UCSZ10);                   // START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRD, 2 );                         // RXD1 �� �Է����� ����
		sbi( DDRD, 3 );                         // TXD1 �� ������� ����
		
		#ifdef UART1_RX_INT_ENABLE			// UART1_RX_INT_ENABLE �����ø�
			UCSR1B |=  (1<<RXCIE1);              	// �������ͷ�Ʈ1 Ȱ��ȭ
		#endif
	}

}



//----------------------------------------------------------------------------
//   				===== Uart_Putch =====
//             		: �ø��� ��Ʈ�� 1����Ʈ ������.
//----------------------------------------------------------------------------
void Uart_Putch(U08 Com, U08 PutData)
{
	switch(Com)
	{
		case UART0:
			while(!( UCSR0A & (1<<UDRE0)) );    // �۽Ű��ɽ������� ���
			UDR0 = PutData;                     // �����͸� �����Ѵ�
			break;
		
		case UART1:
			while(!( UCSR1A & (1<<UDRE1)) );    // �۽Ű��ɽ������� ���
			UDR1 = PutData;                     // �����͸� �����Ѵ�
			break;
	}
}



