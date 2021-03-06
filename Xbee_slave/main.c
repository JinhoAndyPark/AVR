/*==============================================================================
 *
 *   Main Function
 *
 *    	File Name   	: main.c
 *    	Version        	: 1.0
 *    	Date           	: 2012.12.24
 *		Modified       	: 2012.12.24 By Kim, Hyun-Jun
 *		Author         	: Kim, Hyun-Jun  (23rd)
 *		MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: WINAVR use AVRstudio 4.18
 *		Copyright(c) ROLAB, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/

//------------------------------------------------------------------------------
//	=== Include Headerfile ===
//------------------------------------------------------------------------------
#include "main.h"		// 프로그램의 헤더파일 설정

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

U08 data;
U08 i;
//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

ISR(USART0_RX_vect)
{
	Disable_ISR();

	data = UDR0;
	//Uart_Putch(1, data);
	
	Enable_ISR();
}

//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// 초기화_MCU
	
	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
	
	//Uart_Print(0, "AT&MSG=0,");
	Uart_Putch(0,i);
	//Uart_Print(0, "\r");
	i++;
	_delay_ms(1000);
		
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	 
	//Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(0,57600);  		// 초기화_시리얼통신0
	//Init_Uart(1,57600);  	// 초기화_시리얼통신1
	    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
