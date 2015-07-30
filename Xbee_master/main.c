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

#define SLAVE1stON		1
#define SLAVE1stOFF		0
#define SLAVE2ndON		1
#define SLAVE2ndOFF		0
#define	SLAVE3thON		1
#define	SLAVE3thOFF		0

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

U08 IDflag = 0;
U08 nID = 0;
U08 i;

volatile U08 state1st, state2nd, state3th;
U08 CNT1st, CNT2nd, CNT3th;

U16 tic_1sec = 0;

void ServerTxD(unsigned char* packet, int len);
void Master2Server( U08 ID_1, U08 ID_2, U08 ID_3 );

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)	//1//2ms
{
	TCNT0 = 131;
	tic_1sec++;
	if(tic_1sec >= 500)
	{
		tic_1sec = 0;

		Master2Server( state1st, state2nd, state3th );

		if(state1st == SLAVE1stON)
		{
			CNT1st++;
			if(CNT1st > 1)	state1st = SLAVE1stOFF;
		}
		if(state2nd == SLAVE2ndON)
		{
			CNT2nd++;
			if(CNT2nd > 1)	state2nd = SLAVE2ndOFF;
		}
		if(state3th == SLAVE3thON)
		{
			CNT3th++;
			if(CNT3th > 1) state3th = SLAVE3thOFF;
		}
	}
	
}

ISR(USART0_RX_vect)
{
	U08 data;
	
	Disable_ISR();

	data = UDR0;

	if(IDflag == 1)
	{
		IDflag = 0;
		nID = data;

		if(nID == '1')
		{
			sbi(PORTC,3);
			state1st = SLAVE1stON;
			CNT1st = 0;
		}
		else if(nID == '2')
		{
			sbi(PORTC,4);
			state2nd = SLAVE2ndON;
			CNT2nd = 0; 
		}
		else if(nID == '3')
		{
			sbi(PORTC,5);
			state3th = SLAVE3thON;
			CNT3th = 0;
		}
	}

	if((data=='@') && (IDflag==0))	IDflag = 1;
	
	Enable_ISR();
}


void ServerTxD(unsigned char* packet, int len)
{
	int cnt;

	for(cnt = 0; cnt < len ; cnt++)
	{
		while(!( UCSR1A & (1<<UDRE1)));
		UDR1 = packet[cnt];
	}
}

void Master2Server( U08 ID_1, U08 ID_2, U08 ID_3 )
{
	U08 PacketBuffer[5];
	
	PacketBuffer[0] = 0xFF;				// Start Code 0xff ID1 ID2 ID3 0xEE
	PacketBuffer[1] = ID_1;		
	PacketBuffer[2] = ID_2;				//My ID
	PacketBuffer[3] = ID_3;				//Data
	PacketBuffer[4] = 0xEE;				// End Code

	ServerTxD( PacketBuffer, 5 );
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
	

	if(state1st == SLAVE1stON)			sbi(PORTC,0);
	else if(state1st == SLAVE1stOFF)	cbi(PORTC,0);
	
	if(state2nd == SLAVE2ndON)			sbi(PORTC,1);
	else if(state1st == SLAVE1stOFF)	cbi(PORTC,1);
	
	if(state3th == SLAVE3thON)			sbi(PORTC,2);
	else if(state3th == SLAVE3thOFF) 	cbi(PORTC,2);
			
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
    Init_Uart(0,57600);  		// 초기화_시리얼통신0
	Init_Uart(1,57600);  	// 초기화_시리얼통신1

	DDRC = 0xFF;
	DDRD = 0xFF;
    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
