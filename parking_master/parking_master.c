#include "parking_master.h"		// 프로그램의 헤더파일 설정

#define REVPORT		PORTC
#define REVPIN		PINC
#define USER1BIT	0
#define USER2BIT	1
#define USER3BIT	2

U16 tic_1sec = 0;
U08 state1_flag=0, state2_flag=0, state3_flag=0;
U08 user1_flag=0, user2_flag=0, user3_flag=0;

volatile U08 nSEC1, nMIN1, nHOR1;
volatile U08 nSEC2, nMIN2, nHOR2;
volatile U08 nSEC3, nMIN3, nHOR3;

U16 cost1=1000, cost2=1000, cost3=1000;


ISR(TIMER0_OVF_vect)	// 2ms
{
	TCNT0 = 131;
	tic_1sec++;

	if( tic_1sec >= 500 )		//sec
	{
		tic_1sec = 0;

		if(state1_flag == 1)
		{
			nSEC1++;
			if(nSEC1 >= 60)
			{
				nMIN1++;
				nSEC1 = 0;

				if(nMIN1 >= 60)
				{
					nHOR1++;
					nMIN1 = 0;					
				}
			}
		}

		if(state2_flag == 1)
		{
			nSEC2++;
			if(nSEC2 >= 60)
			{
				nMIN2++;
				nSEC2 = 0;

				if(nMIN2 >= 60)
				{
					nHOR2++;
					nMIN2 = 0;					
				}
			}
		}

		if(state3_flag == 1)
		{
			nSEC3++;
			if(nSEC3 >= 60)
			{
				nMIN3++;
				nSEC3 = 0;

				if(nMIN3 >= 60)
				{
					nHOR3++;
					nMIN3 = 0;					
				}
			}
		}

		
	}
}

ISR(INT0_vect)		//INTERRUPT FALLING EDGE FOR STATE1
{
	state1_flag = 0;

	nHOR1 = 0;
	nMIN1 = 0;
	nSEC1 = 0;
	//process calc cost and init state
}

ISR(INT1_vect)		//INTERRUPT RISING EDGE FOR STATE1
{
	state1_flag = 1;
}

ISR(INT2_vect)		//INTERRUPT FALLING EDGE FOR STATE2
{
	state2_flag = 0;
	
	nHOR2 = 0;
	nMIN2 = 0;
	nSEC2 = 0;
}

ISR(INT3_vect)		//INTERRUPT RISING EDGE FOR STATE2
{
	state2_flag = 1;
}

ISR(INT4_vect)		//INTERRUPT FALLING EDGE FOR STATE3
{
	state3_flag = 0;
	
	nHOR3 = 0;
	nMIN3 = 0;
	nSEC3 = 0;
}

ISR(INT5_vect)		//INTERRUPT RISING EDGE FOR STATE3
{
	state3_flag = 1;
}

int main(void)
{
	Init_Main();
	
	while(1)
	{
		Send_Computer();
		_delay_ms(300);
	}

	return 0;
}

void Init_Main(void)
{
	Init_Timer0();
	Init_RecieveSlave();
	Init_Uart();

	DDRC = 0xFF;
	PORTC = 0xFF;
}

void Init_RecieveSlave(void)
{
	Disable_ISR();
	
	DDRC = 0x00;	//setting recievePORT
	/*-----------
	PORTC.0	--- slave_1st_userstate
	PORTC.1 --- slave_2nd_userstate
	PORTC.2 --- slave_3th_userstate
	-----------*/

	sbi( EICRA, ISC01 );    // FALLING EDGE FOR STATE1
	cbi( EICRA, ISC00 );
	sbi( EIMSK, INT0  );    // EXT_INT 0 ENABLE
	cbi( EIFR , INTF0 );    // INTERRUPT FLAG CLEAR
	cbi(DDRD, 0);  
	sbi(PORTD, 0);

	sbi( EICRA, ISC11 );    // RISING EDGE FOR STATE1
	sbi( EICRA, ISC10 );
	sbi( EIMSK, INT1  );    // EXT_INT 1 ENABLE
	cbi( EIFR , INTF1 );    // INTERRUPT FLAG CLEAR
	cbi(DDRD, 1);  
	sbi(PORTD, 1);

	sbi( EICRA, ISC21 );    // FALLING EDGE FOR STATE2
	cbi( EICRA, ISC20 );
	sbi( EIMSK, INT2  );    // EXT_INT 2 ENABLE
	cbi( EIFR , INTF2 );    // INTERRUPT FLAG CLEAR
	cbi(DDRD, 2);  
	sbi(PORTD, 2);
	
    
	sbi( EICRA, ISC31 );    // RISING EDGE FOR STATE2
	sbi( EICRA, ISC30 );
	sbi( EIMSK, INT3  );    // EXT_INT 3 ENABLE
	cbi( EIFR , INTF3 );    // INTERRUPT FLAG CLEAR
	cbi(DDRD, 3);  
	sbi(PORTD, 3);

	sbi( EICRB, ISC41 );    // FALLING EDGE FOR STATE3
	cbi( EICRB, ISC40 );
	sbi( EIMSK, INT4  );    // EXT_INT 4 ENABLE
	cbi( EIFR , INTF4 );    // INTERRUPT FLAG CLEAR
	cbi(DDRE, 4);  
	sbi(PORTE, 4);
  	
	sbi( EICRB, ISC51 );    // RISING EDGE FOR STATE3
	sbi( EICRB, ISC50 );
	sbi( EIMSK, INT5  );    // EXT_INT 5 ENABLE
	cbi( EIFR , INTF5 );    // INTERRUPT FLAG CLEAR
	cbi(DDRE, 5);  
	sbi(PORTE, 5);

	Enable_ISR();
}

void Init_Timer0(void)			// 타이머0 초기화
{                
	sbi( TIMSK, TOIE0 );     	// 타이머0 오버플로어 ON
	TCNT0 = 131;					// 타이머0 상수 
		
	TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );				// prescaler 설정
}

void Init_Uart(void)	//컴퓨터 통신
{
	U16 Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * 9600) - 1; 
	
	UBRR0H = (Temp_UBRR >> 8);              // 통신속도 설정
	UBRR0L = (Temp_UBRR & 0x00FF);
	
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		// 수신,송신 기능 활성화
	UCSR0C = (3<<UCSZ00);					// START 1비트/DATA 8비트/STOP 1비트
		
	cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
	sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
}

void Uart_Putch(U08 PutData)
{
	while(!( UCSR0A & (1<<UDRE0)) );		// 송신가능시점까지 대기
	UDR0 = PutData;							// 데이터를 전송한다
}

void Send_Computer(void)
{
	U08 Parameter[8];

	Parameter[0] = 0xF0;
	Parameter[1] = nHOR1;
	Parameter[2] = nMIN1;
	Parameter[3] = nHOR2;
	Parameter[4] = nMIN2;
	Parameter[5] = nHOR3;
	Parameter[6] = nMIN3;
	Parameter[7] = 0x0F;

	U08 cnt;

	for(cnt=0; cnt<8; cnt++)
	{
		Uart_Putch(Parameter[cnt]);
	}
}