/*==============================================================================
 *
 *  Ax_Motor_Module
 *
 *        File Name      : motor_ax.c
 *        Version        : 1.1
 *        Date           : 2006.03.26
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.03.26 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#include "main.h"
#include "define.h"
#include "uart.h"
#include "motor_ax.h"

U8 RxBufferReadPointer;
U8 Parameter[128];
U8 RxBuffer[128];
U8 TxBuffer[128];
U8 RxBufferWritePointer;
volatile U8 RxInterruptBuffer[256];

extern U08 ID,TxPacketLength, RxPacketLength;
extern U08 Parameter[128], RxBufferReadPointer, RxBuffer[128], TxBuffer[128];
extern volatile U08 RxInterruptBuffer[256];
extern U08 RxBufferWritePointer;


U8 TxPacket(U8 ID,U8 Instruction,U8 ParameterLength)
{
     U8 Count,CheckSum,PacketLength;



     TxBuffer[0] = 0xff;
     TxBuffer[1] = 0xff;
     TxBuffer[2] = ID;
     TxBuffer[3] = ParameterLength+2;
     TxBuffer[4] = Instruction;
     for( Count = 0; Count < ParameterLength ;+ Count++ )
     {
          TxBuffer[Count+5] = Parameter[Count];
     }
     CheckSum = 0;

     PacketLength = ParameterLength +4+2;



     for( Count = 2; Count < PacketLength-1; Count++ ) //except 0xff,checksum
     {
         CheckSum += TxBuffer[Count];
     }
     TxBuffer[Count] = ~CheckSum;

     RS485_TXD;


     for(Count = 0; Count < PacketLength; Count++)
     {
         sbi(UCSR0A,6);       //SET_TXD0_FINISH;
         Uart_Putch(UART0,(TxBuffer[Count]));
     }
     while(!CHECK_TXD0_FINISH); //Wait until TXD Shift register empty


     RS485_RXD;
	


     return(PacketLength);
}



U8 RxPacket(U8 RxPacketLength)
{
     #define RX_TIMEOUT_COUNT2   3000L
     #define RX_TIMEOUT_COUNT1  (RX_TIMEOUT_COUNT2*10L)

     U32 Counter;
     U8  Count, Length, Checksum;
     U8  Timeout;

     Timeout = 0;
     for(Count = 0; Count < RxPacketLength; Count++)
     {
          Counter = 0;
          while(RxBufferReadPointer == RxBufferWritePointer)
          {
               if(Counter++ > RX_TIMEOUT_COUNT1)
               {
                    Timeout = 1;
                    break;
               }
          }
          if(Timeout) break;
          RxBuffer[Count] = RxInterruptBuffer[RxBufferReadPointer++];
     }
     Length = Count;
     Checksum = 0;

     if(TxBuffer[2] != BROADCASTING_ID)
     {
          if(Timeout && RxPacketLength != 255)
          {
               //Uart_Print(UART1,"\r\n [Error:RxD Timeout]");
               CLEAR_BUFFER;
          }

          if(Length > 3)
          {
               if(RxBuffer[0] != 0xff || RxBuffer[1] != 0xff )
               {
                    //Uart_Print(UART1,"\r\n [Error:Wrong Header]");
                    CLEAR_BUFFER;
                    return 0;
               }
               if(RxBuffer[2] != TxBuffer[2] )
               {
                    //Uart_Print(UART1,"\r\n [Error:TxID != RxID]");
                    CLEAR_BUFFER;
                    return 0;
               }
               if(RxBuffer[3] != Length-4)
               {
                    //Uart_Print(UART1,"\r\n [Error:Wrong Length]");
                    CLEAR_BUFFER;
                    return 0;
               }
               for(Count = 2; Count < Length; Count++) Checksum += RxBuffer[Count];
               if(Checksum != 0xff)
               {
                    //Uart_Print(UART1,"\r\n [Error:Wrong CheckSum]");
                    CLEAR_BUFFER;
                    return 0;
               }
          }
     }
     return Length;
}

void ID_Setting(U08 bID, U08 cID)
{
	Parameter[0] = P_ID;
	Parameter[1] = cID;
	TxPacketLength = TxPacket(bID, INST_WRITE, 2);
	RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

void Baud_Setting(U08 ID, U08 BAUD)
{
	Parameter[0] = P_BAUD_RATE;
	Parameter[1] = BAUD;
	TxPacketLength = TxPacket(ID, INST_WRITE, 2);
	RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

void Torque_Enable(U08 ID)
{
	Parameter[0] = P_TORQUE_ENABLE;
	Parameter[1] = 0x01;
	TxPacketLength = TxPacket(ID, INST_WRITE, 2);
	RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

void AX_Action(U08 ID, U08 Position_H, U08 Position_L, U08 Speed_H, U08 Speed_L)
{
	Parameter[0] = P_GOAL_POSITION_L;
	Parameter[1] = Position_L;
	Parameter[2] = Position_H;
	Parameter[3] = Speed_L;
	Parameter[4] = Speed_H;
	TxPacketLength = TxPacket(ID,INST_WRITE,5);
	RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}
