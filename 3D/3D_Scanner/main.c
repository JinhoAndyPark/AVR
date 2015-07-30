
//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------



/*==============================================================================
 *
 *   Main Function
 *
 *    	File Name   	: main.c
 *    	Version        	: 1.0
 *    	Date           	: 2013.10.30
 *		Modified       	: 2013.10.30 By Park, Jin-Ho
 *		Author         	: Park, Jin-Ho  (27th)
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




void Uart_U16Bit_PutNum(U16 NumData);
//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------
U08 BREAK_NUM0 = 0;		//extern
U08 BREAK_NUM1 = 0;
U08 Getch_USART1 = 0;





ISR(USART1_RX_vect)
{	
		U08 Getch_USART1=UDR1;
		
		switch(Getch_USART1)
		{
		
			case 'A':
			
			X_Move_Startpoint();
			_delay_ms(100);
			Y_Move_Startpoint();

			break;
			
		
			case 'B' :
			
			_delay_ms(100);
			X_Move_deg();	
			_delay_ms(100);
			X_Move_Startpoint();

			break;

			case 'U' :

			Y_Move_Up();

			break;
			
	}

}
int main(void)
{	
	U16 Dis = 0;
	
	//U16 cnt;
	
	Main_Init();
	
	/*
	X_Move_Startpoint();
	_delay_ms(100);

	//Y_Move_Startpoint();
	
	
	for(cnt=0; cnt<200; cnt++)
	{
		X_Move_deg();
		//if( BREAK_NUM0 = 1 )
		//break;
	}
	_delay_ms(500);
	
	if( BREAK_NUM0 = 0)
	{
		for(cnt=0; cnt<2; cnt++)
		{
			X_Move_deg();
			if( BREAK_NUM0 = 1 )
			break;
		}
	}
	*/
	while(1)
	{	/*
		for(cnt=0; cnt<200; cnt++)
		{
			X_Move_deg();
		}
		*/
		
		Read_ADC(0);
		_delay_ms(500);
		Dis = (( (11.65/((ADC/204.8) - 0.147) ) - 0.42 ) * 10)-4;
		Uart_U16Bit_PutNum(Dis);
	}
	
	return 0;
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------

void Main_Init(void)
{
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������
	
	//Init_IO();				// �ʱ�ȭ_�������Ʈ	
	Init_Ext_Interrupt(INT0);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	Init_Ext_Interrupt(INT1);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	//Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(UART0,9600);  		// �ʱ�ȭ_�ø������0
	Init_Uart(UART1,9600);  	// �ʱ�ȭ_�ø������1
	Init_ADC();					// �ʱ�ȭ_ADC
    //Init_SPI(MASTER);			// �ʱ�ȭ_SPI��� 
	//Init_TWI(MASTER);			// �ʱ�ȭ_TWI���

	//Uart_Getch(1);					
						
	Motor_Init();

	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

void Uart_U16Bit_PutNum(U16 NumData)
{
	U16 TempData;

	TempData = NumData/10000;
	Uart_Putch(0,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(0,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1's place print 
						
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1's place print 
}

