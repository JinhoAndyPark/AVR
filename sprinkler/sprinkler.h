#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header

#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT
#define 	Disable_ISR()    cbi(SREG, 7)			// 인터럽트 사용금지
#define 	Enable_ISR()     sbi(SREG, 7)			// 인터럽트 사용허가

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
void Timer2_Init(void);
void Ext_Interrupt5_Init(void);
void Ext_Interrupt6_Init(void);
void Ext_Interrupt7_Init(void);

void ADC_Init(void);
unsigned int ADC_Read(unsigned char Channel);

void Init_Uart(unsigned int want_Baud);
void Uart_Putch(unsigned char PutData);
void SendRemote(void);