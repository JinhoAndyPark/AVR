// 캐릭터LCD 포트제어방식(4비트모드)

#ifndef __LCD_H

#include <avr/io.h>
#include <util/delay.h>



void lcd_iw(U08 inst); // LCD 명령출력함수.
void lcd_dw(U08 dw); // LCD 데이터출력함수.
void init_lcd(void); // LCD 초기화
void lcd_str(S08 *str) // 문자열출력함수.

#endif
