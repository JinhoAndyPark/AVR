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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

#define UART_SLAVE	0
#define UART_SERVER	1

#define MY_ID		3


#define	NOT_YET		0
#define	DONE		1


#define	PACKET_START			0xFF
#define	PACKET_END				0xEE

#define PACKET_LENGTH			2

#define PACKET_NO_ERR			0
#define PACKET_LENGTH_ERR		1
#define PACKET_INDEX_ERR		2
#define PACKET_DATA_ERR			3
#define PACKET_CHKSUM_ERR		4
#define PACKET_END_ERR			5



// DATA
#define DATA_RX_				0x01


U16 TMR_100ms_CNT=0, TMR_INTERVAL_CNT=0;
U08 ID_cnt = 1;


typedef enum packet_state
{
	PK_ST_INIT=0,
	PK_ST_LENGTH,
	PK_ST_ID,
	PK_ST_DATA,
	PK_ST_rDATA,
	PK_ST_END,
	PK_ST_UNKNOWN
}PACKET_STATE;

typedef struct packet_decode
{
	U08 id;	
	U08 value;
	U08 rev_value;
	U08 end;

	unsigned int data_len;
	unsigned char data[MAX_LEN];
	
	unsigned char error_code;

	unsigned int timeout_cnt;
	
}GUI_PACKET;



volatile UART_CONTEXT pContext;
volatile GUI_PACKET pPacket;

void proc_packet_read_status(GUI_PACKET *packet);
void proc_packet_command(GUI_PACKET *packet);
void proc_packet_error(U08 code);

void Packet_TxD( U08 Length, U08 ID, U08 Data );

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

ISR(USART0_RX_vect)
{
	U08 data;
	Disable_ISR();

	data = UDR0;

	if(( data == PACKET_START) && ( pContext.b_start == NOT_YET))
	{
		pContext.rPacketData[pContext.isr_cnt++] = data;
		pContext.b_start = DONE;
	}
	else if((pContext.isr_cnt >= 1) && (pContext.b_start == DONE))
	{
		pContext.rPacketData[pContext.isr_cnt++] = data;
	}
	Enable_ISR();
}

void Init_packet( GUI_PACKET *packet, UART_CONTEXT *context )
{
	memset(packet, 0, sizeof(GUI_PACKET));
	memset(context, 0, sizeof(UART_CONTEXT));
}

void PacketManager( GUI_PACKET *packet, UART_CONTEXT *context )
{
	static PACKET_STATE current_pk_state = PK_ST_INIT;
	static PACKET_STATE next_pk_state = PK_ST_INIT;

	current_pk_state = next_pk_state;

	switch( current_pk_state )
	{
		case PK_ST_INIT:
			if( context->b_start )
			{
				packet->timeout_cnt = 0;

				next_pk_state = PK_ST_LENGTH;
			}
			break;

		case PK_ST_LENGTH:
			packet->data_len = context->rPacketData[1];

			if( packet->data_len == PACKET_LENGTH )		
			{
				next_pk_state = PK_ST_ID;
			}
			else
			{
				packet->error_code = PACKET_LENGTH_ERR;
				proc_packet_error( packet->error_code);

				next_pk_state = PK_ST_INIT;
				Init_packet(packet, context);
			}
			break;

		case PK_ST_ID:
			packet->id = context->rPacketData[2];

			switch( packet->id )
			{
				case MY_ID:
					next_pk_state = PK_ST_DATA;
					break;
				
				default:
					packet->error_code = PACKET_INDEX_ERR;
					proc_packet_error( packet->error_code );	// length error

					next_pk_state = PK_ST_INIT;
					Init_packet(packet, context);
					
					break;
			}
			break;

		case PK_ST_DATA:
			packet->value = context->rPacketData[3] ;

			next_pk_state =  PK_ST_rDATA;
			break;
			
		case PK_ST_rDATA:
			packet->rev_value = ~(context->rPacketData[4]);

			next_pk_state = PK_ST_END;
				
			break;

		case PK_ST_END:
			packet->end = context->rPacketData[5];
			
			if( packet->end == PACKET_END )		
			{
				packet->error_code = PACKET_NO_ERR;
				
				proc_packet_error( packet->error_code );		// packet end error
				proc_packet_command(packet);
			}
			else 
			{			
				packet->error_code = PACKET_END_ERR;
				proc_packet_error( packet->error_code );		// packet end error
			}
			
			next_pk_state = PK_ST_INIT;
			Init_packet(packet, context);
			
			break;

		default:
			break;
	}
}

void proc_packet_command( GUI_PACKET *packet )
{

	switch( packet->id )
	{
		case MY_ID:	// Command
			Packet_TxD( 2, MY_ID, 0xF0 );
			switch( packet->value )
			{
				case DATA_RX_:	
					break;
					
				default:
					break;
			}
			break;
			
		default :
			break;
	}

	
}


void proc_packet_error(U08 code)
{
	switch(code)
	{
		case PACKET_NO_ERR:			// No Error
			break;
		case PACKET_LENGTH_ERR:		// Length Error
			break;	
		case PACKET_INDEX_ERR:		// Index Error
			break;	
		case PACKET_DATA_ERR:		// Data Error
			break;	
		case PACKET_CHKSUM_ERR:		// Check Sum Error
			break;	
		case PACKET_END_ERR:	
			break;			
		default:
			break;
	}
}


void HostUartTxD(unsigned char* packet, int len)
{
	int cnt;

	for(cnt = 0; cnt < len ; cnt++)
	{
		while(!(UCSR0A & (1 <<UDRE0)));
		UDR0 = packet[cnt];
	}
}

void Packet_TxD( U08 Length, U08 ID, U08 Data )			// Laser -> GUI �� Packet ���۽� ���
{
	U08 PacketBuffer[6];
	
	PacketBuffer[0] = PACKET_START;		// Start Code
	PacketBuffer[1] = Length;			// Length
	PacketBuffer[2] = ID;				//My ID
	PacketBuffer[3] = Data;				//Data
	PacketBuffer[4] = ~Data;			//reverse Data
	PacketBuffer[5] = PACKET_END;		// End Code

	HostUartTxD( PacketBuffer, Length + 4 );
}


//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
int main(void)
{ 
	Init_Main();		// �ʱ�ȭ_MCU
	
	Init_packet((GUI_PACKET*)&pPacket, (UART_CONTEXT*)&pContext);
	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
		
		PacketManager( (GUI_PACKET*)&pPacket, (UART_CONTEXT *)&pContext );

		_delay_ms(2);
		
		
	//--------------------------------------------------------------------------    
	}
	return 0;
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������
	 
	//Init_IO();				// �ʱ�ȭ_�������Ʈ	
	//Init_Ext_Interrupt(INT0);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	//Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(0,57600);  		// �ʱ�ȭ_�ø������0
	//Init_Uart(1,57600);  	// �ʱ�ȭ_�ø������1
	//Init_ADC();				// �ʱ�ȭ_ADC
    //Init_SPI(MASTER);			// �ʱ�ȭ_SPI��� 
	//Init_TWI(MASTER);			// �ʱ�ȭ_TWI���

    
	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
