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
U08 RFIDcard_val;
U08 STBIT;

S16 TMR_10ms_CNT=0;

void Read_RFID_card(void)		//This Module position in Uart_RX_ISR 
{
	U08 Read_ID;

	if((STBIT==1)&&(data==0x46))
	{
		Read_ID = 0x01;
		STBIT = 0;
		Uart_Putch(1,Read_ID);
	}
	else if((STBIT==2)&&(data==0x33))
	{
		Read_ID = 0x02;
		STBIT = 0;
		Uart_Putch(1,Read_ID);
	}
	else if((STBIT==3)&&(data==0x34))
	{
		Read_ID = 0x03;
		STBIT = 0;
		Uart_Putch(1,Read_ID);
	}
	else if((STBIT==4)&&(data==0x32))
	{
		Read_ID = 0x04;
		STBIT = 0;
		Uart_Putch(1,Read_ID);
	}
	else
	{
		STBIT = 0;
	}

	if(data == 0x45)		STBIT = 1;
	else if(data == 0x33)	STBIT = 2;
	else if(data == 0x31)	STBIT = 3;
	else if(data == 0x44)	STBIT = 4;

}


//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)	//1//1ms
{
	TCNT1 = 65285;

	TMR_10ms_CNT++;
	if(TMR_10ms_CNT >= 10)
	{
		TMR_10ms_CNT = 0;
		//Uart_Putch(1,RFIDcard_val);
	}
}


ISR(USART0_RX_vect)
{
	Disable_ISR();

	data = UDR0;
	Read_RFID_card();
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
		
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	 
	//Init_IO();				// 초기화_입출력포트	
	//Init_Ext_Interrupt(INT0);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7
	Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(0,9600);  		// 초기화_시리얼통신0
	Init_Uart(UART1,57600);  	// 초기화_시리얼통신1
	//Init_ADC();				// 초기화_ADC
    //Init_SPI(MASTER);			// 초기화_SPI통신 
	//Init_TWI(MASTER);			// 초기화_TWI통신

	//Init_Dynamic_FND();
	//Init_DCmotor_Control();
	//Init_Encoder();

    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

