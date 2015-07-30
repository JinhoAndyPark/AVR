#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header


#define 	SETBIT(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	CLRBIT(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT


void Init_Main(void);
void Init_Timer0(void);
void Init_Timer2(void);
void Init_Uart0(void);
void Init_Uart1(void);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned char Com, unsigned int NumData);
void Init_Ext_Interrupt0(void);
void Init_Ext_Interrupt1(void);
void Init_ADC(void);
unsigned int ADC_Read(unsigned char Channel);
void SendServer(void);
unsigned char AsciiToChar(unsigned char* AsciiArray);