#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


SIGNAL(INT0_vect)//INT0����
{
	PORTC = 0xf0;//LEDON
}

SIGNAL(INT1_vect)//INT1����
{
	PORTC = 0x0f;//LEDON
}

int main(void)
{
	DDRC = 0xff;	//��¼���
	PORTC = 0xff;	//��ҿ� ������
	SREG |= 0x80;	//�۷ι����ͷ�Ʈ set
	GICR = 0xc0;	//���ͷ�Ʈ set
	MCUCR |= 0x00; //(1<<ISC01)|(0<<ISC00)|(1<<ISC10)|(0<<ISC11);	//low �����϶�


	while(1)
	{
	PORTC = 0xff;	//��ҿ��� �����´�.
	}

	return 0;
}




