#include <avr/io.h>
#include <avr/interrupt.h>
#include "main.h"		// 프로그램의 헤더파일 설정

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

U08 ID,TxPacketLength, RxPacketLength;
extern U8 RxBufferReadPointer;
extern U8 Parameter[128];
extern U8 RxBuffer[128];
extern U8 TxBuffer[128];
extern U8 RxBufferWritePointer;
extern volatile U8 RxInterruptBuffer[256];

U08 count=0, count_1s=0;
U16 ADC_Value = 0;
U08 Moveflag=0;

ISR(TIMER0_OVF_vect)	//8ms
{
	TCNT0 = 131;
	count++;

	ADC_Value = Read_ADC(0);
	if(ADC_Value >=80)
	{
		Moveflag=1;
	}
	else
		Moveflag=0;
	//Uart_Print(1, "\n");
	//Uart_U16Bit_PutNum(1, Read_ADC(0) );
	if(count==50)
	{
		count =0;
		//Uart_Print(1, "\n");
		//Uart_U16Bit_PutNum(1, Read_ADC(0) );
		count_1s++;
	}

}

ISR(USART0_RX_vect)
{
	RxInterruptBuffer[(RxBufferWritePointer++)]= RXD0_DATA;
}
//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// 초기화_MCU


	RS485_RXD;
	RxBufferReadPointer = RxBufferWritePointer = 0;

	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
		Uart_Print(1, "\n");
		Uart_U16Bit_PutNum(1, ADC_Value );
		_delay_ms(200);

/*
		if ( Moveflag==1)
		{
			//Uart_Print(1, "if OK!\n");
			AX_Action(0, 0x02, 0x00, 0x02, 0x90);
			_delay_ms(300);
			AX_Action(0, 0x02, 0x90, 0x02, 0x90);
		    _delay_ms(300);
		}
*/
    //--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	
	Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(UART0,1000000);  	// 초기화_시리얼통신0
	Init_Uart(UART1,57600);  	// 초기화_시리얼통신1
	Init_Sensor_ADC();			// 초기화_ADC
	
	cbi(SFIOR,2);
	sbi(DDRE,2);
	sbi(DDRE,3);
	
	cbi(PORTE,2);
	sbi(PORTE,3);
    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
