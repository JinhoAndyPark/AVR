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

#define UART0_RX_INT_ENABLE			// 수신인터럽트0 활성화
//#define UART1_RX_INT_ENABLE			// 수신인터럽트1 활성화

//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: 희망하는 속도로 시리얼 통신을 초기화 한다.
//------------------------------------------------------------------------------
void Init_Uart(U08 Com, U32 Uart_Baud)
{
	U16 Temp_UBRR;

	Temp_UBRR = AVR_CLK/(16L * Uart_Baud) - 1;   	// 통신 보레이트 계산식
													// U2X = 0 일때 (일반모드)
	
    //---------------------------- UART0 초기화 --------------------------------
	if( Com == UART0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		// 수신,송신 기능 활성화
		UCSR0C = (3<<UCSZ00);				// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
		sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
		
		#ifdef UART0_RX_INT_ENABLE			// UART0_RX_INT_ENABLE 설정시만
			UCSR0B |=  (1<<RXCIE0);	             	// 수신인터럽트0 활성화
		#endif
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	if( Com == UART1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// 수신,송신 상태비트 초기화
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// 수신,송신 기능 활성화
		UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 2 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 3 );                         // TXD1 핀 출력으로 설정
		
		#ifdef UART1_RX_INT_ENABLE			// UART1_RX_INT_ENABLE 설정시만
			UCSR1B |=  (1<<RXCIE1);              	// 수신인터럽트1 활성화
		#endif
	}

}



//----------------------------------------------------------------------------
//   				===== Uart_Putch =====
//             		: 시리얼 포트로 1바이트 보낸다.
//----------------------------------------------------------------------------
void Uart_Putch(U08 Com, U08 PutData)
{
	switch(Com)
	{
		case UART0:
			while(!( UCSR0A & (1<<UDRE0)) );    // 송신가능시점까지 대기
			UDR0 = PutData;                     // 데이터를 전송한다
			break;
		
		case UART1:
			while(!( UCSR1A & (1<<UDRE1)) );    // 송신가능시점까지 대기
			UDR1 = PutData;                     // 데이터를 전송한다
			break;
	}
}



