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
//             		: 희망하는 속도로 시리얼 통신을 초기화 한다.
//------------------------------------------------------------------------------
void Init_Uart(U8 Com, U32 Uart_Baud)
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
		UCSR0C = (3<<UCSZ00);					// START 1비트/DATA 8비트/STOP 1비트 
		
		cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
		sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
		
		//#ifdef UART0_RX_INT_ENABLE				// UART0_RX_INT_ENABLE 설정시만
			sbi(UCSR0B, RXCIE0);              	// 수신인터럽트0 활성화
		//#endif
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	if( Com == UART1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 		// 수신,송신 상태비트 초기화 
		UCSR1B = (1<<RXEN1) | (1<<TXEN1);    	// 수신,송신 기능 활성화
		UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트 
		
		cbi( DDRD, 2 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 3 );                         // TXD1 핀 출력으로 설정
		
		//#ifdef UART1_RX_INT_ENABLE				// UART1_RX_INT_ENABLE 설정시만
			sbi(UCSR1B, RXCIE1);              	// 수신인터럽트1 활성화
		//#endif
	}

}

//----------------------------------------------------------------------------
//       			===== Uart_Getch =====
//              	: 시리얼 포트로 부터 1바이트 데이터를 받는다.
//----------------------------------------------------------------------------
U8 Uart_Getch( U8 Com )
{
	switch( Com )
	{
		case UART0:
			while(!( UCSR0A & (1<<RXC0)) );    // 수신완료까지 대기
			return UDR0;                       // 수신데이터 반환
		
		case UART1:
			while(!( UCSR1A & (1<<RXC1)) );    // 수신완료까지 대기
			return UDR1;                       // 순신데이터 반환
		
        default:
			return 0;
	}
}

//----------------------------------------------------------------------------
//   				===== Uart_Putch =====
//             		: 시리얼 포트로 1바이트 보낸다.
//----------------------------------------------------------------------------
void Uart_Putch(U8 Com, U8 PutData)
{
	switch( Com )
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

//----------------------------------------------------------------------------
//          		===== Uart_Print =====
//             		: 시리얼로 문자열을 보낸다.
//----------------------------------------------------------------------------
void Uart_Print(U8 Com, char *UartPrintData)
{
	while(*UartPrintData != '\0')				// NULL문자 전까지 반복
	{
		Uart_Putch( Com, *UartPrintData );		// 1바이트씩 전송
		
		if(*UartPrintData == 0x0A)  			// LF 에 CR을 보탠다
			Uart_Putch( Com, 0x0D );
		
		UartPrintData++;
	}
}

//----------------------------------------------------------------------------
//        			===== Uart_U8Bit_PutNum =====
//             		: 시리얼로 unsigned char 형 숫자를 출력
//----------------------------------------------------------------------------
void Uart_U8Bit_PutNum( U8 Com, U8 NumData )
{
	char TempData;
	
	TempData =  NumData/100;
	Uart_Putch( Com, TempData+48 );			// 100 자리 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch( Com, TempData+48 );      	// 10  자리 출력
	
	TempData =  NumData%10;
	Uart_Putch( Com, TempData+48 );      	// 1   자리 출력
}

//----------------------------------------------------------------------------
//        			===== Uart_U8Bit_PutNum =====
//              	: 시리얼로 unsigned char 형 숫자를 출력
//----------------------------------------------------------------------------
void Uart_U8Bit_PutNum_Substance( U8 Com, U8 NumData )
{
	char TempData;
	
	TempData =  NumData/100;
	if(TempData > 0)						// 100 자리가 0보다 크면 출력
		Uart_Putch( Com, TempData+48 );   	// 100 자리 출력   
	
	TempData = (NumData%100)/10;
	if(TempData > 0)						// 10  자리가 0보다 크면 출력
		Uart_Putch( Com, TempData+48 );   	// 10  자리 출력 	
	
	TempData = NumData%10;
	Uart_Putch( Com, TempData+48 );      	// 1   자리는 무조건 출력
}

//----------------------------------------------------------------------------
//          		===== Uart_U16Bit_PutNum =====
//          		: 시리얼로 unsigned char 형 숫자를 출력
//----------------------------------------------------------------------------
void Uart_U16Bit_PutNum( U8 Com, U16 NumData )
{
	U16 TempData;
	
	TempData =  NumData/10000;
	Uart_Putch( Com, TempData+48 );      // 1000 자리 출력
	
	TempData = (NumData%10000)/1000;
	Uart_Putch( Com, TempData+48 );      // 1000 자리 출력
	
	TempData = (NumData%1000)/100;
	Uart_Putch( Com, TempData+48 );      // 100  자리 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch( Com, TempData+48 );      // 10   자리 출력
	
	TempData =  NumData%10;
	Uart_Putch( Com, TempData+48 );      // 1   자리는 무조건 출력
}

//----------------------------------------------------------------------------
//         			===== Uart_ByteToHexPutch =====
//         			:1바이트를 헥사로 출력한다.
//----------------------------------------------------------------------------
void Uart_ByteToHexPutch(U8 Com, U8 ByteData)
{
	U8 HexData;
	U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	
	HexData = Hex_Table[ByteData>>4];
	Uart_Putch(Com, HexData);            // 상위 비트를 출력
	
	HexData = Hex_Table[ByteData&0x0F];
	Uart_Putch(Com, HexData);            // 하위 비트를 출력
}


