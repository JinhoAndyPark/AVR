//------------------------------------------------------------------------------
//	=== Include Headerfile ===
//------------------------------------------------------------------------------
#include "main.h"		// ���α׷��� ������� ����


#define	MODEREADY	0
#define MODERUN		1

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

U08 ID,TxPacketLength, RxPacketLength;
extern volatile U08 RxInterruptBuffer[256];
extern U08 RxBufferReadPointer;
extern U08 RxBufferWritePointer;

U16 tic_1sec = 0;
U08 nSEC, nMIN, nHOR;
U08 nMODE;

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)	//2ms
{
	TCNT0 = 131;
	tic_1sec++;
	if(tic_1sec >= 500)
	{
		
	}
	
}

ISR(USART0_RX_vect)
{	
	Disable_ISR();

	RxInterruptBuffer[(RxBufferWritePointer++)]= UDR0;

	Enable_ISR();
}



//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// �ʱ�ȭ_MCU
	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
	if(ADC_Average(0, 10) >= 200)
	{
		//nMODE = MODERUN;
		AX_Action(0, 0x02, 0x00, 0x02, 0x90);
		_delay_ms(300);
		AX_Action(0, 0x02, 0x90, 0x02, 0x90);
		_delay_ms(300);
		
	}
			
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������

	Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(0,1000000);  		// �ʱ�ȭ_�ø������0
	Init_Uart(1,57600);  	// �ʱ�ȭ_�ø������1
	Init_ADC();
	//Lcd_Init();
	//sbi(DDRE,4);
    
	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------