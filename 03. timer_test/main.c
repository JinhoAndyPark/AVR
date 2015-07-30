#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX,BitX) PORTX |= (1<<BitX) //비트 SET 명령 정의
#define cbi(PORTX,BitX) PORTX &= ~(1<<BitX) //비트 CLEAR 명령 정의

unsigned char count=0;


ISR(TIMER0_COMP_vect)
{	
	count++;
	
	if(count==125)
	{
		if(PORTC==0x00)
		PORTC=0xff;
		else if(PORTC==0xff)
		PORTC=0;
		count=0;
	}
	TCNT0=125;              //

}
	
void main_init(void);

int main(void)
{
	main_init();
	while(1);
}

void main_init(void)
{
	
	PORTC = 0xff;   //포트A값 초기화
	DDRC = 0xff;	//포트A 출력으로 설정
	TCCR0 = 0x0f;  	//ctc mode,1024분주 설정(clkt=16000000/1024=15625Hz)
	TCNT0 = 1;
	OCR0 = 0xff ;   // 125  1/clkt0= 64us, 64us*125=8ms
	TIMSK = 0x02;   // compare interrupt enable
	sbi(SREG,7);    // all interrupt enable
}
