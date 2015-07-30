
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
//캐릭터LCD 포트제어방식(4비트모드)
#include <avr/io.h>
#include <util/delay.h>
#include "../Define.h"
#include "Lcd.h"

//extern U08 *str1="<Welcome to 3D>";
//extern U08 *str2="<YYYY>";

void lcd_iw(U08 inst) // LCD 명령출력함수.
{
	PORTG = 0x04; // LCD를명령쓰기모드로설정
	PORTD = inst & 0xf0; // 명령어상위4비트전송
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x04;
	PORTD = inst << 4; // 명령어하위4비트전송
	PORTG &= 0xfb; // LCD Disable
	_delay_ms(2);
}
void lcd_dw(U08 dw) // LCD 데이터출력함수.
{
	PORTG = 0x05; // LCD를데이터쓰기모드로설정
	PORTD = dw & 0xf0; // 데이터상위4비트전송	6,5,4, 핀에 101
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x05;
	PORTD = dw << 4; // 데이터하위4비트전송
	PORTG &= 0xfb;
	_delay_us(40);
}
void init_lcd(void) // LCD 초기화
{
	DDRD = 0xf0; //포트D 상위4비트를출력으로설정
	DDRG = 0x07; //포트G 하위3비트를출력으로설정
	
	lcd_iw(0x20);
	lcd_iw(0x28); // FUNCTION SET	2행
	lcd_iw(0x06); // ENTRY MODE 	어드레드+1
	lcd_iw(0x0c); // DISPLAY ON 	lcd키고 커서점멸off
	lcd_iw(0x01); // ALL CLEAR
}

void lcd_str(S08 *str) // 문자열출력함수.
{
	U08 i;
	while(*str){		//while(null=0) 이라서 멈침 while(1)만 무한루프가 아니라 while(2,3,4~~~xxx)도 무한루프
	lcd_dw(*str++);
	for(i=0; i<10; i++)
	_delay_ms(1); // 시간지연.
}
}

