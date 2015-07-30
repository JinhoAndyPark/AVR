#include "main.h"

U08 Parameter[128];						// �Ű�����
U08 RxBuffer[128]; 						// ���Ź���
U08 TxBuffer[128]; 						// �۽Ź���
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
	DX_Action(2, 0x02, 0x30, 0x01, 0x44); // ���͸� �ʱⰪ���� �̵���Ų��.
	_delay_ms(3000); 
	
	while(1)
	{
		Sensor_Reading();
		_delay_ms(1000); // ���� ������

		if(sensingNullFlag)
		{
			DX_Action(1, 0x02, 0x00, 0x00, 0x44);
			DX_Action(2, 0x02, 0x30, 0x00, 0x44); // ���͸� �ʱⰪ���� �̵���Ų��.
			continue;
		}
		
		horizontal = (int)((top_sensing - down_sensing) * sensing_weight)/3; 	
		vertical = (int)((right_sensing- left_sensing) * sensing_weight )/3; 	
		// sensor �� ���̸� Ȯ���Ͽ� �̵��ؾ��� ������ ����		
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

	Temp_UBRR = 16000000L/(16L * Uart_Baud) - 1;   	// ��� ������Ʈ ����
													// U2X = 0 �϶� (�Ϲݸ��)
	if( Com == 0 )                           	
	{
		UBRR0H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR0L = (Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// ����,�۽� ���º�Ʈ �ʱ�ȭ
        UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  		// ����,�۽� ��� Ȱ��ȭ
		UCSR0C = (3<<UCSZ00);				// START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRE, 0 );                         // RXD0 �� �Է����� ����
		sbi( DDRE, 1 );                         // TXD0 �� ������� ����
	}
	
	if( Com == 1)
	{
		UBRR1H = (Temp_UBRR >> 8);              // ��żӵ� ����
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 	// ����,�۽� ���º�Ʈ �ʱ�ȭ
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);    	// ����,�۽� ��� Ȱ��ȭ
		UCSR1C = (3<<UCSZ10);                   // START 1��Ʈ/DATA 8��Ʈ/STOP 1��Ʈ
		
		cbi( DDRD, 2 );                         // RXD1 �� �Է����� ����
		sbi( DDRD, 3 );                         // TXD1 �� ������� ����
	}
}

void Uart_U10Bit_PutNum(U08 Com, U16 NumData)
{
	U16 TempData;

	TempData =  NumData/1000;
	Uart_Putch(Com, TempData+48);			// 1000 �ڸ� ������ ���
	
	TempData = (NumData%1000)/100;
	Uart_Putch(Com, TempData+48);			// 100  �ڸ� ������ ���
	
	TempData = (NumData%100)/10;
	Uart_Putch(Com, TempData+48);      		// 10   �ڸ� ������ ���
	
	TempData =  NumData%10;
	Uart_Putch(Com, TempData+48);      		// 1    �ڸ� ������ ���
}


void Uart_Putch(U08 Com, U08 Data)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // �۽Ű��ɽ������� ���
			UDR0 = Data;                     // �����͸� �����Ѵ�
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // �۽Ű��ɽ������� ���
			UDR1 = Data;                     // �����͸� �����Ѵ�
			break;
	}
}

U08 TxPacket(U08 ID, U08 Instruction, U08 ParameterLength)
{
    //--------------------------------------------------------------------------
    //		===== ��Ŷ ���� =====
    //--------------------------------------------------------------------------

    U08 Count;					// ��Ŷ�� ���� ��ȣ
    U08 CheckSum;				// ��Ŷ�� ���� ���� ���
    U08 PacketLength;			// �Ű��������� �� ����
	
	TxBuffer[0] = 0xFF;						// Start CODE
	TxBuffer[1] = 0xFF;						// Start CODE
	TxBuffer[2] = ID;						// ����ID (0~253), BroadcastingID=0xFE
	TxBuffer[3] = ParameterLength + 2;		// Length(Instruction + ParamterLength + Checksum)
	TxBuffer[4] = Instruction;				// ��ɾ� ����(���Ͼ���,���߾���,�б� ��)
	
	for(Count = 0; Count < ParameterLength; Count++)
	{
		TxBuffer[Count+5] = Parameter[Count];			// �Ű����� ����
	}
	
    CheckSum = 0;										// CheckSum �ʱ�ȭ
	PacketLength = ParameterLength + 4 + 2;				// ��Ŷ�� ��ü ���� ����
	
	for(Count = 2; Count < PacketLength-1; Count++)  	// Except 0xFF, Checksum
	{
		CheckSum += TxBuffer[Count];
	}
	
	TxBuffer[Count] = ~CheckSum;                       	// Checksum ����


	sbi(PORTE, 3);                                         	// RS485 ��¸��� ����
	
    for(Count = 0; Count < PacketLength; Count++)
	{
		sbi(UCSR0A, 6);						     		// �۽ſϷ� ���·� ��ȯ
		Uart_Putch( 0, TxBuffer[Count] );         	// ������ ��Ŷ���� MCU->DX
	}
	
	while(!(UCSR0A & (1<<TXC0)));                         	// �۽Ź��� �������� ��ٸ�
	cbi(PORTE, 3);                                          	// RS485 �Է¸��� ����
	
	return(PacketLength);								// ��Ŷ�� ��ü���� ����
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
	DDRF = 0x00; 			   //ADC��Ʈ �Է� ����

	ADMUX = 0x00;
	ADCSRA = 0x00;			   //�������� �ʱ�ȭ �� AREF���ڷ� �Է����� ���

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//���������Ϸ� 128����


	sbi( ADCSRA, ADEN );		   	// ADC �ο��̺�
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

