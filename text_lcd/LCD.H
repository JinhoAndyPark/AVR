// ĳ����LCD ��Ʈ������(4��Ʈ���)

#ifndef __LCD_H

#include <avr/io.h>
#include <util/delay.h>



void lcd_iw(U08 inst); // LCD ��������Լ�.
void lcd_dw(U08 dw); // LCD ����������Լ�.
void init_lcd(void); // LCD �ʱ�ȭ
void lcd_str(S08 *str) // ���ڿ�����Լ�.

#endif