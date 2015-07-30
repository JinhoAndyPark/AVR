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

#define START_BIT	0xFF
#define END_BIT		0xEE

#define PACKET_LEN	5
#define UART_SLAVE	0
#define UART_SERVER	1

U16 TMR_100ms_CNT=0, TMR_INTERVAL_CNT=0;
U08 data;
U08 ID_cnt = 1;

//packet : start_bit | ID | data | ~data | end_bit
U08 packet[PACKET_LEN];
U08 receive_packet[PACKET_LEN];
U08 receive_buffer[PACKET_LEN];
U08 SVpacket[PACKET_LEN];

U08 check_RxD = 0;

struct SLAVE
{
	U08 LIVE;
	U08 DATA;
};

struct SLAVE slave_1st;
struct SLAVE slave_2nd;
struct SLAVE slave_3th;

void Master2Server(U08 Data1, U08 Data2, U08 Data3);
void Master2Slave(U08 last_ID, U08 sData);

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)	//1//1ms
{
	TCNT1 = 65285;

	TMR_100ms_CNT++;
	if(TMR_100ms_CNT >= 100)
	{
		
		TMR_100ms_CNT = 0;
		
		TMR_INTERVAL_CNT++;
		if(TMR_INTERVAL_CNT >= 10)
		{
			Master2Server(slave_1st.LIVE, slave_2nd.LIVE, slave_3th.LIVE);
			Master2Slave(3, 0xFD);			//아마 여기도 카운트해서 사라질 경우 체크
			TMR_INTERVAL_CNT = 0;
		}
	}
}

ISR(USART0_RX_vect)
{
	Disable_ISR();
	
	data = UDR0;
	check_RxD++;
	
	Enable_ISR();
}

void Send_Packet(U08 Com, U08 len)
{
	U08 cnt;

	for(cnt=0; cnt<len; cnt++)
	{
		Uart_Putch(Com, packet[cnt]);
		//_delay_ms(5);
	}
}

void Send_Sever(U08 Com, U08 len)
{
	U08 cnt;

	for(cnt=0; cnt<len; cnt++)
	{
		Uart_Putch(Com, SVpacket[cnt]);
		//_delay_ms(5);
	}
}


void Master2Server(U08 Data1, U08 Data2, U08 Data3)
{
	SVpacket[0] = START_BIT;
	SVpacket[1] = Data1;
	SVpacket[2] = Data2;
	SVpacket[3] = Data3;
	SVpacket[4] = END_BIT;

	Send_Sever(UART_SERVER, PACKET_LEN);
}

void Master2Slave(U08 last_ID, U08 sData)
{
	if(ID_cnt>last_ID)		ID_cnt = 1;
	
	packet[0] = START_BIT;
	packet[1] = ID_cnt;
	packet[2] = sData;
	packet[3] = ~sData;
	packet[4] = END_BIT;

	Send_Packet(UART_SLAVE, PACKET_LEN);
	ID_cnt++;
	
}

void Clear_buffer(void)
{
	U08 cnt;
	
	for(cnt=0; cnt<PACKET_LEN; cnt++)
	{
		receive_buffer[cnt] = 0;
	}
}

U08 Check_Packet(void)
{
	U08 rev_data = 0;
	
	if(receive_buffer[0] == START_BIT)
	{
		rev_data = ~receive_buffer[2];
		if(receive_buffer[3] == rev_data)
		{
			if(receive_buffer[4] == END_BIT)	return 1;
			else								return 0;
		}
		else	return 0;
	}
	else	return 0;
		
}

void Receive_Packet(void)
{
	if(check_RxD == 1)				receive_buffer[0] = data;
	else if(check_RxD == 2)		receive_buffer[1] = data;
	else if(check_RxD == 3)		receive_buffer[2] = data;
	else if(check_RxD == 4)		receive_buffer[3] = data;	
	else if(check_RxD == 5)
	{
		receive_buffer[4] = data;
		
		if(Check_Packet())
		{
			receive_packet[0] = receive_buffer[0];
			receive_packet[1] = receive_buffer[1];
			receive_packet[2] = receive_buffer[2];
			receive_packet[3] = receive_buffer[3];
			receive_packet[4] = receive_buffer[4];

			Clear_buffer();
		}
		else 	Clear_buffer();
		check_RxD = 0;
	}
	
}

//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// 초기화_MCU

	slave_1st.LIVE = 0;
	slave_2nd.LIVE = 0;
	slave_3th.LIVE = 0;
	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
		//Uart_Print(0, "\r\n");
		//Master2Slave(3, 300, 0xFD);
		//if(data=='a')	Master2Slave(3, 1000, 0x55);
		//else	Master2Slave(3, 300, 0xFD);

		//struct SLAVE slave_1st;
		//struct SLAVE slave_2nd;
		//struct SLAVE slave_3th;
		
		Receive_Packet();

		if(receive_packet[1] == 0x01)
		{
			//Uart_Putch(0, '1');
			slave_1st.LIVE = 1;
			slave_1st.DATA = receive_packet[2];
		}
		else if(receive_packet[1] == 0x02)
		{
			//Uart_Putch(0, '2');
			slave_2nd.LIVE = 1;
			slave_2nd.DATA = receive_packet[2];
		}
		else if(receive_packet[1] == 0x03)
		{
			//Uart_Putch(0, '3');
			slave_3th.LIVE = 1;
			slave_3th.DATA = receive_packet[2];
		}
		
		_delay_ms(50);
		
		
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
    Init_Uart(0,57600);  		// 초기화_시리얼통신0
	Init_Uart(1,57600);  	// 초기화_시리얼통신1
	//Init_ADC();				// 초기화_ADC
    //Init_SPI(MASTER);			// 초기화_SPI통신 
	//Init_TWI(MASTER);			// 초기화_TWI통신

    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
