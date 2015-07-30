
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
	{                                    //키보드로부터 데이터를 수신

		

		switch(Uart_Getch(1))
		{
		
	
		case 'A':
		
		OCR1C=700;
		count=45;
		_delay_ms(1000);
		Uart_Putch(1, 'A');
		Uart_Putch(1, count);
		_delay_ms(1000);
		sbi(PORTB,0);   cbi(PORTB,1);//왼쪽 dc정
		sbi(PORTB,3);   cbi(PORTB,2);//오른쪽 dc정
		break;
		
		
		case 'B':
		count=count+5;
		OCR1C=400;
		_delay_ms(1000);
		Uart_Putch(1, 'B');
		Uart_Putch(1, count);
		_delay_ms(1000);
		sbi(PORTB,1);   cbi(PORTB,0);// dc 역
		sbi(PORTB,2);   cbi(PORTB,3);

		break;
	
		case 'C':
		count=100;

		OCR1C=count;

		Uart_Putch(1, 'C');
		Uart_Putch(1, count);
		_delay_ms(1000);
		cbi(PORTB,1);   cbi(PORTB,0);// dc중지
		cbi(PORTB,2);   cbi(PORTB,3);
		break;

	



		}


	}
	return 0;
}

void main_init(void)
{
	cbi(SREG,7);				//모든 인터럽트 비활성화
	UBRR1H = 0; UBRR1L = 16;   //57600bps(16MHZ)
	UCSR1A = (0<<RXC1) | (1<<UDRE1);
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UCSR1C = (3<<UCSZ10);
	
	//bluetooth 이용 활성화
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
	
	TCCR1A = 0x0A;  // OC1C포트에 모드설정   
	TCCR1B = 0x1C;  // mode14(fast pwm),분주비256 = 16us  
	ICR1 = 1249;    //ICR1값(OVERFLOW값) 16us*1250 = 20ms servo모터 주기설정 
	OCR1C = 70;    // 비율 70:1250
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



