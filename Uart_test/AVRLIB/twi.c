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
     TWSR = 0x00;             // ���·������� �ʱ�ȭ
     
     SCL_Master();            // SCL Output Set 
     //SCL_Slave();           // SCL �Է����� ����
     
     //SDA_SET_WR();            // SDA WR Set
     SDA_SET_RD();          // SDA RD Set
     SCL_Master();
     sbi(PORTD, 0);           // SCL 1������ �ʱ�ȭ
     sbi(PORTD, 1);           // SDA 1������ �ʱ�ȭ
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
U8 TWI_ACK( U8 Index )             // 0�϶��� ��ȣ ��û, 1�϶��� ��ȣ ���� 
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
     TWCR = 0xA4;        // START ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x08)); // START ����Ȯ��
     
     TWDR = (Address & 0xFE); // SLA+W �Է�
     
     TWCR = 0x84;        // SLA+W ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x18));  // SLA+W ����Ȯ��
     
     TWDR = Data;        // Data �Է�
     
     TWCR = 0x84;        // Data ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x28));  // Data ����Ȯ��
     
     TWCR = 0x94;        // STOP ����
}


//------------------------------------------------------------------------------ 
//             		===== TWI_Read_Data 2 =====
//------------------------------------------------------------------------------
U8 TWI_Read(U8 Address)
{
     U8 Data;
     
     TWCR = 0xA4;        // START ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x08)); // START ����Ȯ��
     
     TWDR = (Address & 0xFE) + 0x01; // SLA+R �Է�
     
     TWCR = 0x84;        // SLA+R ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x40));  // SLA+W ����Ȯ��
     
     TWCR = 0x84;        // Data ����
     while(((TWCR & 0x80) == 0x00) || ((TWSR & 0xF8) != 0x58));  // Data ����Ȯ��
     Data = TWDR;        // Data ����
     
     TWCR = 0x94;        // STOP ����
     
     return Data;        // ���ŵ���Ÿ ��ȯ
}
