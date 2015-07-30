
/*==============================================================================
 *
 *   
 *
 *        File Name      : LCD.c
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
//ĳ����LCD ��Ʈ������(4��Ʈ���)
#include <avr/io.h>
#include <util/delay.h>
#include "../Define.h"
#include "Lcd.h"

//extern U08 *str1="<Welcome to 3D>";
//extern U08 *str2="<YYYY>";

void lcd_iw(U08 inst) // LCD �������Լ�.
{
	PORTG = 0x04; // LCD����ɾ�����μ���
	PORTD = inst & 0xf0; // ��ɾ����4��Ʈ����
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x04;
	PORTD = inst << 4; // ��ɾ�����4��Ʈ����
	PORTG &= 0xfb; // LCD Disable
	_delay_ms(2);
}
void lcd_dw(U08 dw) // LCD ����������Լ�.
{
	PORTG = 0x05; // LCD�������;�����μ���
	PORTD = dw & 0xf0; // �����ͻ���4��Ʈ����	6,5,4, �ɿ� 101
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x05;
	PORTD = dw << 4; // ����������4��Ʈ����
	PORTG &= 0xfb;
	_delay_us(40);
}
void init_lcd(void) // LCD �ʱ�ȭ
{
	DDRD = 0xf0; //��ƮD ����4��Ʈ��������μ���
	DDRG = 0x07; //��ƮG ����3��Ʈ��������μ���
	
	lcd_iw(0x20);
	lcd_iw(0x28); // FUNCTION SET	2��
	lcd_iw(0x06); // ENTRY MODE 	��巹��+1
	lcd_iw(0x0c); // DISPLAY ON 	lcdŰ�� Ŀ������off
	lcd_iw(0x01); // ALL CLEAR
}

void lcd_str(S08 *str) // ���ڿ�����Լ�.
{
	U08 i;
	while(*str){		//while(null=0) �̶� ��ħ while(1)�� ���ѷ����� �ƴ϶� while(2,3,4~~~xxx)�� ���ѷ���
	lcd_dw(*str++);
	for(i=0; i<10; i++)
	_delay_ms(1); // �ð�����.
}
}

