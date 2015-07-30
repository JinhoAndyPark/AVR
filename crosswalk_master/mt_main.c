//------------------------------------------------------------------------------
//	=== Include Headerfile ===
//------------------------------------------------------------------------------
#include "main.h"		// 프로그램의 헤더파일 설정

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

#define	SIDE1CHK		1
#define	SIDE1UNCHK		0
#define	SIDE2CHK		1
#define SIDE2UNCHK		0
#define SIDE3CHK		1
#define SIDE3UNCHK		0
#define SIDE4CHK		1
#define SIDE4UNCHK		0

volatile unsigned char CheckFlag=0, NowSide=0;
volatile unsigned char Val_Side1, Val_Side2, Val_Side3, Val_Side4;
unsigned char ascii1[2],ascii2[2],ascii3[2],ascii4[2];
volatile unsigned char checkPKflag=0, arraynextstate;

volatile unsigned char count1S, count2S, count3S, count4S;
unsigned int count1sec = 0;

volatile unsigned int PSD_val_L, PSD_val_R;
unsigned char light_signal_flag=0;

unsigned char revARRAY[2];

unsigned char test;

unsigned char cntval1, cntval2, cntval3, cntval4;
unsigned char stval1, stval2, stval3, stval4;


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 131;

	count1sec++;

	if(count1sec >= 500)
	{
		count1sec = 0;

		if(Val_Side1 >= 30)
		{
			cntval1++;
			if(cntval1 > 10)	SendServer();
		}
		else
			cntval1 = 0;
			
		if(Val_Side2 >= 30)
		{
			cntval2++;
			if(cntval2 > 10)	SendServer();
		}
		if(Val_Side3 >= 30)
		{
			cntval3++;
			if(cntval3 > 10)	SendServer();
		}
		if(Val_Side4 >= 30)
		{
			cntval4++;
			if(cntval4 > 10)	SendServer();
		}
	}
}


ISR(USART0_RX_vect)
{
	unsigned char RXD;
	
	CLRBIT(SREG, 7); 

	RXD = UDR0;

	//test = RXD;

	if(CheckFlag == 1)
	{
		//CheckFlag = 0;
		NowSide = RXD;

		if(NowSide == '1')
		{
			checkPKflag = 1;
			CheckFlag = 0;
		}
		else if(NowSide == '2')
		{
			checkPKflag = 2;
			CheckFlag = 0;
		}
		else if(NowSide == '3')
		{
			checkPKflag = 3;
			CheckFlag = 0;
		}
		else if(NowSide == '4')
		{
			checkPKflag = 4;
			CheckFlag = 0;
		}
	}

	if(arraynextstate == 1)
	{
		if(checkPKflag == 1)
		{
			ascii1[0] = RXD;
			arraynextstate = 2;
		}
		else if(checkPKflag == 2)
		{
			ascii2[0] = RXD;
			arraynextstate = 2;
		}
		else if(checkPKflag == 3)
		{
			ascii3[0] = RXD;
			arraynextstate = 2;
		}
		else if(checkPKflag == 4)
		{
			ascii4[0] = RXD;
			arraynextstate = 2;
		}
		else {}
	}

	if(arraynextstate == 2)
	{
		if(checkPKflag == 1)
		{
			ascii1[1] = RXD;
			Val_Side1 = AsciiToChar(ascii1);
			arraynextstate = 0;
			checkPKflag = 0;
		}
		else if(checkPKflag == 2)
		{
			ascii1[1] = RXD;
			Val_Side2 = AsciiToChar(ascii2);
			arraynextstate = 0;
			checkPKflag = 0;
		}
		else if(checkPKflag == 3)
		{
			ascii1[1] = RXD;
			Val_Side3 = AsciiToChar(ascii3);
			arraynextstate = 0;
			checkPKflag = 0;
		}
		else if(checkPKflag == 4)
		{
			ascii1[1] = RXD;
			Val_Side4 = AsciiToChar(ascii4);
			arraynextstate = 0;
			checkPKflag = 0;
		}
		else {}
	}

	if((RXD=='@') && (CheckFlag==0))		CheckFlag = 1; 	//ready
	if((RXD=='=') && (checkPKflag>0))		arraynextstate = 1;		
	
	SETBIT(SREG, 7); 
}



void main(void)
{ 
	Init_Main();		// 초기화_MCU

	while(1)
	{
		PSD_val_L = ADC_Read(0);
		PSD_val_R = ADC_Read(1);

		SETBIT(PORTA,0);
		SETBIT(PORTA,3);
				
		CLRBIT(PORTA,1);
		_delay_ms(500);
		SETBIT(PORTA,1);
		_delay_ms(500);

	
		if((PSD_val_L >= 200) || (PSD_val_R >= 200))
		{
			light_signal_flag = 1;
		}

		if(light_signal_flag == 1)
		{
			CLRBIT(PORTA,0);
			SETBIT(PORTA,1);
			CLRBIT(PORTA,3);
			_delay_ms(5000);
			light_signal_flag = 0;
		}
				
		
	}
}


