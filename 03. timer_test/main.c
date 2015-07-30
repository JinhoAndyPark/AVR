#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX,BitX) PORTX |= (1<<BitX) //��Ʈ SET ��� ����
#define cbi(PORTX,BitX) PORTX &= ~(1<<BitX) //��Ʈ CLEAR ��� ����

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
	
	PORTC = 0xff;   //��ƮA�� �ʱ�ȭ
	DDRC = 0xff;	//��ƮA ������� ����
	TCCR0 = 0x0f;  	//ctc mode,1024���� ����(clkt=16000000/1024=15625Hz)
	TCNT0 = 1;
	OCR0 = 0xff ;   // 125  1/clkt0= 64us, 64us*125=8ms
	TIMSK = 0x02;   // compare interrupt enable
	sbi(SREG,7);    // all interrupt enable
}
