#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

 
#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   // 비트 SET 명령 정의
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)   // 비트 CLEAR 명령 정의
 
void Main_Init(void);           // 초기화 함수 선언

int main(void)
{      
    Main_Init();
		
    while(1)
    {
	PORTB=0x40;
	PORTB=0x20;
		/*
        OCR1A=0;        _delay_ms(1500); // 0%듀티비
        OCR1A=250;       _delay_ms(1500); // 25%듀티비
        OCR1A=500;      _delay_ms(1500); // 50%듀티비
        OCR1A=750;      _delay_ms(1500); // 75%듀티비
        OCR1A=1000;      _delay_ms(1500); // 100%듀티비
		
        OCR1B=0;        _delay_ms(1500); // 0%듀티비
        OCR1B=250;       _delay_ms(1500); // 25%듀티비
        OCR1B=500;      _delay_ms(1500); // 50%듀티비
        OCR1B=750;      _delay_ms(1500); // 75%듀티비
        OCR1B=1000;      _delay_ms(1500); // 100%듀티비
    */
	}
return 0;
}
void Main_Init(void)
{
    cbi(SREG,7);        // 모든 인터럽트 비활성화

    DDRB    = 0xff;     // 포트B 출력으로 설정
    //TCCR1A  = 0xA2;     // 1010 0010 모드 14, 1,0 비교매치0출력 오버플로우1출력
	//TCCR1B  = 0x1d;		// 0001 1101 (clkt=16000000/1024=15625Hz ) 64us
    //ICR1 = 1000;		// top 설정
	//TCNT1=0;

//	sbi(SREG,7);         
			          
    
       /* TIMSK   = 0x03;     // COMP 인터럽트 인에이블
    sbi(SREG,7);      */  // 모든 인터럽트 인에이블
}
 
