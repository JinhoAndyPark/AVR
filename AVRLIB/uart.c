/*==============================================================================
 *
 *   USART Communication Module
 *
 *        File Name   		: Uart.c
 *        Version        	: 1.3
 *        Date           	: 2005.10.10
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.07.04 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "uart.h"

#define UART0_RX_INT_ENABLE	

//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: ����ϴ� �ӵ��� �ø��� ����� �ʱ�ȭ �Ѵ�.
//------------------------------------------------------------------------------
void Init_Uart(U8 Com, U32 Uart_Baud)
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
		UCSR0C = (3<<UCSZ00);					// START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ 
		
		cbi( DDRE, 0 );                         // RXD0 �� �Է����� ����
		sbi( DDRE, 1 );                         // TXD0 �� ������� ����
		
		//#ifdef UART0_RX_INT_ENABLE				// UART0_RX_INT_ENABLE �����ø�
			sbi(UCSR0B, RXCIE0);              	// �������ͷ�Ʈ0 Ȱ��ȭ
		//#endif
	}
	
    //---------------------------- UART1 �ʱ�ȭ --------------------------------
	if( Com == UART1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 		// ����,�۽� ���º�Ʈ �ʱ�ȭ 
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// ����,�۽� ��� Ȱ��ȭ
		UCSR1C = (3<<UCSZ10);                   // START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ 
		
		cbi( DDRD, 2 );                         // RXD1 �� �Է����� ����
		sbi( DDRD, 3 );                         // TXD1 �� ������� ����
		
		//#ifdef UART1_RX_INT_ENABLE				// UART1_RX_INT_ENABLE �����ø�
			sbi(UCSR1B, RXCIE1);              	// �������ͷ�Ʈ1 Ȱ��ȭ
		//#endif
	}

}

//----------------------------------------------------------------------------
//       			===== Uart_Getch =====
//              	: �ø��� ��Ʈ�� ���� 1����Ʈ �����͸� �޴´�.
//----------------------------------------------------------------------------
U8 Uart_Getch( U8 Com )
{
	switch( Com )
	{
		case UART0:
			while(!( UCSR0A & (1<<RXC0)) );    // ���ſϷ���� ���
			return UDR0;                       // ���ŵ����� ��ȯ
		
		case UART1:
			while(!( UCSR1A & (1<<RXC1)) );    // ���ſϷ���� ���
			return UDR1;                       // ���ŵ����� ��ȯ
		
        default:
			return 0;
	}
}

//----------------------------------------------------------------------------
//   				===== Uart_Putch =====
//             		: �ø��� ��Ʈ�� 1����Ʈ ������.
//----------------------------------------------------------------------------
void Uart_Putch(U8 Com, U8 PutData)
{
	switch( Com )
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

//----------------------------------------------------------------------------
//          		===== Uart_Print =====
//             		: �ø���� ���ڿ��� ������.
//----------------------------------------------------------------------------
void Uart_Print(U8 Com, char *UartPrintData)
{
	while(*UartPrintData != '\0')				// NULL���� ������ �ݺ�
	{
		Uart_Putch( Com, *UartPrintData );		// 1����Ʈ�� ����
		
		if(*UartPrintData == 0x0A)  			// LF �� CR�� ���Ĵ�
			Uart_Putch( Com, 0x0D );
		
		UartPrintData++;
	}
}

//----------------------------------------------------------------------------
//        			===== Uart_U8Bit_PutNum =====
//             		: �ø���� unsigned char �� ���ڸ� ���
//----------------------------------------------------------------------------
void Uart_U8Bit_PutNum( U8 Com, U8 NumData )
{
	char TempData;
	
	TempData =  NumData/100;
	Uart_Putch( Com, TempData+48 );			// 100 �ڸ� ���
	
	TempData = (NumData%100)/10;
	Uart_Putch( Com, TempData+48 );      	// 10  �ڸ� ���
	
	TempData =  NumData%10;
	Uart_Putch( Com, TempData+48 );      	// 1   �ڸ� ���
}

//----------------------------------------------------------------------------
//        			===== Uart_U8Bit_PutNum =====
//              	: �ø���� unsigned char �� ���ڸ� ���
//----------------------------------------------------------------------------
void Uart_U8Bit_PutNum_Substance( U8 Com, U8 NumData )
{
	char TempData;
	
	TempData =  NumData/100;
	if(TempData > 0)						// 100 �ڸ��� 0���� ũ�� ���
		Uart_Putch( Com, TempData+48 );   	// 100 �ڸ� ���   
	
	TempData = (NumData%100)/10;
	if(TempData > 0)						// 10  �ڸ��� 0���� ũ�� ���
		Uart_Putch( Com, TempData+48 );   	// 10  �ڸ� ��� 	
	
	TempData = NumData%10;
	Uart_Putch( Com, TempData+48 );      	// 1   �ڸ��� ������ ���
}

//----------------------------------------------------------------------------
//          		===== Uart_U16Bit_PutNum =====
//          		: �ø���� unsigned char �� ���ڸ� ���
//----------------------------------------------------------------------------
void Uart_U16Bit_PutNum( U8 Com, U16 NumData )
{
	U16 TempData;
	
	TempData =  NumData/10000;
	Uart_Putch( Com, TempData+48 );      // 1000 �ڸ� ���
	
	TempData = (NumData%10000)/1000;
	Uart_Putch( Com, TempData+48 );      // 1000 �ڸ� ���
	
	TempData = (NumData%1000)/100;
	Uart_Putch( Com, TempData+48 );      // 100  �ڸ� ���
	
	TempData = (NumData%100)/10;
	Uart_Putch( Com, TempData+48 );      // 10   �ڸ� ���
	
	TempData =  NumData%10;
	Uart_Putch( Com, TempData+48 );      // 1   �ڸ��� ������ ���
}

//----------------------------------------------------------------------------
//         			===== Uart_ByteToHexPutch =====
//         			:1����Ʈ�� ���� ����Ѵ�.
//----------------------------------------------------------------------------
void Uart_ByteToHexPutch(U8 Com, U8 ByteData)
{
	U8 HexData;
	U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	HexData = Hex_Table[ByteData>>4];
	Uart_Putch(Com, HexData);            // ���� ��Ʈ�� ���
	
	HexData = Hex_Table[ByteData&0x0F];
	Uart_Putch(Com, HexData);            // ���� ��Ʈ�� ���
}


