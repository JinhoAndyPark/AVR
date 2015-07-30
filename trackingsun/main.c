#include "main.h"

U08 Parameter[128];						// 매개변수
U08 RxBuffer[128]; 						// 수신버퍼
U08 TxBuffer[128]; 						// 송신버퍼
U08 ID, TxPacketLength, RxPacketLength;

volatile U16 left_sensing;
volatile U16 right_sensing;
volatile U16 top_sensing;
volatile U16 down_sensing;
volatile U16 sensing_weight = 1; // ex

volatile U16 horizontalAngle = 150;
volatile U16 verticalAngle = 150;

volatile U16 preHozizontal = 0;
volatile U16 preVertical = 0;

volatile U16 sensingNullFlag = 0;

volatile U16 horizontal = 0;
volatile U16 vertical = 0;

void Init_Main(void)
{
	Init_Uart(0, 1000000);
	Init_Uart(1, 57600);
	Init_ADC() ;
	
	sbi(DDRE, 3);
	sbi(DDRA, 0);
	sbi(PORTA, 0) ; 
}

int main(void)
{
	Init_Main();

			//Left(up : 150++ down : 150--)
	//////////////////
	//Down			//Top(up : 150++ down : 150--)
	//				//
	//////////////////
			//Right
	_delay_ms(1000); 
	DX_Action(1, 0x02, 0x00, 0x01, 0x44);
	DX_Action(2, 0x02, 0x30, 0x01, 0x44); // 모터를 초기값으로 이동시킨다.
	_delay_ms(3000); 
	
	while(1)
	{
		Sensor_Reading();
		_delay_ms(1000); // 센싱 딜레이

		if(sensingNullFlag)
		{
			DX_Action(1, 0x02, 0x00, 0x00, 0x44);
			DX_Action(2, 0x02, 0x30, 0x00, 0x44); // 모터를 초기값으로 이동시킨다.
			continue;
		}
		
		horizontal = (int)((top_sensing - down_sensing) * sensing_weight)/3; 	
		vertical = (int)((right_sensing- left_sensing) * sensing_weight )/3; 	
		// sensor 값 차이를 확인하여 이동해야할 정도를 결정		
		/*
		Uart_U10Bit_PutNum(1,horizontal);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,horizontal * -1);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,vertical);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,vertical * -1);
	Uart_Putch(1,'\r');
	Uart_Putch(1,'\n');
*/

		DX_Angle_Action(2,horizontalAngle - horizontal);
		DX_Angle_Action(1,verticalAngle - vertical);

		preHozizontal = horizontal;
		preVertical = vertical;
	}
	return 0;	
}
int abs(int a,int b)
{
	if(a > b) return a - b;
	if(b > a) return b - a;
}
void DX_Angle_Action(int id, double angle)
{
	///3ff,000
	//1023 ,0
	if(angle < 100) angle = 100;
	if(angle > 200) angle = 200;

	int temp = (int)(1023.0 * angle / 300.0);
	int high = temp/256;
	int low = temp % 256;
	
	DX_Action(id, high, low, 0x00, 0x44); 
	if(id == 2) horizontalAngle = angle;
	if(id == 1) verticalAngle = angle;
	//Uart_U10Bit_PutNum(1,low);
}

void Sensor_Reading()
{
	top_sensing = ADC_Average(0,50);//ADC_Read(0);
	down_sensing = ADC_Average(2,50);//ADC_Read(2);
	right_sensing = ADC_Average(3,50);//ADC_Read(3);
	left_sensing = ADC_Average(1,50);//ADC_Read(1);
/*
	Uart_U10Bit_PutNum(1,top_sensing);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,down_sensing);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,right_sensing);
	Uart_Putch(1,' ');
	Uart_U10Bit_PutNum(1,left_sensing);
	Uart_Putch(1,'\r');
	Uart_Putch(1,'\n');
*/
	if(top_sensing<200&&down_sensing<200&&right_sensing<200&&left_sensing<200)
	{
		cbi(PORTA,0);
		sensingNullFlag = 1;
	}
	else 
	{
		sbi(PORTA,0);
		sensingNullFlag = 0;
	}
}


void Init_Uart(U08 Com, U32 Uart_Baud)
{
	U16 Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * Uart_Baud) - 1;   	// 통신 보레이트 계산식
													// U2X = 0 일때 (일반모드)
	if( Com == 0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
        UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  		// 수신,송신 기능 활성화
		UCSR0C = (3<<UCSZ00);				// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
		sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
	}
	
	if( Com == 1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// 수신,송신 상태비트 초기화
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);    	// 수신,송신 기능 활성화
		UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 2 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 3 );                         // TXD1 핀 출력으로 설정
	}
}

