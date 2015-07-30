/*==============================================================================
 *
 *   Text_Lcd Drive Module
 *
 *        File Name      : lcd_text.c 
 *        Version        : 1.0
 *        Date           : 2005.07.02
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Add Description: SST42D1100 / SLA7026M
 *        Modified       : 2005.12.11 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../define.h"
#include "../delay.h"
#include "lcd_text.h"

//------------------------------------------------------------------------------
// LCD 초기화 함수
//------------------------------------------------------------------------------
void Lcd_Init(void)
{
	
	LCD_PORT_SETUP();
	
	LCD_C_PORT = 0x00; // 0000 0000
	Delay(10);
	Command(FUNSET);
	Delay(100);
	Command(DISPON);
	Command(ALLCLR);
	Command(ENTMODE);
	
	Lcd_Print_Xy( 0, 0 ,"Lcd Init OK");

	Lcd_Print_Xy( 1, 0, "This is Test PRG");
}

void Busy(void)
{
	Delay(1000);
}
//------------------------------------------------------------------------------
// 명령 함수
//------------------------------------------------------------------------------
void Command( U8 byte )
{
	Busy();
	LCD_D_PORT = byte;
	LCD_C_PORT = 0x04; // 0000 0100
	Delay(1000);
	LCD_C_PORT = 0x00; // 0000 0000
}


//------------------------------------------------------------------------------
// 데이타 쓰기 함수
//------------------------------------------------------------------------------
void Data( U8 byte )
{
	Busy();
	LCD_D_PORT = byte;
	LCD_C_PORT = 0x05; // 0000 0101
	Delay(1000);
	LCD_C_PORT = 0x00; // 0000 0000
}


//------------------------------------------------------------------------------ 
//                 Lcd에 한칸에 문자 출력 
//------------------------------------------------------------------------------ 
void Put_Lcd_Char( U8 Lcd_Data )
{ 
     Data( Lcd_Data ); 
     Busy(); 
} 

//------------------------------------------------------------------------------ 
//                 Lcd에 String을 출력 
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
	Put_Lcd_String( Lcd_Data );		// 주소를 넘겨줘야 함
}

//---------------------------------------------------------------------------- 
//          		Lcd_ByteToHex
//          		HEX로 출력한다. 
//---------------------------------------------------------------------------- 
void Lcd_ByteToHex1(U8 ByteData) 
{
     U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
     U8 HexData; 

   	HexData = Hex_Table[ByteData>>4]; 
   	Lcd_Put_Char_Xy(0,0,HexData);   // 상위 비트를 출력 

    	HexData = Hex_Table[ByteData&0x0F]; 
    	Lcd_Put_Char_Xy(0,1,HexData);   // 하위 비트를 출력 
} 

void Lcd_ByteToHex2(U8 ByteData) 
{
     U8 Hex_Table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
  	U8 HexData; 

   	HexData = Hex_Table[ByteData>>4]; 
   	Lcd_Put_Char_Xy(0,2,HexData);   // 상위 비트를 출력 

   	HexData = Hex_Table[ByteData&0x0F]; 
   	Lcd_Put_Char_Xy(0,3,HexData);   // 하위 비트를 출력 
} 

