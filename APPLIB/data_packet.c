/*==============================================================================
 *
 *   Packet Communication Module
 *
 *        File Name   		: data_packet.c
 *        Version        	: 1.2
 *        Date           	: 2006.02.02
 *        Author         	: Sayhacker (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.05 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "data_packet.h"

//------------------------------------------------------------------------------
//       			=== 네트워크 패킷의 식별자 검출함수 ===
//------------------------------------------------------------------------------
U8 Get_NetPacket_ID(U8 Packet)
{
	return Packet >> 7; 
}

//------------------------------------------------------------------------------
//            		=== Action Packet 생성 함수 ===
// 				: 10비트의 값과, 행동 식별자를 입력해주면, 액션 패킷을 리턴해준다.
//------------------------------------------------------------------------------
U16 Make_ActPacket(U16 Value, U16 Type) 
{
	U16 ActPacket;
	Type <<= 10;
	ActPacket = Value & 1023;
	ActPacket |= Type;

	return ActPacket;
}

//------------------------------------------------------------------------------
//              	=== Action -> Network Packet 생성 함수 ===
// 				: 액션패킷을 네트워크 패킷으로 만들어준다.
//------------------------------------------------------------------------------
void Split_As_NetPacket(U8 *NetPacket_H, U8 *NetPacket_L, U16 ActPacket)
{
	U16 CovertorTemp;
     
	CovertorTemp = ActPacket & (U16)127;
	*NetPacket_L = (U8)CovertorTemp;

	CovertorTemp = (ActPacket>>7)& (U16)127;
	CovertorTemp |= 128;
	*NetPacket_H = (U8)CovertorTemp;
}

//------------------------------------------------------------------------------
//              	===  Network -> Action Packet 생성 함수 ===
// 				: 네트워크 패킷을  액션 패킷으로 만들어준다.
//------------------------------------------------------------------------------
U16 Combine_As_ActPacket(U8 NetPacket_H, U8 NetPacket_L)
{
	U16 ActPacket;

	if ( Get_NetPacket_ID(NetPacket_H) != 1 ) return 0xffff;
	if ( Get_NetPacket_ID(NetPacket_L) != 0 ) return 0xffff;

	NetPacket_H = NetPacket_H & 127;
	NetPacket_L = NetPacket_L & 127;

	ActPacket = (U16)NetPacket_H;
	ActPacket <<= 7;
	ActPacket |= (U16)NetPacket_L;

	return ActPacket;
}

