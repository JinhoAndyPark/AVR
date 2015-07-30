
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

void main_init(void);
void Uart_Putch(unsigned char Com, unsigned char PutData);
unsigned char Uart_Getch(unsigned char Com);


void main(void)
{
	main_init();
	while(1)
	{             
		                       				
		Uart_Putch(0, Uart_Getch(0)); //Ű����κ��� �����͸� ���� �Ѱ� �۽�
	}
}

void main_init(void)
{
	cbi(SREG,7);				//��� ���ͷ�Ʈ ��Ȱ��ȭ
	UBRR0H = 0; UBRR0L = 16;   //57600bps(16MHZ)
	UCSR0A = (0<<RXC0) | (1<<UDRE0);
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
	cbi(DDRE,0); 
	sbi(DDRE,1);
	sbi(SREG,7);

	
	

}

void Uart_Putch(unsigned char Com, unsigned char PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // �۽Ű��ɽ������� ���
			UDR0 = PutData;                     // �����͸� �����Ѵ�
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // �۽Ű��ɽ������� ���
			UDR1 = PutData;                     // �����͸� �����Ѵ�
			break;
	}
}

unsigned char Uart_Getch(unsigned char Com)
{
	switch( Com )
	{
		case 0:
			while(!( UCSR0A & (1<<RXC0)) );    // ���ſϷ���� ���
			return UDR0;                       // ���ŵ����� 
		
		case 1:
			while(!( UCSR1A & (1<<RXC1)) );    // ���ſϷ���� ���
			return UDR1;                       // ���ŵ����� ��ȯ
		
        default:
			return 0;
	}
}
	

