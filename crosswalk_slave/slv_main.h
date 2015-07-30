;
#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header


#define 	SET_BIT(PORT , Bit)   PORT |=  (1 << Bit)	// SET   BIT
#define 	CLR_BIT(PORT , Bit)   PORT &= ~(1 << Bit)	// CLEAR BIT

#define 	Disable_ISR()    cbi(SREG, 7)			// 인터럽트 사용금지
#define 	Enable_ISR()     sbi(SREG, 7)			// 인터럽트 사용허가

void Init_Main(void);
void Init_Timer0(void);
void Init_Timer2(void);
void Init_Uart0(void);
void Init_Uart1(void);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Init_Ext_Interrupt0(void);
void Init_Ext_Interrupt1(void);
