/*==============================================================================
 *
 *   Two Wire Serial Interface Module
 *
 *        File Name   		: Twi.c
 *        Version        	: 1.2
 *        Date           	: 2006.01.18
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "twi.h"
#include "uart.h"
#include "delay.h"

//------------------------------------------------------------------------------ 
//     				===== TWI Initialize ===== 
//------------------------------------------------------------------------------
void Init_TWI(void) 
{
     TWBR = 12;               // 400kHz (TWBR=12, TWPS=0)
     TWSR = 0x00;             // 상태레지스터 초기화
     
     SCL_Master();            // SCL Output Set 
     //SCL_Slave();           // SCL 입력으로 설정
     
     //SDA_SET_WR();            // SDA WR Set
     SDA_SET_RD();          // SDA RD Set
     SCL_Master();
     sbi(PORTD, 0);           // SCL 1값으로 초기화
     sbi(PORTD, 1);           // SDA 1값으로 초기화
} 


//------------------------------------------------------------------------------ 
//              		===== TWI_Write_Data ===== 
//------------------------------------------------------------------------------
void TWI_Write_Data( U8 Data ) 
{
     static U8 i; 
     static U8 Data_Temp = 0; 
     
     for(i = 0; i < 8; i++) 
     {
          Data_Temp = Data; 
          Data_Temp = ( (Data_Temp >> (7 - i)) & 0x01); 
          
          if(Data_Temp == 1)
            sbi( PORTD, 1 );
          if(Data_Temp == 0)
            cbi( PORTD, 1 );
          
          //SCL_Pulse();
     } 
} 


//------------------------------------------------------------------------------ 
//                    	===== TWI_Read_Data =====
//------------------------------------------------------------------------------
U8 TWI_Read_Data( void ) 
{ 
     static U8 i; 
     static U8 Data = 0; 
     static U8 Data_Temp = 0; 
     
     SDA_SET_RD();
     
     for(i = 0; i < 8; i++) 
     {
          Data_Temp = (U8)SDA_READ(); 
          Data |= ( ( Data_Temp << (7 - i)) & 0xff ); 
          
          //SCL_Pulse();
     }
     
     SDA_SET_WR();
     
     Uart_Print(UART1,"Read Data = ");
     Uart_U8Bit_PutNum(UART1, Data );
     Uart_Print(UART1,"\n"); 

     return Data; 
} 


//------------------------------------------------------------------------------ 
//            			===== TWI_Acknowledges =====
//------------------------------------------------------------------------------
U8 TWI_ACK( U8 Index )             // 0일때는 신호 요청, 1일때는 신호 보냄 
{
     static U8 Data = 0; 
     static U8 SDA_Data = 0; 

     if( Index == 0 ) 
     { 
          SDA_SET_RD(); 
                 
          cbi(PORTD, 0);           // SCL LOW SET 
          Delay_us(10); 
                                 
          sbi(PORTD, 0);           // SCL HIGH SET 
          Delay_us(10); 
                 
          SDA_Data = SDA_READ(); 
                 
          Delay_us(10); 
          cbi(PORTD, 0);           // SCL LOW SET 
                 
          SDA_SET_WR(); 
                 
          if(SDA_Data == 0) 
               Data = 1;           // ACK ON 
          if(SDA_Data == 1) 
               Data = 0;           // ACK OFF 
                         
     } 
     if( Index == 1 )
     {
          cbi(PORTD, 1);           //SDA LOW SET 
          Delay_us(10);
          
          //SCL_Pulse();
     }
     
     return Data; 
         
} 


//------------------------------------------------------------------------------ 
//           			===== TWI_Write_Data 2 =====
//------------------------------------------------------------------------------
void TWI_Write(U8 Address, U8 Data)
{
     TWCR = 0xA4;        // START 전송
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x08)); // START 전송확인
     
     TWDR = (Address & 0xFE); // SLA+W 입력
     
     TWCR = 0x84;        // SLA+W 전송
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x18));  // SLA+W 전송확인
     
     TWDR = Data;        // Data 입력
     
     TWCR = 0x84;        // Data 전송
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x28));  // Data 전송확인
     
     TWCR = 0x94;        // STOP 전송
}


//------------------------------------------------------------------------------ 
//             		===== TWI_Read_Data 2 =====
//------------------------------------------------------------------------------
U8 TWI_Read(U8 Address)
{
     U8 Data;
     
     TWCR = 0xA4;        // START 전송
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x08)); // START 전송확인
     
     TWDR = (Address & 0xFE) + 0x01; // SLA+R 입력
     
     TWCR = 0x84;        // SLA+R 전송
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x40));  // SLA+W 전송확인
     
     TWCR = 0x84;        // Data 수신
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x58));  // Data 수신확인
     Data = TWDR;        // Data 저장
     
     TWCR = 0x94;        // STOP 전송
     
     return Data;        // 수신데이타 반환
}
