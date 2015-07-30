/*==============================================================================
 *
 *   Text_Lcd Drive Module
 *
 *        File Name      : lcd_text4bit.h
 *        Version        : 1.0
 *        Date           : 2006.03.12
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Add Description: 12*4 LINE
 *					  PA0-3 DATA LINE
 *					  PA4 - E
 * 					  PA5 - RS
 *        Modified       : 2006.03.12 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __Text_Lcd_H 
#define __Text_Lcd_H 

//Text Lcd 포트 정의
#define	LCD_D_PORT		PORTA 		// 데이타포트
#define	LCD_C_PORT		PORTB 		// 제어포트

#define	LCD_PORT_SETUP()	DDRA=0xff; DDRB=0xff; PORTA=0x00; PORTB=0x00; 	//포트셋팅


//Text Lcd 명령어 셋팅
#define	FUNSET1		0x38		//Function Set			0011 1000
#define	FUNSET2		0x28		//Function Set			0010 1000
#define	ENTMODE		0x06		//Entry Mode Set		0000 0110
#define	ALLCLR		0x01		//All Clear 			0000 0001
#define	DISPON		0x0e		//Display On			0000 1110
#define	LINE2		0xc0		//2nd Line Move		1100 0000
#define	CUR_HOME		0x02		//Cursor Home			0000 0010
#define	SHIFT_LEFT	0x10		//Cursor Shift Left		0001 0000 
#define	SHIFT_RIGHT	0x14		//Cursor Shift Right	0001 0100

// 내부 4k가 있으므로 외부의 경우 0번지가 0x1100번지에 해당함 
#define   LCD_IW    *((U8 *)0x1100) 
#define   LCD_IR    *((U8 *)0x1101) 
#define   LCD_DW    *((U8 *)0x1102) 
#define   LCD_DR    *((U8 *)0x1103) 

#define   CLEAR               0x01 
#define   CURSOR_HOME         0x02 

//ENTRY MODE SETUP 
#define   ENTRY_MODE_SET      0x04 
#define   ADDRESS_INC         0x02      // address increase 
#define   ADDRESS_DEC         0x00      // address decrese 

//DISPLAY ON /OFF SETUP 
#define   DISPLAY_ON_OFF_SET  0x08       
#define   DISPLAY_ON          0x04      // display on 
#define   DISPLY_OFF          0x00      // display off 
#define   CURSOR_ON           0x02      // CURSOR ON 
#define   CURSOR_OFF          0x00      // CURSOR OFF 
#define   BLINK_ON            0x01      // BLINK ON 
#define   BLINK_OFF           0x00      // BLINK OFF 

//CUSOR ON SHIFT SETUP 
#define   CURSOR_ON_SHIFT_SET 0x10 
#define   CURSOR_SHIFT_ON     0x80 
#define   CURSOR_SHIFT_OFF    0x00 
#define   SHIFT_RIGHT0         0x04 
#define   SHIFT_LEFT0          0x00 

//FUNCTION SETUP 
#define   FUNCTION_SET        0x20 
#define   DATA_LENGH_8BIT     0x10      // 8BIT 
#define   DATA_LENGH_4BIT     0x00      // 4BIT 
#define   LINE_2              0x08      // 2행 
#define   LINE_1              0x00      // 1행 
#define   F1                  0x04      // 4*10 도트 
#define   F0                  0x00      // 5*7 도트 

#define   CG_RAM_ADDRESS_SET  0x40 
#define   DD_RAM_ADDRESS_SET  0x80 

#define   BUSY_FLAG           0x80 



//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Lcd_Init(void);
void Lcd_Delay( unsigned long Cnt );
void Busy(void);
void Send_Bit4(U8 byte);
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
