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
#include "main.h"		// ���α׷��� ������� ����

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
	Init_Main();		// �ʱ�ȭ_MCU
	
	
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
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������
	 
	//Init_IO();				// �ʱ�ȭ_�������Ʈ	
	//Init_Ext_Interrupt(INT0);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(0,9600);  		// �ʱ�ȭ_�ø������0
	Init_Uart(UART1,57600);  	// �ʱ�ȭ_�ø������1
	//Init_ADC();				// �ʱ�ȭ_ADC
    //Init_SPI(MASTER);			// �ʱ�ȭ_SPI��� 
	//Init_TWI(MASTER);			// �ʱ�ȭ_TWI���

	//Init_Dynamic_FND();
	//Init_DCmotor_Control();
	//Init_Encoder();

    
	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

