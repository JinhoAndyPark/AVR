#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

/////////////////////////////////////////////////////////////
void main_init(void);
void trig(void);
unsigned int pulseIn(unsigned char bit);
void Uart_Init(unsigned char com,unsigned long Uart_Baud);
unsigned char Uart_Getch(unsigned char Com);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);
////////////////////////////////////////////////////////////


ISR(TIMER0_OVF_vect)
{
	//cbi(PORTA,1);
	cbi(SREG,7);
	cbi(TIMSK,0);
	Uart_Putch(1,2);
}

int main(void)
{

	main_init();
	sbi(SREG,7);

	while(1)
	{                                   
		_delay_ms(1000);	
		cbi(PORTA,0);
		_delay_us(2);
		sbi(SREG,7);
		sbi(TIMSK,0);
	
		sbi(PORTA,0);
		TCNT0 = 176;
	
 //1초에 한번
		
		 Uart_Putch(1,1);
		// Uart_U16Bit_PutNum(  pulseIn(0x02));
	}
	
return 0;
}



void main_init(void)
{
	cbi(SREG,7);				//모든 인터럽트 비활성화
	Uart_Init(1,57600);
	Uart_Init(0,57600);
	
///////////////////아두이노 초음파
	sbi(DDRA,1);
	cbi(PORTA,1);	
	
//////////////////타이머 인터럽트
	sbi(TIMSK,0);
	TCCR0 = 0x01; //prescale 1
}


void trig(void)
{
	sbi(DDRA,1);	
	cbi(PORTA,1);
	_delay_us(2);
	sbi(SREG,7);
	sbi(TIMSK,0);
//	cbi(PORTA,1);
	//cbi(DDRA,1);// INPUT 설정

}

 


unsigned int pulseIn(unsigned char bit)
{
unsigned int width=0;
unsigned long timeout =1000000;
unsigned long numloops = 0;
// pin 이 1이라고 생각하자. PA1
unsigned long maxloops = timeout;

/*while ((*portInputRegister(port) & bit) == stateMask)
		if (numloops++ == maxloops)
			return 0;
	
	// wait for the pulse to start  when timing low to High!!! 
	while ((*portInputRegister(port) & bit) != stateMask)
		if (numloops++ == maxloops)
			return 0;
	
	// wait for the pulse to stop when High to low.....
	while ((*portInputRegister(port) & bit) == stateMask) {
		if (numloops++ == maxloops)
			return 0;
		width++;
	}
*/
	while ((PINA & bit) == bit) //다르다.....가..... 안달라지면 0 
		{if (numloops++ == maxloops)
			return 0;
		}

	// wait for the pulse to start  when timing low to High!!! 
	while ((PINA & bit) != bit)
		{if (numloops++ == maxloops)
			return 0;
		}

	// wait for the pulse to stop when High to low.....
	while ((PINA & bit) == bit) {
		if (numloops++ == maxloops)
			return 0;
		width++;
	}
	return width*21/16+1;

}
//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: Initial set what num & speed 
//------------------------------------------------------------------------------

void Uart_Init(unsigned char com,unsigned long Uart_Baud) 
{	
	unsigned long Temp_UBRR;
	Temp_UBRR = 16000000/(16L * Uart_Baud) - 1;
	
	
    //---------------------------- UART0 초기화 --------------------------------
	if( com==0 )                           	
	{
		           // 통신속도 설정
		UBRR0H =(Temp_UBRR >> 8);              // Baud set
		UBRR0L =(Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0) | (1<<UDRE0);  // nothing in recieve buffer & transmission buffer  
		UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  //recieve & transmission enable , recieve complete interrupt enable(수신완료 인터럽트 활성화)  
		UCSR0C = (3<<UCSZ00);		//8bit transfer 
		cbi(DDRE,0); 	//RXD input
		sbi(DDRE,1);	//TXD output
		
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	else if( com==1 )
	{
		              
		UBRR1H = (Temp_UBRR >> 8);              // Baud set
		UBRR1L = (Temp_UBRR & 0x00FF);

		
		  
		UCSR1A = (0<<RXC1) | (1<<UDRE1);	//nothing in recieve buffer & transmission buffer
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);	//recieve & transmission enable,recieve complete interrupt enable(수신완료 인터럽트 활성화)
		UCSR1C = (3<<UCSZ10);			//8bit transfer
		cbi(DDRD,2);  	//RXD input
		sbi(DDRD,3);	//TXD output
		
	}
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


void Uart_U16Bit_PutNum(unsigned int NumData)   // 10진수로 출력
{
	unsigned int TempData;
	
	TempData = NumData/1000;
	Uart_Putch(0,TempData+48);					// 1000 자리 출력
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100 자리 출력
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10 자리 출력
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1 자리 출력 
}
