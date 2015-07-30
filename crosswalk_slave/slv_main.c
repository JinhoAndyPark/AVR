//------------------------------------------------------------------------------
//	=== Include Headerfile ===
//------------------------------------------------------------------------------
#include "main.h"		// 프로그램의 헤더파일 설정

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

volatile unsigned  char Sonic_val = 0, Sonic_cm = 0;
unsigned int count1sec = 0;
//unsigned char chkcnt=0;

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

ISR(TIMER2_OVF_vect)	// Sonic Trigger Pulse
{
	TCNT2 = 0;
	SET_BIT(PORTG,3);
	_delay_us(10);
	CLR_BIT(PORTG,3);
}

ISR(INT0_vect)
{
	TCCR2 = 0x00;			//off timer cnt
	Sonic_val = TCNT2;		//check cnt
	Sonic_cm = (((Sonic_val * 64) * 34300)/2000000) +1;		//초음파 거리측정

	TCCR2 = ( 1 << CS20 ) | ( 0 << CS21 ) | ( 1 << CS22 );		//freescale : 1024
}

ISR(INT1_vect)		//init cnt(tcnt2)
{
	TCNT2 = 0;
}

void main(void)
{ 
	Init_Main();		// init_device
	
	while(1)
	{
		//Uart_Putch(0, 0x01);
		//if(chkcnt >= 10)
		//if(Sonic_cm < 15)
		//{
			Uart_Putch(0, Sonic_cm);	//xbee
		//	chkcnt = 0;
		//}
		//Uart_Putch(0, Sonic_cm);

		//_delay_ms(200);
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	CLR_BIT(SREG, 7);           	// 전체인터럽트 사용금지

	Init_Timer2();				// 초기화_타이머2
    Init_Uart0();  				// 초기화_시리얼통신0
    Init_Uart1();				// 초기화_시리얼통신1 deb
    Init_Ext_Interrupt0();
	Init_Ext_Interrupt1();

	SET_BIT(DDRG, 3);
	SET_BIT(DDRB, 3);
    
	SET_BIT(SREG, 7);          
}

void Init_Timer2(void)   
{   
	SET_BIT( TIMSK, TOIE2 );     
	TCNT2 = 55;				
		
	TCCR2 = ( 1 << CS20 ) | ( 0 << CS21 ) | ( 1 << CS22 );			
}

void Init_Uart0(void)
{
	unsigned   int Temp_UBRR0;
	Temp_UBRR0 = 16000000L/(16L * 9600) - 1;   

	UBRR0H = (Temp_UBRR0 >> 8);        
	UBRR0L = (Temp_UBRR0 & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);	
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		
	UCSR0C = (3<<UCSZ00);			
		
	CLR_BIT( DDRE, 0 );        
	SET_BIT( DDRE, 1 );          
		
}

void Init_Uart1(void)
{
	unsigned   int Temp_UBRR1;
	Temp_UBRR1 = 16000000L/(16L * 9600) - 1; 
	
	UBRR1H = (Temp_UBRR1 >> 8);        
	UBRR1L = (Temp_UBRR1 & 0x00FF);

	UCSR1A = (0<<RXC1)  | (1<<UDRE1); 
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);  
	UCSR1C = (3<<UCSZ10);              
	
	CLR_BIT( DDRD, 2 );  
	SET_BIT( DDRD, 3 ); 
	
}

void Uart_Putch(unsigned char  Com, unsigned char PutData)
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

void Init_Ext_Interrupt0(void)
{
	SET_BIT( EICRA, ISC01 );    // FALLING EDGE ENABLE
	CLR_BIT( EICRA, ISC00 );    // FALLING EDGE ENABLE
	SET_BIT( EIMSK, INT0  );    // EXT_INT 0 ENABLE
	CLR_BIT( EIFR , INTF0 );    // INTERRUPT FLAG CLEAR
	CLR_BIT(DDRD, 0);  
	SET_BIT(PORTD, 0);		// Input Set, Pull-Up Setting
}

void Init_Ext_Interrupt1(void)
{
	SET_BIT( EICRA, ISC11 );    // RISING EDGE ENABLE
	SET_BIT( EICRA, ISC10 );    // RISING EDGE ENABLE
	SET_BIT( EIMSK, INT1  );    // EXT_INT 1 ENABLE
	CLR_BIT( EIFR , INTF1 );    // INTERRUPT FLAG CLEAR
	CLR_BIT(DDRD, 1);  
	SET_BIT(PORTD, 1);		// Input Set, Pull-Up Setting
}
