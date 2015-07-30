/*==============================================================================
 *
 *   ANSI/VT100 Terminal Module
 *
 *     	File Name   	: ansi.c
 *    	Version        	: 1.0
 *    	Date           	: 2006.07.09
 * 		Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *     	MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: IAR Eebedded Workbench 4.1
 *    	Modified       	: 2006.07.09 By Yoonseok Pyo
 *     	Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *    	All Rights Reserved.
 *
 *		NOTE : 이 모듈은 '이야기멀티'를 기반으로 작성하였으며 ANSI 규약과
 *			  VT100 터미널 규약을 기반으로 짜여져 있습니다.
==============================================================================*/


//------------------------------------------------------------------------------
//                 			=== Include Headerfile ===
//------------------------------------------------------------------------------
#include <iom128.h>
#include "../define.h"
#include "ansi.h"
#include "../AVRLIB/uart.h"

#define COM		UART1		// UART 변경시 매개변수를 수정하라. (UART0 or UART1)

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------ 
//				===== ANSI DATA 전송 =====
//------------------------------------------------------------------------------
void ANSI_Send(U8 data)
{
	Uart_Putch(COM, data);
}

void ANSI_Send_Num(U8 data)
{
	Uart_U8Bit_PutNum_Substance(COM,data);
}

U8 ANSI_Getch(void)
{
	return Uart_Getch(COM);
}

//------------------------------------------------------------------------------ 
//				===== Set Attribute Mode =====
//------------------------------------------------------------------------------
void ANSI_Normal(void)			// 글자 기본 속성
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send('0');
	ANSI_Send('m');
}

void ANSI_Underline(U8 On_Off)	// 글자 밑줄 속성
{
	ANSI_Send(0x1B);
	ANSI_Send('[');

	if (On_Off==OFF)
		ANSI_Send('2');

	ANSI_Send('4');
	ANSI_Send('m');
}

void ANSI_Blink(U8 On_Off)		// 글자 깜박임 속성
{
	ANSI_Send(0x1B);
	ANSI_Send('[');

	if (On_Off==OFF)
		ANSI_Send('2');

	ANSI_Send('5');
	ANSI_Send('m');
}

void ANSI_Reverse(U8 On_Off)	// 글자 반전 속성
{
	ANSI_Send(0x1B);
	ANSI_Send('[');

	if (On_Off==OFF)
		ANSI_Send('2');

	ANSI_Send('7');
	ANSI_Send('m');
}

void ANSI_Bold(U8 On_Off)		// 글자 굵은 속성
{
	ANSI_Send(0x1B);
	ANSI_Send('[');

	if (On_Off==OFF)
		ANSI_Send('2');

	ANSI_Send('2');
	ANSI_Send('m');
}


//------------------------------------------------------------------------------ 
//				===== Set Color Attributes =====
//------------------------------------------------------------------------------
void ANSI_SetColor(U8 foreground, U8 background)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send('3');
	ANSI_Send(foreground + '0');
	ANSI_Send(';');
	ANSI_Send('4');
	ANSI_Send(background + '0');
	ANSI_Send('m');
}

//------------------------------------------------------------------------------ 
//				===== Erasing Text =====
//------------------------------------------------------------------------------
void ANSI_ClearScreen(U8 where)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');

   	if (where==0)			// 커서부터 지우기 
		ANSI_Send('0');
   	else if (where==1)		// 커서까지 지우기
		ANSI_Send('1');
   	else 					// 전체 지우기
		ANSI_Send('2');		
    
	ANSI_Send('J');
}

//------------------------------------------------------------------------------ 
//				===== Cursor Control  =====
//------------------------------------------------------------------------------
void ANSI_GotoXY(U8 x, U8 y)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
  	ANSI_Send_Num(y);	// ROW
	ANSI_Send(';');
   	ANSI_Send_Num(x);	// COLMUN
	ANSI_Send('H');
}


void ANSI_Cursor_Up(U8 amount)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send_Num(amount);
	ANSI_Send('A');
}

void ANSI_Cursor_Down(U8 amount)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send_Num(amount);
	ANSI_Send('B');
}

void ANSI_Cursor_Left(U8 amount)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send_Num(amount);
	ANSI_Send('C');
}

void ANSI_Cursor_Right(U8 amount)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send_Num(amount);
	ANSI_Send('D');
}



//------------------------------------------------------------------------------ 
//				===== Scrolling  =====
//------------------------------------------------------------------------------
void ANSI_Scroll_Region(U8 top, U8 bottom)
{
	ANSI_Send(0x1B);
	ANSI_Send('[');
	ANSI_Send_Num(top);
	ANSI_Send(';');
	ANSI_Send_Num(bottom);
	ANSI_Send('r');
}

//------------------------------------------------------------------------------ 
//				===== 라인긋기  =====
//------------------------------------------------------------------------------
void ANSI_Line(U8 y)
{
	U8 temp;
	
	ANSI_GotoXY(0, y);
	
	for (temp=0; temp<=39; temp++)
	{
		ANSI_Send(0xa6);
		ANSI_Send(0xa1);
	}
}


//------------------------------------------------------------------------------ 
//				===== 화면제어 =====
//------------------------------------------------------------------------------
U8 GetKey(void)
{
	U8 c;

	c=ANSI_Getch();

	if (c==0x1b)
	{
		c=ANSI_Getch();
		if (c==0x5b)
		{
			c=ANSI_Getch();
			switch (c)
			{
				case 0x41:	{ ANSI_Cursor_Up(1);	return KEY_UP; }
				case 0x42:	{ ANSI_Cursor_Down(1);	return KEY_DOWN; }
				case 0x43:	{ ANSI_Cursor_Left(1);	return KEY_LEFT; }
				case 0x44:	{ ANSI_Cursor_Right(1);	return KEY_RIGHT; }
				default: 	{ return c; }
			}
		}
		return c;
	}

	else if (c=='\r')
	{
		ANSI_Send('\n');
		return KEY_RET;
	}

	else if (c=='\b')
	{
		ANSI_Send('\b');
		ANSI_Send(' ');
		ANSI_Send('\b');
		return KEY_BS;
	}

	else if (c=='\t')
	{
		ANSI_Send('\t');
		return KEY_TAB;
	}

	ANSI_Send(c);
	return c;
}

