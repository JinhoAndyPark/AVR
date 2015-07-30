#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header

#include "../define.h"
#include "../AVRLIB/uart.h"
#include "motor_ax.h"

U08 RxBufferReadPointer;
U08 Parameter[128];
U08 RxBuffer[128];
U08 TxBuffer[128];
U08 RxBufferWritePointer;
volatile U08 RxInterruptBuffer[256];

U08 ID,TxPacketLength, RxPacketLength;
U08 Parameter[128], RxBufferReadPointer, RxBuffer[128], TxBuffer[128];
volatile U08 RxInterruptBuffer[256];
U08 RxBufferWritePointer;


U08 TxPacket(U08 ID, U08 Instruction, U08 ParameterLength)
{
     U08 Count,CheckSum,PacketLength;



     TxBuffer[0] = 0xff;
     TxBuffer[1] = 0xff;
     TxBuffer[2] = ID;
     TxBuffer[3] = ParameterLength+2;
     TxBuffer[4] = Instruction;
     for( Count = 0; Count < ParameterLength ; Count++ )
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
         Uart_Putch(0,(TxBuffer[Count]));
     }
     //while(!CHECK_TXD0_FINISH); //Wait until TXD Shift register empty


     RS485_RXD;
	


     return(PacketLength);
}



U08 RxPacket(U08 RxPacketLength)
{
     #define RX_TIMEOUT_COUNT2   3000L
     #define RX_TIMEOUT_COUNT1  (RX_TIMEOUT_COUNT2*10L)

     U32 Counter;
     U08  Count, Length, Checksum;
     U08  Timeout;

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
               CLEAR_BUFFER;
          }

          if(Length > 3)
          {
               if(RxBuffer[0] != 0xff || RxBuffer[1] != 0xff )
               {
                    CLEAR_BUFFER;
                    return 0;
               }
               if(RxBuffer[2] != TxBuffer[2] )
               {
                    CLEAR_BUFFER;
                    return 0;
               }
               if(RxBuffer[3] != Length-4)
               {
                    CLEAR_BUFFER;
                    return 0;
               }
               for(Count = 2; Count < Length; Count++) Checksum += RxBuffer[Count];
               if(Checksum != 0xff)
               {
                    CLEAR_BUFFER;
                    return 0;
               }
          }
     }
     return Length;
}

void AX_Action(U08 ID, U08 Position_H, U08 Position_L, U08 Speed_H, U08 Speed_L)
//ID가 일치하는 모터가 position으로 setting된 speed로 이동한다.
{
	Parameter[0] = P_GOAL_POSITION_L;		//goal position address : 30
	Parameter[1] = Position_L;				//Low 8bit at goal position
	Parameter[2] = Position_H;				//High 8bit at goal position
	Parameter[3] = Speed_L;				//Low 8bit at moving speed 
	Parameter[4] = Speed_H;				//High 8bit at moving speed
	TxPacketLength = TxPacket(ID,INST_WRITE,5);
	//RxPacketLength = RxPacket(DEFAULT_RETURN_PACKET_SIZE);
}

