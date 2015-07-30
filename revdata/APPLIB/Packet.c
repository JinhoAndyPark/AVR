/*==============================================================================
 *
 *   Packet Making Module
 *
 *   File Name   	: Packet.c
 *   Version        	: 1.0
 *   Date           	: 2013.04.15
 *	 Modified       	: 2013.04.15 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/
#include "Packet.h"
#include "../Main.h"
#include "stepmotor.h"

volatile U08 CoordinateX[256];
volatile U08 CoordinateY[256];
volatile U08 CoordinateZ[256];

extern volatile U08 moveflag;
volatile U08 TXflag=0;

volatile U08 RXLENGTH = 0;
volatile U08 RXstate = 0, RXcnt=0;
volatile U08 nPAGE = 0, PAGEcnt;

extern MODE_STATE Mode;


void Init_packet( PARTNER_PACKET *packet, UART_CONTEXT *context )
{
	memset(packet, 0, sizeof(PARTNER_PACKET));
	memset(context, 0, sizeof(UART_CONTEXT));
}


void PacketManager( PARTNER_PACKET *packet, UART_CONTEXT *context )
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
				next_pk_state = PK_ST_INDEX;
			}
			else
			{
				packet->error_code = PACKET_LENGTH_ERR;
				proc_packet_error( packet->error_code);

				next_pk_state = PK_ST_INIT;
				Init_packet(packet, context);
			}
			break;
			
		case PK_ST_INDEX:
			packet->index = context->rPacketData[2];

			next_pk_state =  PK_ST_XCOD;
			break;

		case PK_ST_XCOD:
			packet->xcod = context->rPacketData[3];

			next_pk_state =  PK_ST_YCOD;
			break;
			
		case PK_ST_YCOD:
			packet->ycod = context->rPacketData[4];

			next_pk_state = PK_ST_CHKSUM;
				
			break;

		case PK_ST_CHKSUM:
			if(1)//( Checksum( packet, context ))
			{
				next_pk_state = PK_ST_END;
			}
			else
			{
				packet->error_code = PACKET_CHKSUM_ERR;
				proc_packet_error( packet->error_code );	// check sum error
				
				next_pk_state = PK_ST_INIT;
				Init_packet(packet, context);
			}
			break;

		case PK_ST_END:
			packet->end = context->rPacketData[6];
			
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


void proc_packet_command( PARTNER_PACKET *packet )
{

	switch( packet->index )
	{
		case IND_RX_TXSTART:
			//Moving_StartPoint();
			SendRequestPacket(IND_TX_STATE, DATA_TX_STANDBY);
			Mode = MODE_STANDBY;
			TXflag = 1;
			nPAGE = 0;
			break;
			
		case IND_RX_PAGESTART:
			if(TXflag == 1)
			{
				PAGEcnt = packet->ycod;
				
				if(PAGEcnt == nPAGE)
				{
					RXLENGTH = packet->xcod;
					RXstate = RXBUFFERING;
					RXcnt = 0;
				}
				else	SendRequestPacket(IND_TX_PAGEERR, nPAGE);
			}
			
			break;

		case IND_RX_ZSTART:
			if((TXflag==1) && (RXstate==RXBUFFERING))
			{
				CoordinateX[RXcnt] = packet->xcod;
				CoordinateY[RXcnt] = packet->ycod;
				CoordinateZ[RXcnt] = 2;
				RXcnt++;
			}
			break;
			
		case IND_RX_ZING:
			if((TXflag==1) && (RXstate==RXBUFFERING))
			{
				CoordinateX[RXcnt] = packet->xcod;
				CoordinateY[RXcnt] = packet->ycod;
				CoordinateZ[RXcnt] = 1;
				RXcnt++;
			}
			break;

		case IND_RX_ZEND:
			if((TXflag==1) && (RXstate==RXBUFFERING))
			{
				CoordinateX[RXcnt] = packet->xcod;
				CoordinateY[RXcnt] = packet->ycod;
				CoordinateZ[RXcnt] = 0;
				RXcnt++;
			}
			break;

		case IND_RX_PAGEEND:
			if((TXflag==1) && (RXstate==RXBUFFERING))
			{
				if(RXcnt == RXLENGTH)
				{
					nPAGE++;
					Mode = MODE_RUN;
					RXstate = RXEND;
				}
				else	
				{
					Mode = MODE_STANDBY;
					RXstate = RXREADY;
					SendRequestPacket(IND_TX_PAGEERR, nPAGE);
				}
			}
			break;

		case IND_RX_TXEND:
			TXflag = 0;
			Position_Homing();
			
			Mode = MODE_READY;
			//SendRequestPacket(IND_TX_STATE, DATA_TX_READY);
			break;

		case IND_RX_ASKREADY:
			if(Mode == MODE_READY)			SendRequestPacket(IND_TX_STATE, DATA_TX_READY);
			else if(Mode == MODE_STANDBY) 	SendRequestPacket(IND_TX_STATE, DATA_TX_STANDBY);
			else							SendRequestPacket(IND_TX_STATE, DATA_TX_RUN);
			break;

		default :
			break;
	}
}

U16 Checksum(PARTNER_PACKET *packet, UART_CONTEXT *context)
{
	U16 i;

	for(i=0 ; i < 3 ; i++)
	{
		packet->checksum ^= context->rPacketData[i+2];
	}

	_delay_ms(5);	// delay. NECESSARY!!!

	if(packet->checksum ==  context->rPacketData[5])		return 1;
	else													return 0;
}


void proc_packet_error(U08 code)
{
	switch(code)
	{
		case PACKET_NO_ERR:			// No Error
			//Uart_Print(1, "PACKET_NO_ERR\n");
			//Uart_Putch(1, 0x00);
			break;
		case PACKET_LENGTH_ERR:		// Length Error
			//Uart_Print(1, "PACKET_LENGTH_ERR\n");
			break;	
		case PACKET_CHKSUM_ERR:		// Checksum Error
			//Uart_Print(1, "PACKET_CHKSUM_ERR\n");
			break;	
		case PACKET_END_ERR:		//End Error
			//Uart_Print(1, "PACKET_END_ERR\n");
			break;			
		default:
			break;
	}
}

void SendRequestPacket(U08 IND, U08 DATA)
{
	U08 TXParameter[4];
	U08 cnt;

	TXParameter[0] = PACKET_START;
	TXParameter[1] = IND;
	TXParameter[2] = DATA;
	TXParameter[3] = PACKET_END;

	for(cnt=0; cnt<4; cnt++)	
	{
		Uart_Putch(0, TXParameter[cnt]);
		//_delay_us(100);
	}
}

