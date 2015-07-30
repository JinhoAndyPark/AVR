#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>	

#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)
#define 	Disable_ISR()    cbi(SREG, 7)
#define 	Enable_ISR()     sbi(SREG, 7)

void Init_main(void);

void Lcd_Init(void);
void Command(unsigned char byte);
void Data(unsigned char byte);
void Put_Lcd_Char(char Lcd_Data);
void Put_Lcd_String( char *Lcd_Data);
void Display_Position(unsigned char line, unsigned char col);
void Lcd_Put_Char_Xy(unsigned char line, unsigned char col, unsigned char Lcd_Data);
void Lcd_Print_Xy(unsigned char line, unsigned char col, char *Lcd_Data);
void Lcd_Print_Num(unsigned char line, unsigned char col, unsigned char data);
void Lcd_Print_U16digit(unsigned char line, unsigned char col, unsigned int data);

void Timer0_Init(void);

void Init_Uart(unsigned int want_Baud);
void Uart_Putch(unsigned char PutData);

void KEYSCAN(void);