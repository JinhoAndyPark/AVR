/*==============================================================================
 *
 *   
 *
 *        File Name      : LCD.h
 *        Version        : 1.0
 *        Date           : 2013.10.30
 *        Author         : Park, Jin-Ho (ROLAB 27th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Add_Description: SST42D1100 / SLA7026M
 *        Modified       : 2013.10.30 By Park, Jin-Ho
 *        Copyright(c)ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/// 
// 캐릭터LCD 포트제어방식(4비트모드)

#ifndef __LCD_H
#define __LCD_H


void lcd_iw(U08 inst); // LCD 명령출력함수.
void lcd_dw(U08 dw); // LCD 데이터출력함수.
void init_lcd(void); // LCD 초기화
void lcd_str(S08 *str); // 문자열출력함수.

#endif
