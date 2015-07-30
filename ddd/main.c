
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)
////// For CM-5
#define RS485_TXD PORTE &= ~(1<<PE3),PORTE |= (1<<PE2)  //PORT_485_DIRECTION = 1
#define RS485_RXD PORTE &= ~(1<<PE2),PORTE |= (1<<PE3)  //PORT_485_DIRECTION = 0


void Main_Init(void);
void Tx_Packet(float ANGLE3, signed long Speed3);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Motor_Init(void);

void main()
{
  Main_Init();
  
  while(1)
  {
    /**************************************************************************/
   	//Motor_Init();  // ID 부여 뒤에는 반드시 주석 처리 할것 
    /**************************************************************************/
    Tx_Packet(50,500) ;// 60// 60
    _delay_ms(2000);
    Tx_Packet(10,500);
    _delay_ms(2000);

  }
}



void Main_Init(void)
{	

	//cbi(SREG,7);						//모든 인터럽트 비활성화
	
UCSR1A=0x00;
UCSR1B=0x08;
UCSR1C=0x06;
UBRR1H=0x00;
UBRR1L=0x00;


 ;                   // START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 3 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 4 );                         // TXD1 핀 출력으로 설정

	//direction 
	sbi(DDRE,3);
	sbi(DDRE,4);
	sbi(PORTE,3);
	cbi(PORTE,4);		//tx 
	_delay_ms(500);
		 
}

//------------------------------------------------------------------------------
//     				===== Tx_Packet =====
//             		: MCU->Ax
//------------------------------------------------------------------------------

void Tx_Packet(float ANGLE3, signed long Speed3)  
{
  unsigned char i,TxData[11];

  ANGLE3 = ANGLE3*3.4 + 512;
  
  // 1.Packet Transfer Start signal
  TxData[0] = 0xff;
  TxData[1] = 0xff;  
  // 2.Dynamixel ID
  TxData[2] = 0;
  // 3.Parameter Length
  TxData[3] = 0x07;
  // 4.Write instruction
  TxData[4] = 0x03;
  // 5.Write Address
  TxData[5] = 0x1e;
  // 6.parameter
  TxData[6] = (unsigned char)((unsigned long )ANGLE3 & 0xff); //위치 Data의 Low값 저장
  TxData[7] = (unsigned char)((unsigned long )ANGLE3 >> 8); //위치 Data의 High값 저장
  TxData[8] = (unsigned char)((unsigned long )Speed3 & 0xff); //속도 Data의 Low값 저장
  TxData[9] = (unsigned char)((unsigned long )Speed3 >> 8); //속도 Data의 High값 저장

  TxData[10] = 0x00;
  for(i=2;i<10;i++)
  {
    TxData[10] += TxData[i];
  }
  TxData[10] = ~TxData[10];

  for(i=0 ; i<11 ; i++)
	{
		UCSR1A |=(1<<TXC1)	;	//clear TXC(USART Trasmit Complete)
		Uart_Putch(1,TxData[i]); //send TxData to AX 
		
	}
  	_delay_us(5000);
				
}


void Motor_Init(void)  
{  
  unsigned char i, TxData[8];
  TxData[0] = 0xff;                         
  TxData[1] = 0xff;   
  
  TxData[2] = 0xfe;
  TxData[3] = 0x04;                            
  TxData[4] = 0x03;         
  TxData[5] = 0x03;
  TxData[6] = 0x00;  //0번으로 부여    
  TxData[7] = 0x00;                            
  
  for(i = 2 ; i < 7 ; i++) 
  {
    TxData[7] += TxData[i];
  }     
  
  TxData[7] = ~TxData[7];

  	for(i=0 ; i<8; i++)
	{
		UCSR1A |=(1<<TXC1)	;	//clear TXC(USART Trasmit Complete)
		Uart_Putch(1,TxData[i]); //send TxData to AX 
		
	}
	_delay_us(5000);

  	
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
