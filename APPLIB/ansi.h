/*==============================================================================
 *
 *   ANSI/VT100 Terminal Module
 *
 *     	File Name   	: ansi.h
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

#ifndef _ANSI_H_
#define _ANSI_H_

//------------------------------------------------------------------------------
//					===== Define : Attribute Mode =====
//------------------------------------------------------------------------------
#define ANSI_ATTR_OFF		0

#define ANSI_BOLD			1
#define ANSI_USCORE		    4
#define ANSI_BLINK			5
#define ANSI_REVERSE		7

#define ANSI_BOLD_OFF		21
#define ANSI_USCORE_OFF	    24
#define ANSI_BLINK_OFF		25
#define ANSI_REVERSE_OFF	27

//------------------------------------------------------------------------------
//					===== Define : Colors =====
//------------------------------------------------------------------------------
#define ANSI_BLACK			0 
#define ANSI_RED			1
#define ANSI_GREEN			2
#define ANSI_BROWN			3
#define ANSI_BLUE			4
#define ANSI_MAGENTA		5
#define ANSI_CYAN			6
#define ANSI_WHITE			7

//------------------------------------------------------------------------------
//					===== Define : Foreground Colors =====
//------------------------------------------------------------------------------
#define FG_BLACK			30 
#define FG_RED				31
#define FG_GREEN			32
#define FG_BROWN			33
#define FG_BLUE				34
#define FG_MAGENTA			35
#define FG_CYAN				36
#define FG_WHITE			37

//------------------------------------------------------------------------------
//					===== Define : Background Colors =====
//------------------------------------------------------------------------------
#define BG_BLACK			40 
#define BG_RED				41
#define BG_GREEN			42
#define BG_BROWN			43
#define BG_BLUE				44
#define BG_MAGENTA			45
#define BG_CYAN				46
#define BG_WHITE			47

//------------------------------------------------------------------------------
//					===== =====
//------------------------------------------------------------------------------


#define KEY_UP				(0xFF)
#define KEY_DOWN			(0xFE)
#define KEY_LEFT			(0xFD)
#define KEY_RIGHT			(0xFC)
#define KEY_BS				(0xFB)
#define KEY_RET				(0xFA)
#define KEY_TAB				(0xF9)

//------------------------------------------------------------------------------
//					===== =====
//------------------------------------------------------------------------------
#define FROM			0
#define UNTIL			1
#define ALL				2


//------------------------------------------------------------------------------
//          		===== Funtion Prototype =====
//------------------------------------------------------------------------------
void ANSI_Send(U8 data);
void ANSI_Send_Num(U8 data);
U8 ANSI_Getch(void);

void ANSI_Normal(void);
void ANSI_Underline(U8 mode);
void ANSI_Blink(U8 mode);
void ANSI_Reverse(U8 mode);
void ANSI_Bold(U8 mode);

void ANSI_SetColor(U8 fgcolor, U8 bgcolor);
void ANSI_ClearScreen(U8 where);
void ANSI_GotoXY(U8 x, U8 y);


void ANSI_Cursor_Up(U8 amount);
void ANSI_Cursor_Down(U8 amount);
void ANSI_Cursor_Right(U8 amount);
void ANSI_Cursor_Left(U8 amount);

void ANSI_Scroll_Region(U8 top, U8 bottom);
void ANSI_Line(U8 y);

U8 GetKey(void);

#endif
