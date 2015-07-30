/*==============================================================================
 *
 *  Ax Motor_Module
 *
 *        File Name      : ax_exampe.c
 *        Version        : 1.0
 *        Date           : 2006.12.29
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.12.96 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/

#include<iom128.h>
#include"../define.h"
#include"../delay.h"
#include"uart.h"
#include"ax_motor.h"
#include"ax_example.h"


extern U8 ID,TxPacketLength, RxPacketLength;
extern U8 Parameter[128], RxBufferReadPointer,RxBuffer[128],TxBuffer[128];
extern volatile U8 RxInterruptBuffer[256];
extern U8 RxBufferWritePointer;

void ID_Setting(U8 bID, U8 cID)     //ID change
{
    Parameter[0] = P_ID; //Address of Firmware Version
    Parameter[1] = cID;  // Changed ID
    TxPacketLength = TxPacket(bID,INST_WRITE,2);      // before ID
    RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

void Baud_Setting(U8 ID, U8 BAUD)   //BAUD change
{
    Parameter[0] = P_BAUD_RATE;     //Address of Firmware Version
    Parameter[1] = BAUD;            // Changed BAUD
    TxPacketLength = TxPacket(ID,INST_WRITE,2);      // before BAUD
    RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}
void Ax_Test(U8 ID,U8 Position_H,U8 Position_L,U8 Spped_H, U8 Spped_L )     // Position, Speed Setting
{
    Parameter[0] = P_GOAL_POSITION_L;   //Address of Firmware Version
    Parameter[1] = Position_L;          //Writing Data P_GP_GOAL_POSITION_HOAL_POSITION_L
    Parameter[2] = Position_H;          //Writing Data
    Parameter[3] = Spped_L;             //Writing Data P_GOAL_SPEED_L
    Parameter[4] = Spped_H;             //Writing Data P_GOAL_SPEED_H
    TxPacketLength = TxPacket(ID,INST_WRITE,5);
    RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

void Torque_Enable(U8 ID)     // Torque_On
{
     Parameter[0] = P_TORQUE_ENABLE; //Address of Firmware Version
     Parameter[1] = 0x01;

     TxPacketLength = TxPacket(ID,INST_WRITE,2);
     RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}
void Endless_Turn(U8 ID)       // Endless_Turn Setting
{
     Parameter[0] = P_CW_ANGLE_LIMIT_L;     //Address of Firmware Version
     Parameter[1] = 0x00;                   //CW Angle Limit_L
     Parameter[2] = 0x00;                   //CW Angle Limit_H

     TxPacketLength = TxPacket(0x01,INST_WRITE,3);
     RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);


     Parameter[0] = P_CCW_ANGLE_LIMIT_L;    //Address of Firmware Version
     Parameter[1] = 0x00;                   //CCW Angle Limit_L
     Parameter[2] = 0x00;                   //CCW Angle Limit_H

     TxPacketLength = TxPacket(ID,INST_WRITE,3);
     RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);

}

void Position_View(U8 ID)       // Motor Position View
{
    U8 Position_H;
    U8 Position_L;

    Parameter[0] = P_PRESENT_POSITION_L;     //Reading Address
    Parameter[1] = 0x02;                     //Read Length

    TxPacketLength = TxPacket(ID,INST_READ,2);
    RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE + Parameter[1]);
    Position_H  = RxBuffer[6];
    Position_L = RxBuffer[5];

	Uart_Print(UART1,",");
    Uart_ByteToHexPutch(UART1,Position_H);
	Uart_Print(UART1,",0x");
    Uart_ByteToHexPutch(UART1,Position_L);
    Uart_Print(UART1,"\r\n ");
}
