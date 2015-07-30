/*==============================================================================
 *
 *   Packet Communication Module
 *
 *        File Name   		: data_packet.h
 *        Version        	: 1.1
 *        Date           	: 2006.02.02
 *        Author         	: sayhacker (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.02 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
 * 
==============================================================================*/

#ifndef __PACKET_H
#define __PACKET_H


//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

U8 get_net_packet_identity( U8 packet );
U16 Make_ActPacket( U16 Value, U16 Type);
void Split_As_NetPacket(U8 *NetPacket_H, U8 *NetPacket_L, U16 ActPacket);
U16 Combine_As_ActPacket(U8 NetPacket_H, U8 NetPacket_L);

#endif
