#include "main.h"

#define	MODEREADY	0
#define MODERUN		1
#define MODEEND		2

#define mFLAGSTART	0
#define mFLAGEND	1

#define NOMALUSER	0
#define UNNOMALUSER	1


U16 tic_1sec = 0;
U08 nSEC, nMIN, nHOR;
volatile U08 nMODE=0;
volatile U08 rFLAG=0, sFLAG=0;

volatile U08 RFIDdata, RFIDcard_val, STBIT, Read_ID=0;
U08 USER=0;
U16 Cal_Cost=500;


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 131;
	tic_1sec++;
	if(tic_1sec >= 500)
	{
		tic_1sec = 0;
		if((nMODE == MODERUN)&&(sFLAG == 1))		//(sFLAG ==1) for delay_time
		{
			nSEC++;
			if(nSEC >= 60)
			{
				nMIN++;
				nSEC = 0;

				if(nMIN >= 60)
				{
					nHOR++;
					nMIN = 0;					
				}
			}
		}
	}
}// 타이머 인터럽트.. 주차를 하고서 얼마나 시간이 경과한지 연산

ISR(USART1_RX_vect)
{
	Disable_ISR();
	
	RFIDdata = UDR1;
	Read_RFID_card();

	Enable_ISR();
}


int main(void)
{ 
	Init_Main();		// 초기화_MCU
	//Lcd_Print_Xy( 1, 0, "test2           ");
	AX_Action(0, 0x03, 0x35, 0x02, 0x90);
	
	while(1)
	{
		//Lcd_Print_Xy( 1, 0, "test3           ");

		if(nMODE == MODEREADY)
		{
			if(ADC_Average(0, 10) >= 200)			// PSD센싱 시 모드 실행, 일정 거리에 차가 들어오면 실행
			{
				nMODE = MODERUN;
				//AX_Action(0, 0x01, 0xFF, 0x02, 0x90);

				//sbi(PORTE,4);
			}
			else									
			{
				nMODE = MODEREADY;
				//AX_Action(0, 0x03, 0x35, 0x02, 0x90);
				//cbi(PORTE,4);
			}
		}

		if((Read_ID != 0x00)&&(nMODE == MODERUN))
		{
			nMODE = MODEEND;
			cbi(PORTB,0);
		}

		if(nMODE == MODERUN)
		{
			rFLAG = 0;
			
			if(sFLAG ==1)
			{
				Lcd_Print_2Digit(1,4, nHOR);
				Lcd_Print_2Digit(1,7, nMIN);
				Lcd_Print_2Digit(1,10,nSEC);  
			}
			else
			{
				_delay_ms(4000);		//start delay 2sec
				Lcd_Print_Xy( 0, 0, "      TIME      ");
				Lcd_Print_Xy( 1, 0, "      :  :      ");
				AX_Action(0, 0x01, 0xFF, 0x02, 0x90);
				sbi(PORTE,4);
				sbi(PORTB,0);
				sFLAG = 1;
			}
		}

		else if(nMODE == MODEEND)
		{
			Lcd_Print_Xy( 0, 0, "COST :          ");
			Lcd_Print_Xy( 1, 0, "   Thank You!   ");

			if(Read_ID % 2 == 1)
			{
				USER = NOMALUSER;
				//cbi(PORTB,1);
			}
			else
			{
				USER = UNNOMALUSER;
				//sbi(PORTB,1);
			}

			if(USER == NOMALUSER)	Cal_Cost = (((nHOR * 60) + nMIN) * 1500);
			else					Cal_Cost = (((nHOR * 60) + nMIN) * 1000);

			Lcd_Print_U16digit(0, 6, Cal_Cost);
			AX_Action(0, 0x03, 0x35, 0x02, 0x90);
			//cbi(PORTE,4);
			//sbi(PORTE,4);

			if(ADC_Average(0, 10) < 200)
			{
				nMODE = MODEREADY;
				cbi(PORTE,4);
				Read_ID = 0;
				nHOR = 0;
				nMIN = 0;
				nSEC = 0;
				Cal_Cost = 0;
			}
		}
 
		else
		{
			sFLAG = 0;
			
			if(rFLAG == 0)
			{
				Lcd_Print_Xy( 0, 0, "   This place   ");
				Lcd_Print_Xy( 1, 0, "    is empty    ");
				rFLAG = 1;
			}
			else	{}
		}
		//Lcd_Print_Xy( 1, 0, "test4           ");
	
			
	//--------------------------------------------------------------------------    
	}
	//Lcd_Print_Xy( 1, 0, "test5           ");
	return 0;
}

void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지

	Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(0,1000000);  		// 초기화_시리얼통신0
	Init_Uart(1,9600);  		// 초기화_시리얼통신1
	Init_ADC();
	Lcd_Init();
	
	sbi(DDRE,4);				//자리 표시 LED
	sbi(DDRE,2);
	sbi(DDRE,3);
	sbi(DDRB,0);				//signal parking
	//sbi(DDRB,1);				//signal user

	//Lcd_Print_Xy( 0, 0, "test            ");
	//Lcd_Print_Xy( 1, 0, "test1           ");
    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

void Read_RFID_card(void)		//This Module position in Uart_RX_ISR
{
	if((STBIT==1)&&(RFIDdata==0x46))
	{
		Read_ID = 0x01;
		STBIT = 0;
	}
	else if((STBIT==2)&&(RFIDdata==0x33))
	{
		Read_ID = 0x02;
		STBIT = 0;
	}
	else if((STBIT==3)&&(RFIDdata==0x34))
	{
		Read_ID = 0x03;
		STBIT = 0;
	}
	else if((STBIT==4)&&(RFIDdata==0x32))
	{
		Read_ID = 0x04;
		STBIT = 0;
	}
	else
	{
		STBIT = 0;
	}

	if(RFIDdata == 0x45)		STBIT = 1;
	else if(RFIDdata == 0x33)	STBIT = 2;
	else if(RFIDdata == 0x31)	STBIT = 3;
	else if(RFIDdata == 0x44)	STBIT = 4;

}
