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
typedef   signed  long    S32;
typedef unsigned  long    U32;

U16 ADC_Read(U08 Channel);
U16 ADC_Average(U08 Channel, U08 number);
void Init_Uart(U08 Com, U32 Uart_Baud);
void Uart_Putch(U08 Com, U08 Data);
U08 TxPacket(U08 ID, U08 Instruction, U08 ParameterLength);
void DX_Action(U08 ID, U08 Position_H, U08 Position_L, U08 Speed_H, U08 Speed_L);
void DX_Angle_Action(int id, double angle);
void Init_ADC(void);
