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
// ĳ����LCD ��Ʈ������(4��Ʈ���)

#ifndef __LCD_H
#define __LCD_H


void lcd_iw(U08 inst); // LCD ��������Լ�.
void lcd_dw(U08 dw); // LCD ����������Լ�.
void init_lcd(void); // LCD �ʱ�ȭ
void lcd_str(S08 *str); // ���ڿ�����Լ�.

#endif