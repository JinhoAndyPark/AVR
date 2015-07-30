
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)
////// For CM-5
#define RS485_TXD PORTE &= ~(1<<PE3),PORTE |= (1<<PE2)  //PORT_485_DIRECTION = 1
#define RS485_RXD PORTE &= ~(1<<PE2),PORTE |= (1<<PE3)  //PORT_485_DIRECTION = 0
#define INST_READ           0x02
#define INST_WRITE          0x03
#define INST_RESET          0x06
#define INST_SYNC_WRITE     0x83
////////////////////////////////////////////////////////////////////////////



void Main_Init(void);
unsigned char TxPacket(unsigned char ID,unsigned char Instruction,unsigned char ParameterLength);
void ID_Setting(unsigned char bID, unsigned char cID);
void Baud_Setting(unsigned char ID, unsigned char BAUD);
void PS_Setting(unsigned char ID,unsigned char Position_H,unsigned char Position_L,unsigned char Speed_H,unsigned char Speed_L);
void S_Settting(unsigned char ID,unsigned char Speed_H,unsigned char Speed_L); 
void Endless_Turn(unsigned char ID);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Uart_Init(unsigned char com,unsigned long Uart_Baud);
void Reset(unsigned char ID);
//////////////////////////////////////////////////////////////////////////
unsigned char ID,TxPacketLength,Count;
unsigned char Parameter[128], RxBuffer[128],TxBuffer[128];


//------------------------------------------------------------------------------
//     				===== RX ISR =====
//             		: AX->MCU
//------------------------------------------------------------------------------

ISR(USART1_RX_vect)
{	
	Uart_Putch(0,1);
	/*
	RxBuffer[Count]=UDR1;

	UCSR0A |=(1<<TXC0);       //SET_TXD0_FINISH;
        	 Uart_Putch(0,(RxBuffer[Count]));
	Count++;
	
	
	if(6==Count)
	{
	
	/*
		for(Count = 0; Count < 7; Count++)
		{
         	UCSR0A |=(1<<TXC0);       //SET_TXD0_FINISH;
        	 Uart_Putch(0,(RxBuffer[Count]));
     	}
	 _delay_us(160);
     while(!(UCSR0A & (1<<TXC0))); //Wait until TXD Shift register empty
	
	 Count=0;
	}
	
	*/	
		
}
		




