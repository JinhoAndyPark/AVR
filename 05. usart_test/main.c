
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
		                       				
		Uart_Putch(0, Uart_Getch(0)); //키보드로부터 데이터를 수신 한걸 송신
	}
}

void main_init(void)
{
	cbi(SREG,7);				//모든 인터럽트 비활성화
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
			while(!( UCSR0A & (1<<UDRE0)) );    // 송신가능시점까지 대기
			UDR0 = PutData;                     // 데이터를 전송한다
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // 송신가능시점까지 대기
			UDR1 = PutData;                     // 데이터를 전송한다
			break;
	}
}

unsigned char Uart_Getch(unsigned char Com)
{
	switch( Com )
	{
		case 0:
			while(!( UCSR0A & (1<<RXC0)) );    // 수신완료까지 대기
			return UDR0;                       // 수신데이터 
		
		case 1:
			while(!( UCSR1A & (1<<RXC1)) );    // 수신완료까지 대기
			return UDR1;                       // 순신데이터 반환
		
        default:
			return 0;
	}
}
	

