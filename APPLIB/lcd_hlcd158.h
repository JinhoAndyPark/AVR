/*==============================================================================
 *
 *   Hlcd158 Drive Module
 *
 *        File Name   		: lcd_hlcd158.c 
 *        Version        	: 1.2
 *        Date           	: 2005.11.19
 *        Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.02.03 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __Hlcd158_Lcd_H 
#define __Hlcd158_Lcd_H 

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------

void Hlcd158_Init(void);
void Hlcd158_Clear(void);
void Hlcd158_Locate(U8 Locate_X,U8 Locate_Y);
void Hlcd158_font_A(void);
void Hlcd158_font_B(void);
void Hlcd158_Inversion_ON(void);
void Hlcd158_Inversion_OFF(void);
void Hlcd158_KS_A(void);
void Hlcd158_KS_B(void);
void Hlcd158_PrintString(char *PrintString);
void Hlcd158_Print8BitNum(U8 Print8BitNum);
void Hlcd158_Print8BitNum_Substance(U8 Print8BitNum);
void Hlcd158_Print16BitNum(U16 Print16BitNum);
void Hlcd158_Graphic();

#endif