void Init_Main(void)
{
	CLRBIT(SREG, 7);           	// 전체인터럽트 사용금지

	Init_Timer0();				// 초기화_타이머0
    Init_Uart0();  				// 초기화_시리얼통신0 : for xbee
    Init_Uart1();				// 초기화_시리얼통신1 : for BT
	Init_ADC();					//  for PSD sensor

	SETBIT(DDRA, 0);				// light signal CAR_RED
	SETBIT(DDRA, 1);				// light signal CAR_YELLO
	SETBIT(DDRA, 2);				// light signal CAR_GREEN

	SETBIT(DDRA, 3);				// light signal HUM_GREEN
	SETBIT(DDRA, 4);

	SETBIT(PORTA, 0);				//init light : OFF
	SETBIT(PORTA, 1);				//init light : OFF
	SETBIT(PORTA, 2);				//init light : OFF
	SETBIT(PORTA, 3);				//init light : OFF
	SETBIT(PORTA, 4);				//init light : OFF
	

    
	SETBIT(SREG, 7);            	// 전체인터럽트 사용허가
}

void Init_Timer0(void)			// 타이머0 초기화
{
		                       
	SETBIT( TIMSK, TOIE0 );     	// 타이머0 오버플로어 ON
	TCNT0 = 131;					// 타이머0 상수 

	TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//분주비
}

void Init_Uart0(void)		//for xbee
{
	unsigned int Temp_UBRR0;
	Temp_UBRR0 = 16000000L/(16L * 9600) - 1;   	// 통신 보레이트 계산식

	UBRR0H = (Temp_UBRR0 >> 8);              // 통신속도 설정 9600
	UBRR0L = (Temp_UBRR0 & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
    UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  	// 수신,송신,인터럽트 기능 활성화
	UCSR0C = (3<<UCSZ00);				// START 1비트/DATA 8비트/STOP 1비트
		
	CLRBIT( DDRE, 0 );                         // RXD0 핀 입력으로 설정
	SETBIT( DDRE, 1 );                         // TXD0 핀 출력으로 설정		
}

void Init_Uart1(void)		//for bluetooth
{
	unsigned int Temp_UBRR1;
	Temp_UBRR1 = 16000000L/(16L * 9600) - 1;
	
	UBRR1H = (Temp_UBRR1 >> 8);              // 통신속도 설정
	UBRR1L = (Temp_UBRR1 & 0x00FF);

	UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// 수신,송신 상태비트 초기화
	UCSR1B = (1<<RXEN1) | (1<<TXEN1)| (1<<RXCIE1);    	// 수신,송신 기능 활성화
	UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트
	
	CLRBIT( DDRD, 2 );                         // RXD1 핀 입력으로 설정
	SETBIT( DDRD, 3 );                         // TXD1 핀 출력으로 설정	
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

void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x00;
	ADCSRA = 0x00;			   //레지스터 초기화 및 AREF단자로 입력전압 사용

	SETBIT( ADCSRA, ADPS0 );
	SETBIT( ADCSRA, ADPS1 );
	SETBIT( ADCSRA, ADPS2 );		//프리스케일러 128분주


	SETBIT( ADCSRA, ADEN );		   	// ADC 인에이블
	CLRBIT(ADCSR, ADFR);            // AD 컨버터 단일변환 모드
    SETBIT(ADCSR, ADSC);            // AD 컨버터 변환 시작
}

unsigned int ADC_Read(unsigned char Channel)
{
	unsigned int value = 0;

	ADMUX = Channel;
	
	SETBIT( ADCSRA, ADSC );		// ADC Conversion Start
	
	while( ADCSRA & ( 1 << ADSC ) ); 	// wait ADC conversion complete

	value = ADCL;
	value |= (unsigned int)ADCH << 8;
	
	return value;

}

void SendServer(void)
{
	unsigned char PacketData;
	
	PacketData = 0xFF;

	Uart_Putch(1, PacketData);
	
}

unsigned char AsciiToChar(unsigned char *AsciiArray)
{
	unsigned char BufArray[2];
	unsigned char Convert_val;

	BufArray[0] = AsciiArray[0];
	BufArray[1] = AsciiArray[1];

	BufArray[0] -= 48;
	BufArray[1] -= 48;

	Convert_val = BufArray[0]*10 + BufArray[1];

	return Convert_val;
}
