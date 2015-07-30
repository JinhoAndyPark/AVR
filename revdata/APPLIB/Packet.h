/*==============================================================================
 *
 *   Packet Making Header
 *
 *   File Name   	: Packet.h
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

#ifndef __PACKET_H
#define __PACKET_H

#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "../define.h"
#include "../AVRLIB/Uart.h"

#define	NOT_YET		0
#define	DONE		1

#define	PACKET_START			0xFF
#define	PACKET_END				0xEE

#define PACKET_LENGTH			0x03

#define PACKET_NO_ERR			0
#define PACKET_LENGTH_ERR		1
#define PACKET_INDEX_ERR		2
#define PACKET_XCOD_ERR			3
#define PACKET_YCOD_ERR			4
#define PACKET_CHKSUM_ERR		5
#define PACKET_END_ERR			6


//-------------- PARTNER -> THISDEVICE ------------------
// INDEX
#define IND_RX_TXSTART			0x01		//data ´Ï¸Ú´ë·Î
#define IND_RX_PAGESTART		0x02		//data recieve start [data1: Length , data2: Page]
#define IND_RX_ZSTART			0x03		//data start bit of z-axis [data1: Xcod, data2: Ycod]
#define IND_RX_ZING				0x04		//data ing bit of z-axis [data1: Xcod, data2: Ycod]
#define IND_RX_ZEND				0x05		//data end bit of z-axis [data1: Xcod, data2: Ycod]
#define IND_RX_PAGEEND			0x06		//data recieve end [data1:Length , data2: Page]
#define IND_RX_TXEND			0x07

#define IND_RX_ASKREADY			0xA0

/*
0xFF 0x03 0x01 0x00 0x00 0x00 0xEE

startingpoint move -> respon

0xFF 0x03 0x02 256  0x00 0x00 0xEE
0xFF 0x03 0x03 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x05 10   10   0x00 0xEE
0xFF 0x03 0x03 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x05 10   10   0x00 0xEE
0xFF 0x03 0x06 256  0x00 0x00 0xEE

mode change [motor move] time delay???

0xFF 0x03 0x02 256  0x01 0x00 0xEE
0xFF 0x03 0x03 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x05 10   10   0x00 0xEE
0xFF 0x03 0x03 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x04 10   10   0x00 0xEE
0xFF 0x03 0x05 10   10   0x00 0xEE
0xFF 0x03 0x06 256  0x01 0x00 0xEE

mode change [motor move] time delay???

0xFF 0x03 0x07 0x00 0x00 0x00 0xEE
rosting
*/


// DATA

//-------------------------------------------------------

//-------------- THISDEVICE -> PARTNER ------------------
//INDEX
	/*//before
#define IND_TX_READY			0x01
#define IND_TX_NOTYET			0x02
#define IND_TX_PAGEERR			0x03
#define IND_TX_LENERR			0x04
#define IND_TX_RESPONSTBY		0x05
#define IND_TX_RESPONMOVE		0x06
#define IND_TX_RESPONEND		0x07
*/
	//after
#define IND_TX_STATE			0x01
#define IND_TX_PAGEERR			0x02
#define IND_TX_NEXTPAGE			0x03

//DATA
#define DATA_TX_READY			0xA0
#define DATA_TX_STANDBY			0xB0
#define DATA_TX_RUN				0xC0
//-------------------------------------------------------

#define MAX_LEN					0x30

#define RXREADY					0
#define RXBUFFERING				1
#define RXEND					2


typedef struct rs232_context
{
	U16 isr_cnt;		// for counting # of data
	U16 b_start;		// valid interval for receiving data
	U08 rPacketData[MAX_LEN];
}UART_CONTEXT;


typedef enum packet_state
{
	PK_ST_INIT=0,
	PK_ST_LENGTH,
	PK_ST_INDEX,
	PK_ST_XCOD,
	PK_ST_YCOD,
	PK_ST_CHKSUM,
	PK_ST_END,
	PK_ST_UNKNOWN
}PACKET_STATE;

typedef struct packet_decode
{
	U08 index;	
	U08 xcod;
	U08 ycod;
	U08 end;

	U16 data_len;
	U08 data[MAX_LEN];

	U08 checksum;
	U08 error_code;

	U16 timeout_cnt;
	
}PARTNER_PACKET;


void proc_packet_read_status(PARTNER_PACKET *packet);
void proc_packet_command(PARTNER_PACKET *packet);
void proc_packet_error(U08 code);

U16 Checksum(PARTNER_PACKET *packet, UART_CONTEXT *context);
void Init_packet( PARTNER_PACKET *packet, UART_CONTEXT *context );
void PacketManager( PARTNER_PACKET *packet, UART_CONTEXT *context );

void SendRequestPacket(U08 IND, U08 DATA);

#endif

