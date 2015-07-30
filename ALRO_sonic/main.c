
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SET_BIT(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define CLR_BIT(PORTX , BitX)   PORTX &= ~(1 << BitX)


//------------------------------------------------------------------------------
//                   		=== Function Declaration ===
//------------------------------------------------------------------------------
void Init_Main(void);
void Init_Timer0(void);
void Init_Uart0(void);
void Init_Uart1(void);
void Uart_Putch(unsigned char  Com, unsigned int PutData);
void Init_Ext_Interrupt5(void);
void Init_Ext_Interrupt7(void);
void Uart_U16Bit_PutNum(unsigned int Numdata);

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

volatile unsigned  int Sonic_val = 0, Sonic_cm = 0;


//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

ISR(TIMER0_OVF_vect)	// Sonic Trigger Pulse
{
	
		
	SET_BIT(PORTG,0),SET_BIT(PORTG,1);   //오른쪽센서 트리거,왼쪽센서 트리거
	_delay_us(10);
	CLR_BIT(PORTG,0),CLR_BIT(PORTG,1); 
	
	TCNT0 = 0; 
	
}

ISR(INT5_vect)           //오른쪽 센서 에코 
{	

	if(EICRB == 0x0c)		    //오른쪽만 RISING  이면 (왼쪽도 RISING이면 DISABLE 이라두 영향을미침)
	{
		
		TCNT0 = 0;			//카운트 초기화
		EICRB=0x08; 		//오른쪽만 FALLING 세팅
		
	}
	else if(EICRB == 0x08)    //오른쪽 FALLING  ,왼쪽 RISING  이면 
	{
		
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt		
		Sonic_cm = (((Sonic_val * 64) * 34300)/2000000) +1;			//초음파 거리측정
		Uart_U16Bit_PutNum(Sonic_cm);

		_delay_ms(1000);
		
		EICRB=0xc0;    // 왼쪽만RISING, 오른쪽은이용x 

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024 타이머 시작 
		TCNT0 = 56;                                                 //256-56=200   64us*200=약12.8ms
		
		CLR_BIT( EIMSK, INT5  );    // EXT_INT 4 DISABLE 
		SET_BIT( EIMSK, INT7  );    // EXT_INT 5 ENABLE
	}
}

ISR(INT7_vect)
{	
	if(EICRB==0xc0)		    //왼쪽만 RISING EDGE 이면 
	{	
		TCNT0 = 0;		//카운트 초기화
		//Uart_Putch(1,7);
		EICRB=0x80;   // 왼쪽 FALLING SET 
		
	}
	
	else if(EICRB==0x80)    //왼쪽만 FALLING
	{
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt

		Sonic_cm = (((Sonic_val * 64) * 34300)/2000000) +1;			//초음파 거리측정
		Uart_U16Bit_PutNum(Sonic_cm);

		_delay_ms(1000);

		EICRB=0x0c;    // 오른쪽만 FALLING

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024
		TCNT0 = 56;                                                 //256-56=200   64us*200=약12.8ms 

		SET_BIT( EIMSK, INT5  );    // EXT_INT 4 ENABLE 
		CLR_BIT( EIMSK, INT7  );    // EXT_INT 5 DISABLE
	}
}

void main(void)
{ 
	Init_Main();		// init_device
	
	while(1)
	{		
	
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	CLR_BIT(SREG, 7);           	// 전체인터럽트 사용금지

	Init_Timer0();				// 초기화_타이머2
    Init_Uart0();  				// 초기화_시리얼통신0
    Init_Uart1();				// 초기화_시리얼통신1 
    Init_Ext_Interrupt5();		// INT4 신호 인터럽트(오른쪽센서)
	Init_Ext_Interrupt7();		// INT5 신호 인터럽트(왼쪽센서)

	SET_BIT(DDRG, 0);			// 오른쪽센서 트리거출력설정
	SET_BIT(DDRG, 1);			// 왼쪽센서 트리거 출력설정
	
	SET_BIT(SREG, 7);            //  전체 인터럽트 활성화 
}


void Init_Timer0(void)   
{   
	SET_BIT( TIMSK, TOIE0 );     //timer0 overflow interrupt able
	TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//분주비 1024 = 64us	
	TCNT0 = 56;					 // 256-56=200   64us*200=약12.8ms	
}


void Init_Uart0(void)		//ALRO UART0=bluetooth
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


void Init_Uart1(void)		//ALRO UART1=computer
{
	unsigned   int Temp_UBRR1;
	Temp_UBRR1 = 16000000L/(16L * 9600) - 1;  //(UBRR값 구하기공식) UBRR=약103
		
	UBRR1H = (Temp_UBRR1 >> 8);  	//0       
	UBRR1L = (Temp_UBRR1 & 0x00FF); //103  9600bps

	UCSR1A = (0<<RXC1)  | (1<<UDRE1);  //수신버퍼 비워진상태, 송신버퍼 비워진상태
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);  //수신부 동작,송신부 동작 활성화
	UCSR1C = (3<<UCSZ10);  			   //전송데이터 비트수 8비트            
	
	CLR_BIT( DDRD, 2 );  //수신부 입력으로
	SET_BIT( DDRD, 3 );  //송신부 출력으로 
	
}


void Uart_Putch(unsigned char  Com, unsigned int PutData)
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


void Uart_U16Bit_PutNum(unsigned int NumData)   // 10진수로 출력
{
	unsigned int TempData;
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);                  // 10000 자리 출력
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000 자리 출력
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100 자리 출력
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10 자리 출력
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1 자리 출력 
}


void Init_Ext_Interrupt5(void)  				//오른쪽 센서 인터럽트 
{
	SET_BIT( EICRB, ISC51 );    // INT4 RISING EDGE ENABLE
	SET_BIT( EICRB, ISC50 );    // INT4 RISING EDGE ENABLE
	
	SET_BIT( EIMSK, INT5  );    // EXT_INT 4 ENABLE
	CLR_BIT( EIFR, INTF5 );     // INTERRUPT FLAG CLEAR	
	CLR_BIT( DDRE, 5 );  	    // 신호 받아들임
	//SET_BIT( PORTE, 4 );		// Input Set, Pull-Up Setting?????????
}

void Init_Ext_Interrupt7(void)
{
	CLR_BIT( EICRB, ISC71 );    // 
	CLR_BIT( EICRB, ISC70 );    //레지스터 00  
	
	CLR_BIT( EIMSK, INT7  );    // EXT_INT 5 DISABLE
	CLR_BIT( EIFR , INTF7 );    // INTERRUPT FLAG CLEAR
	CLR_BIT( DDRE, 7);			// 신호 받아들임   
	//SET_BIT( PORTE, 5);			// Input Set, Pull-Up Setting?????????
}

