/*==============================================================================
 *
 *   Text_Lcd Drive Module
 *
 *        File Name      : Text_Lcd.c 
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

#ifndef __Text_Lcd_H 
#define __Text_Lcd_H 

//Text Lcd 포트 정의
#define	LCD_D_PORT	PORTC // 데이타포트
#define	LCD_C_PORT	PORTG // 제어포트

#define	LCD_PORT_SETUP()	DDRC = 0xff; DDRG = 0x07;  //포트셋팅


//Text Lcd 명령어 셋팅
#define	FUNSET		0x38		//Function Set			0011 1000
#define	ENTMODE		0x06		//Entry Mode Set		0000 0110
#define	ALLCLR		0x01		//All Clear 			0000 0001
#define	DISPON		0x0e		//Display On			0000 1110
#define	LINE2		0xc0		//2nd Line Move		1100 0000
#define	CUR_HOME		0x02		//Cursor Home			0000 0010
#define	SHIFT_LEFT	0x10		//Cursor Shift Left		0001 0000 
#define	SHIFT_RIGHT	0x14		//Cursor Shift Right	0001 0100


//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Lcd_Init(void);
void Busy(void);
void Command( U8 byte);
void Data( U8 byte);
void Put_Lcd_Char( U8 Lcd_Data );
void Put_Lcd_String( U8 *Lcd_Data);
void Display_Position( U8 line, U8 col );
void Lcd_Put_Char_Xy( U8 line, U8 col, U8 Lcd_Data);
void Lcd_Print_Xy( U8 line, U8 col, U8 *Lcd_Data);
void Lcd_ByteToHex1(U8 ByteData);
void Lcd_ByteToHex2(U8 ByteData);

#endif