//------------------------------------------------------------------------------
//     				===== Main =====
//------------------------------------------------------------------------------
void main()
{
  Main_Init();
  
  while(1)
  {
   Reset(0);
   //	Uart_Putch(0,'A');
  //  Endless_Turn(0);
  //  _delay_ms(1000);
	PS_Setting(1,1,200,0x02,0xff); 
	RxBuffer[Count]=
	
	if(6==Count)
	{
	
	
	if(6==Count)
	{
	
	
	if(6==Count)
	{
	
	
	if(6==Count)
	{
	
	
	
	if(6==Count)
	{
	
   
    _delay_ms(1000);
//	PS_Setting(1,0,100,0x02,0xff);
//	_delay_ms(1500);
//	PS_Setting(1,0,150,0x02,0xff);
//	_delay_ms(1500);
//	PS_Setting(1,0,200,0x02,0xff);
//	_delay_ms(1500);
//	PS_Setting(1,0,250,0x02,0xff);
//	_delay_ms(1500);
  }
}

//------------------------------------------------------------------------------
//     				===== Main_Init =====
//             		: SETTING
//------------------------------------------------------------------------------
void Main_Init(void)
{	
	
	sbi(DDRE,2); 
	sbi(DDRE,3);                ////RS485_TXD,RS485_RXD enable
	
	cbi(SREG,7);						//모든 인터럽트 비활성화
	Uart_Init(0,115200);
	Uart_Init(1,1000000);
		
	sbi(SREG,7);	 
}

//------------------------------------------------------------------------------
//     				===== Tx_Packet =====
//             		: MCU->Ax
//------------------------------------------------------------------------------

unsigned char TxPacket(unsigned char ID,unsigned char Instruction,unsigned char ParameterLength)
{
     unsigned char Count,CheckSum;

     TxBuffer[0] = 0xff;
     TxBuffer[1] = 0xff;
     TxBuffer[2] = ID;
     TxBuffer[3] = ParameterLength+2;
     TxBuffer[4] = Instruction;
     for( Count = 0; Count < ParameterLength ;+ Count++ )
     {
          TxBuffer[Count+5] = Parameter[Count];
     }
     CheckSum = 0;

     TxPacketLength = ParameterLength +4+2;



     for( Count = 2; Count < TxPacketLength-1; Count++ ) //except 0xff,checksum
     {
         CheckSum += TxBuffer[Count];
     }
     TxBuffer[Count] = ~CheckSum;

     RS485_TXD;


     for(Count = 0; Count < TxPacketLength; Count++)
     {
         UCSR1A |=(1<<TXC1);       //SET_TXD0_FINISH;
         Uart_Putch(1,(TxBuffer[Count]));
     }
	 _delay_us(5000);
     while(!(UCSR1A & (1<<TXC1))); //Wait until TXD Shift register empty
     _delay_us(70);
      Uart_Putch(0,'c');
     
     RS485_RXD;
	 Uart_Putch(0,'D');
     return(TxPacketLength); //packetlength return
}
//------------------------------------------------------------------------------
//     				===== ID_Setting =====
//             		: Motor ID Change
//------------------------------------------------------------------------------
void ID_Setting(unsigned char bID, unsigned char cID)     //ID change
{
    Parameter[0]= 0x03;  //ID Address 
    Parameter[1] = cID;  // Changed ID
    TxPacketLength = TxPacket(bID,INST_WRITE,2);      // before ID
}
//------------------------------------------------------------------------------
//     				===== Baud_Setting =====
//             		: Motor Baud Change
//------------------------------------------------------------------------------
void Baud_Setting(unsigned char ID, unsigned char BAUD)   //BAUD change
{
    Parameter[0] = 0x04;     //BAUD Address
    Parameter[1] = BAUD;     // Changed BAUD
    TxPacketLength = TxPacket(ID,INST_WRITE,2);      // before BAUD
}
//------------------------------------------------------------------------------
//     				===== position & speed set =====
//             		: Motor Baud Change  position: 0 ~ 0x1ff ~ 0x3ff speed: max=0x3ff 1=min 0=depends on Volt
//------------------------------------------------------------------------------
void PS_Setting(unsigned char ID,unsigned char Position_H,unsigned char Position_L,unsigned char Speed_H,unsigned char Speed_L) // Position, Speed Setting
{
    Parameter[0] = 0x1e;   //GOAL_POSITION Address
    Parameter[1] = Position_L;          //Writing Data P_GP_GOAL_POSITION_HOAL_POSITION_L
    Parameter[2] = Position_H;          //Writing Data
    Parameter[3] = Speed_L;             //Writing Data P_GOAL_SPEED_L
    Parameter[4] = Speed_H;             //Writing Data P_GOAL_SPEED_H
    TxPacketLength = TxPacket(ID,INST_WRITE,5);
}
//------------------------------------------------------------------------------
//     				===== Speed_Set =====
//             		: only speed setting , 10bit: cw direction:1 ccw direction:0
//------------------------------------------------------------------------------
void S_Settting(unsigned char ID,unsigned char Speed_H,unsigned char Speed_L)
{
	Parameter[0] = 0x20;		//Speed Set
	Parameter[0] = Speed_L;	//Writing Data speed_L
	Parameter[0] = Speed_H;	//Writing Data speed_H
	TxPacketLength = TxPacket(ID,INST_WRITE,3);
}
//------------------------------------------------------------------------------
//     				===== Endless_Turn =====
//             		: ALSO Have to set speed
//------------------------------------------------------------------------------
void Endless_Turn(unsigned char ID)       // Endless_Turn Setting
{
	 Parameter[0] = 0x06;     //CW Angle Limit
     Parameter[1] = 0x00;     //CW Angle Limit_L
     Parameter[2] = 0x00;     //CW Angle Limit_H
     Parameter[3] = 0x00;     //CCW Angle Limit_L
     Parameter[4] = 0x00;     //CCW Angle Limit_H
     TxPacketLength = TxPacket(ID,INST_WRITE,5);
}
void Reset(unsigned char ID)
{	
	TxPacketLength = TxPacket(ID,INST_RESET,0);
}
//------------------------------------------------------------------------------
//     				===== Uart_Putch =====
//------------------------------------------------------------------------------
void Uart_Putch(unsigned char Com, unsigned char PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // 송신가능시점까지 대기
			UDR0 = PutData;                     // 데이터를 전송한다
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );	// 송신가능시점까지 대기
			UDR1 = PutData;                     // 데이터를 전송한다
			break;
	}
}



//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: 희망하는 속도로 시리얼 통신을 초기화 한다.
//------------------------------------------------------------------------------

void Uart_Init(unsigned char com,unsigned long Uart_Baud) 
{	
	unsigned long Temp_UBRR;
	Temp_UBRR = 16000000/(16L * Uart_Baud) - 1;
	
	
    //---------------------------- UART0 초기화 --------------------------------
	if( com==0 )                           	
	{
		           // 통신속도 설정
		UBRR0H =(Temp_UBRR >> 8);              // 통신속도 설정
		UBRR0L =(Temp_UBRR & 0x00FF);

		UCSR0A = (0<<RXC0)  | (1<<UDRE0);		// 수신,송신 상태비트 초기화
        UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);  		// 수신,송신 기능 활성화
		UCSR0C = (3<<UCSZ00);					// START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRE, 0 );                         // RXD0 핀 입력으로 설정
		sbi( DDRE, 1 );                         // TXD0 핀 출력으로 설정
		
		
		sbi(UCSR0B, RXCIE0);              	// 수신인터럽트0 활성화
		
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	else if( com==1 )
	{
		              // 통신속도 설정
		UBRR1H = (Temp_UBRR >> 8);              // 통신속도 설정
		UBRR1L = (Temp_UBRR & 0x00FF);

		UCSR1A = (0<<RXC1)  | (1<<UDRE1); 		// 수신,송신 상태비트 초기화
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) ;//(1<<RXCIE1);    	// 수신,송신 기능 활성화
		UCSR1C = (3<<UCSZ10);                   // START 1비트/DATA 8비트/STOP 1비트
		
		cbi( DDRD, 2 );                         // RXD1 핀 입력으로 설정
		sbi( DDRD, 3 );                         // TXD1 핀 출력으로 설정
		
		
		//sbi(UCSR1B, RXCIE1);              	// 수신인터럽트1 활성화
		
	}
}
