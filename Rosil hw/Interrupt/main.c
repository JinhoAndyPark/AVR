#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


SIGNAL(INT0_vect)//INT0구문
{
	PORTC = 0xf0;//LEDON
}

SIGNAL(INT1_vect)//INT1구문
{
	PORTC = 0x0f;//LEDON
}

int main(void)
{
	DDRC = 0xff;	//출력설정
	PORTC = 0xff;	//평소에 꺼놓기
	SREG |= 0x80;	//글로벌인터럽트 set
	GICR = 0xc0;	//인터럽트 set
	MCUCR |= 0x00; //(1<<ISC01)|(0<<ISC00)|(1<<ISC10)|(0<<ISC11);	//low 상태일때


	while(1)
	{
	PORTC = 0xff;	//평소에는 꺼놓는다.
	}

	return 0;
}




