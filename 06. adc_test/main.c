
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)

void Main_Init(void);
void Uart_Putch(unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);
unsigned int Read_ADC(unsigned char ADC_Input);



void main(void)
{
	Main_Init();

	while(1)
	{
		Uart_U16Bit_PutNum(Read_ADC(0b01000000));  //센서로 부터 받은 데이터를 컴퓨터로 송신
		_delay_ms(1000);
	}
}

void Main_Init(void)                        //전체 세팅 
{
//////////////////////////////////////////////UART 세팅

	cbi(SREG,7);           					//모든 인터럽트 비활성화
	UBRR0H = 0; UBRR0L = 16;				//57600bps(16MHz)
	UCSR0A = (0<<RXC0)|(1<<UDRE0);			//수신,송신 상태비트 초기
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);			//수신,송신 기능 활성화
	UCSR0C = (3<<UCSZ00);					//START  1비트 DATA8비트
	cbi(DDRE,0);							//RXD1핀 입력으로 설정
	sbi(DDRE,1);							//TXD1핀 출력으로 설정

	                   



//////////////////////////////////////////////ADC 세팅

	ADMUX = 0x00;							//ADC 초기화
	ADCSRA = 0x87;							//ADC Enable, 분주비=128
	cbi(DDRF,0);							//ADC0 핀 입력으로 설정
	sbi(SREG,7);							//모든 인터럽트 활성화
}



void Uart_Putch(unsigned char PutData)      //시리얼로부터 1바이트값을 보내는 함수
{
	while(!( UCSR0A & (1<<UDRE0)));         //데이터가 빌때까지 기다렷다가 데이터가차면 아웃
	UDR0 = PutData;							//데이터를 전송한다.
}										



void Uart_U16Bit_PutNum(unsigned int NumData)      //각 자리수를 10진수로 변형해서 출력
{
	unsigned int TempData;
	TempData = (NumData/10000);            // 10000 자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10000)/1000;      // 1000  자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%1000)/100;		   // 100   자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%100)/10;		   // 10    자리출력
	Uart_Putch( TempData+48 );
	TempData = ( NumData%10);			   // 1     자리출력
	Uart_Putch( TempData+48 );
}




unsigned int Read_ADC(unsigned char ADC_Input)		
{
	ADMUX = ADC_Input;					//사용자 설정 (ADC값 입력)
	ADCSRA |= 0x40;						//ADC START Conversion
	while( ( ADCSRA & 0x10) == 0) ;     //ADC interrupt flag check
	return ADC;							//ADC값 반환
}
