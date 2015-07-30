/*==============================================================================
 *
 *   Text_Lcd Drive Module
 *
 *        File Name      : Text_Lcd_DATA4.c 
 *        Version        : 1.0
 *        Date           : 2006.03.12
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.03.12 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "../delay.h"
#include "lcd_text4bit.h"


//------------------------------------------------------------------------------
//	Add Description
//  		LCD TYPE 	: 	12*4 LINE
//					4BIT ������
//
//		PORT SET 	:	PA4-DATA4		PA5-DATA5
//					PA6-DATA6		PA7-DATA7
//					PB7-E
// 					PB6-RS
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// LCD �ʱ�ȭ �Լ�
//------------------------------------------------------------------------------
void Lcd_Init(void)
{
	LCD_PORT_SETUP();
	
	LCD_C_PORT = 0x00; // 0000 0000
	Lcd_Delay(10);
	Command(FUNSET1);
	Lcd_Delay(10);
     Command(FUNSET2);
	Lcd_Delay(10);
	Command(DISPON);
	Command(ALLCLR);
	Command(ENTMODE);
	


//	Command(DISPON);
//	Command(ALLCLR);
//	Command(ENTMODE);
     
	Lcd_Print_Xy( 0, 0 ,"Lcd Init OK");

	Lcd_Print_Xy( 1, 0, "This is Test PRG");
}


void Lcd_Delay( unsigned long Cnt )
{
     while( Cnt -- )
     {
		Delay( 10000 );
     }
}

void Busy(void)
{
	Delay(4000);
}

//------------------------------------------------------------------------------
// 4��Ʈ ����
//------------------------------------------------------------------------------
void Send_Bit4( U8 byte )
{
	LCD_D_PORT =  ( byte & 0xF0 ) ;
//	Delay(10);
     LCD_D_PORT =  ((byte << 4) & 0xF0 ) ;
}

//------------------------------------------------------------------------------
// ���� �Լ�
//------------------------------------------------------------------------------
void Command( U8 byte )
{
	Busy();
	LCD_C_PORT = 0x80; // 0000 0100
     Send_Bit4( byte);
	LCD_C_PORT = 0x00; // 0000 0000
}


//------------------------------------------------------------------------------
// ����Ÿ ���� �Լ�
//------------------------------------------------------------------------------
void Data( U8 byte )
{
	Busy();
     LCD_C_PORT = 0xC0; // 0000 0101
     
	Send_Bit4( byte);
     
	LCD_C_PORT = 0x00; // 0000 0000

}


//------------------------------------------------------------------------------ 
//                 Lcd�� ��ĭ�� ���� ��� 
//------------------------------------------------------------------------------ 
void Put_Lcd_Char( U8 Lcd_Data )
{ 
     Data( Lcd_Data ); 
     Busy(); 
} 

//------------------------------------------------------------------------------ 
//                 Lcd�� String�� ��� 
//------------------------------------------------------------------------------ 
void Put_Lcd_String( U8 *Lcd_Data) 
{ 
	while(*Lcd_Data != 0x00) 
	{ 
		 Put_Lcd_Char(*Lcd_Data); 
		 ++Lcd_Data;
	} 
} 


//------------------------------------------------------------------------------ 
//                 Display Position Setting Function 
//------------------------------------------------------------------------------ 
void Display_Position( U8 line, U8 col ) 
{ 
     if( line == 0 ) 
     	Command( 0x80 + col );
     else 
          Command( 0xc0 + col ); 
} 

void Lcd_Put_Char_Xy( U8 line, U8 col, U8 Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_Char( Lcd_Data );
}

void Lcd_Print_Xy( U8 line, U8 col, U8 *Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_String( Lcd_Data );		// �ּҸ� �Ѱ���� ��
}

//---------------------------------------------------------------------------- 
//          		Lcd_ByteToHex
//          		HEX�� ����Ѵ�. 
//---------------------------------------------------------------------------- 
void Lcd_ByteToHex1(U8 ByteData) 
{
     U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
     U8 HexData; 

   	HexData = Hex_Table[ByteData>>4]; 
   	Lcd_Put_Char_Xy(0,0,HexData);   // ���� ��Ʈ�� ��� 

    	HexData = Hex_Table[ByteData&0x0F]; 
    	Lcd_Put_Char_Xy(0,1,HexData);   // ���� ��Ʈ�� ��� 
} 

void Lcd_ByteToHex2(U8 ByteData) 
{
     U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  	U8 HexData; 

   	HexData = Hex_Table[ByteData>>4]; 
   	Lcd_Put_Char_Xy(0,2,HexData);   // ���� ��Ʈ�� ��� 

   	HexData = Hex_Table[ByteData&0x0F]; 
   	Lcd_Put_Char_Xy(0,3,HexData);   // ���� ��Ʈ�� ��� 
} 