void Uart_U10Bit_PutNum(U08 Com, U16 NumData)
{
	U16 TempData;

	TempData =  NumData/1000;
	Uart_Putch(Com, TempData+48);			// 1000 자리 무조건 출력
	
	TempData = (NumData%1000)/100;
	Uart_Putch(Com, TempData+48);			// 100  자리 무조건 출력
	
	TempData = (NumData%100)/10;
	Uart_Putch(Com, TempData+48);      		// 10   자리 무조건 출력
	
	TempData =  NumData%10;
	Uart_Putch(Com, TempData+48);      		// 1    자리 무조건 출력
}


void Uart_Putch(U08 Com, U08 Data)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // 송신가능시점까지 대기
			UDR0 = Data;                     // 데이터를 전송한다
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // 송신가능시점까지 대기
			UDR1 = Data;                     // 데이터를 전송한다
			break;
	}
}

U08 TxPacket(U08 ID, U08 Instruction, U08 ParameterLength)
{
    //--------------------------------------------------------------------------
    //		===== 패킷 생성 =====
    //--------------------------------------------------------------------------

    U08 Count;					// 패킷의 전송 번호
    U08 CheckSum;				// 패킷의 오류 검출 방법
    U08 PacketLength;			// 매개변수들의 총 갯수
	
	TxBuffer[0] = 0xFF;						// Start CODE
	TxBuffer[1] = 0xFF;						// Start CODE
	TxBuffer[2] = ID;						// 모터ID (0~253), BroadcastingID=0xFE
	TxBuffer[3] = ParameterLength + 2;		// Length(Instruction + ParamterLength + Checksum)
	TxBuffer[4] = Instruction;				// 명령어 선택(단일쓰기,다중쓰기,읽기 등)
	
	for(Count = 0; Count < ParameterLength; Count++)
	{
		TxBuffer[Count+5] = Parameter[Count];			// 매개변수 지정
	}
	
    CheckSum = 0;										// CheckSum 초기화
	PacketLength = ParameterLength + 4 + 2;				// 패킷의 전체 길이 설정
	
	for(Count = 2; Count < PacketLength-1; Count++)  	// Except 0xFF, Checksum
	{
		CheckSum += TxBuffer[Count];
	}
	
	TxBuffer[Count] = ~CheckSum;                       	// Checksum 생성


	sbi(PORTE, 3);                                         	// RS485 출력모드로 설정
	
    for(Count = 0; Count < PacketLength; Count++)
	{
		sbi(UCSR0A, 6);						     		// 송신완료 상태로 전환
		Uart_Putch( 0, TxBuffer[Count] );         	// 순차적 패킷전송 MCU->DX
	}
	
	while(!(UCSR0A & (1<<TXC0)));                         	// 송신버퍼 빌때까지 기다림
	cbi(PORTE, 3);                                          	// RS485 입력모드로 설정
	
	return(PacketLength);								// 패킷의 전체길이 리턴
}

void DX_Action(U08 ID, U08 Position_H, U08 Position_L, U08 Speed_H, U08 Speed_L)
{
	Parameter[0] = 30;						//goal position address : 30
	Parameter[1] = Position_L;				//Low 8bit at goal position
	Parameter[2] = Position_H;				//High 8bit at goal position
	Parameter[3] = Speed_L;				//Low 8bit at moving speed 
	Parameter[4] = Speed_H;				//High 8bit at moving speed
	TxPacketLength = TxPacket(ID, 0x03, 5);
}


void Init_ADC(void)
{
	DDRF = 0x00; 			   //ADC포트 입력 설정

	ADMUX = 0x00;
	ADCSRA = 0x00;			   //레지스터 초기화 및 AREF단자로 입력전압 사용

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 128분주


	sbi( ADCSRA, ADEN );		   	// ADC 인에이블
	ADMUX = 1;
}

U16 ADC_Read(U08 Channel)
{
	U16 value = 0;

	ADMUX = Channel;
	
	sbi( ADCSRA, ADSC );		// ADC Conversion Start
	
	while( ADCSRA & ( 1 << ADSC ) ); 	// wait ADC conversion complete

	value = ADCL;
	value |= (U16)ADCH << 8;
	
	return value;
}

U16 ADC_Average(U08 Channel, U08 number)		//Average ADC
{
	U16 value = 0;
	U16 temp[number];

	for(U08 cnt=0; cnt<number; cnt++)
	{
		temp[cnt] = ADC_Read(Channel);
		value += temp[cnt];
	}
	value /= number;
	
	return value;
}

