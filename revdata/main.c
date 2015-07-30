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
extern volatile U08 CoordinateX[256];
extern volatile U08 CoordinateY[256];
extern volatile U08 CoordinateZ[256];

volatile U08 moveflag;
extern volatile U08 RXstate, RXcnt;
extern volatile U08 RXLENGTH;

volatile UART_CONTEXT pContext;
volatile PARTNER_PACKET pPacket;

MODE_STATE Mode = MODE_READY;


//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)	//1//1ms
{
	TCNT1 = 65285;
}

ISR(USART0_RX_vect)
{
	U08 data;
	Disable_ISR();

	data = UDR0;
	//Uart_Putch(1, data);
	if(( data == PACKET_START) && ( pContext.b_start == NOT_YET))
	{
		pContext.rPacketData[pContext.isr_cnt++] = data;
		pContext.b_start = DONE;
	}
	else if((pContext.isr_cnt >= 1) && (pContext.b_start == DONE))
	{
		pContext.rPacketData[pContext.isr_cnt++] = data;
	}
	PacketManager((PARTNER_PACKET*)&pPacket, (UART_CONTEXT*)&pContext );
	Enable_ISR();
}
/*
ISR(USART1_RX_vect)
{
	U08 data;
	Disable_ISR();

	Disable_ISR();

	data = UDR1;

	if(data == 'a')
	{
		SendRequestPacket(0x01, 0x02);
		data = 0;
	}

	if(data == 'b')
	{
		SendRequestPacket(0x03, 0x04);
		data = 0;
	}

	Enable_ISR();
}
*/
//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// 초기화_MCU

	Position_Homing();

	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------

	//PacketManager((PARTNER_PACKET*)&pPacket, (UART_CONTEXT*)&pContext );
	//_delay_ms(5);		// delay. NECESSARY!!!
	
	if(RXstate == RXEND)
	{
		Mode = MODE_RUN;
		for(U08 cnt=0; cnt<RXLENGTH; cnt++)
		{
			Uart_Print(1,"\n\r Xcod : ");
			Uart_U08Bit_PutNum(1, CoordinateX[cnt]);
			Uart_Print(1," Ycod : ");
			Uart_U08Bit_PutNum(1, CoordinateY[cnt]);
			Uart_Print(1," Zcod : ");
			Uart_U08Bit_PutNum(1, CoordinateZ[cnt]);

			Moving_XYCoordinate(CoordinateX[cnt],CoordinateY[cnt]);
			//Change ServoPWM
		}
		RXstate = RXREADY;
		SendRequestPacket(IND_TX_NEXTPAGE, 0x00);
	}
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	 
	Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(0,9600);  		// 초기화_시리얼통신0
	Init_Uart(1,9600);  	// 초기화_시리얼통신1

	sbi(DDRG,0);	// 1st_step
	sbi(DDRG,1);	// 1st_dir
	sbi(DDRG,3);	// 2nd_step
	sbi(DDRG,4);	// 2nd_dir

	cbi(DDRC,0);	// 1st_hall sensor
	cbi(DDRC,1);	// 2nd_hall sensor

	Init_packet((PARTNER_PACKET*)&pPacket, (UART_CONTEXT*)&pContext );

	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
