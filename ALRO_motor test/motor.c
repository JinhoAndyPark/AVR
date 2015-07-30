
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)


/////////////////////////////////////////////////////////////
void main_init(void);
void Uart_Putch(unsigned char Com, unsigned char PutData);
unsigned char Uart_Getch(unsigned char Com);
void TIMER(void);           
////////////////////////////////////////////////////////////


int count=32;


int main(void)
{


	main_init();


	while(1)
	{                                    //Ű����κ��� �����͸� ����

		

		switch(Uart_Getch(1))
		{
		
	
		case 'A':
		
		OCR1C=700;
		count=45;
		_delay_ms(1000);
		Uart_Putch(1, 'A');
		Uart_Putch(1, count);
		_delay_ms(1000);
		sbi(PORTB,0);   cbi(PORTB,1);//���� dc��
		sbi(PORTB,3);   cbi(PORTB,2);//������ dc��
		break;
		
		
		case 'B':
		count=count+5;
		OCR1C=400;
		_delay_ms(1000);
		Uart_Putch(1, 'B');
		Uart_Putch(1, count);
		_delay_ms(1000);
		sbi(PORTB,1);   cbi(PORTB,0);// dc ��
		sbi(PORTB,2);   cbi(PORTB,3);

		break;
	
		case 'C':
		count=100;

		OCR1C=count;

		Uart_Putch(1, 'C');
		Uart_Putch(1, count);
		_delay_ms(1000);
		cbi(PORTB,1);   cbi(PORTB,0);// dc����
		cbi(PORTB,2);   cbi(PORTB,3);
		break;

	



		}


	}
	return 0;
}

void main_init(void)
{
	cbi(SREG,7);				//��� ���ͷ�Ʈ ��Ȱ��ȭ
	UBRR1H = 0; UBRR1L = 16;   //57600bps(16MHZ)
	UCSR1A = (0<<RXC1) | (1<<UDRE1);
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UCSR1C = (3<<UCSZ10);
	
	//bluetooth �̿� Ȱ��ȭ
	UBRR0H = 0; UBRR0L = 103;   //9600bps(16MHZ)
	UCSR0A = (0<<RXC0) | (1<<UDRE0);
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
	
	cbi(DDRE,0); 
	sbi(DDRE,1);
	sbi(SREG,7);


	cbi(DDRD,2);  
	sbi(DDRD,3);
	
 	DDRB=0xff;
	PORTB=(1<<PORTB5)|(1<<PORTB6);// Enable dc motor
	
	TCCR1A = 0x0A;  // OC1C��Ʈ�� ��弳��   
	TCCR1B = 0x1C;  // mode14(fast pwm),���ֺ�256 = 16us  
	ICR1 = 1249;    //ICR1��(OVERFLOW��) 16us*1250 = 20ms servo���� �ֱ⼳�� 
	OCR1C = 70;    // ���� 70:1250
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



