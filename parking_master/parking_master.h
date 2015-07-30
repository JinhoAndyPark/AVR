#include <avr/io.h>			//ATmega128 I/O Header
#include <avr/interrupt.h>		//ATmega128 INTERRUPT Header
#include <util/delay.h>			//ATmega128 delay Function Header


#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT

#define 	Disable_ISR()    cbi(SREG, 7)			// 인터럽트 사용금지
#define 	Enable_ISR()     sbi(SREG, 7)			// 인터럽트 사용허가

typedef   signed  char    S08;
typedef unsigned  char    U08;
typedef   signed   int    S16;
typedef unsigned   int    U16;


void Init_Main(void);
void Init_Timer0(void);
void Init_Uart(void);
void Init_RecieveSlave(void);
void Send_Computer(void);

