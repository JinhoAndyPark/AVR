
//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------



/*==============================================================================
 *
 *   Main Function
 *
 *    	File Name   	: main.c
 *    	Version        	: 1.0
 *    	Date           	: 2013.10.30
 *		Modified       	: 2013.10.30 By Park, Jin-Ho
 *		Author         	: Park, Jin-Ho  (27th)
 *		MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: WINAVR use AVRstudio 4.18
 *		Copyright(c) ROLAB, Kwangwoon University.
 *    	All Rights Reserved.
 *
==============================================================================*/


//------------------------------------------------------------------------------
//	=== Include Headerfile ===
//------------------------------------------------------------------------------
#include "main.h"		// 프로그램의 헤더파일 설정

#define CW				0
#define CCW				1

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------
U08 BREAK_NUM0 = 0;		//extern
U08 BREAK_NUM1 = 0;
U08 Instruction[5]={0,0,0,0,0};

U16 SENSING_CW[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U16 SENSING_CCW[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
U08 WRONG_SIG = 0; 
U16 Dis;

ISR(USART1_RX_vect)
{	
		U08 Getch_USART1=UDR1;
		
		switch(Getch_USART1)
		{
		
			case 'A':
				
			Instruction[0] = 1 ;	// MOVE START POINT
			//Uart_Putch(1,1);
			break;
			
		
			case 'B' :

			Instruction[1] = 1;	// OPERATE SCANNING
			
			//Uart_Putch(1,2);
			break;
			
			case 'C' :
				
			Instruction[2] = 1;	// SENSING & RETURN 
		
			break;

			case 'D' :

			Instruction[3] = 1;  // SENSING 1DEG

			break;

			
			case 'U' :			// UP 
			
			Y_Move_Simple(CW);

			break;

			case 'W' :			// DOWN 
			
			Y_Move_Simple(CCW);

			break;
			
	}

}
int main(void)
{	
	//U16 SENSING_CW[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//U16 SENSING_CCW[200] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//U16 Dis;
	S16 cnt; // when operation for x_move_deg(ccw), it makes cnt<0
	U16 ccnt;
	
	Main_Init();

	while(1)	
	{	
		
		if( Instruction[0] == 1 )
		{
			Instruction[0] = 0;
			_delay_ms(100);
			X_Move_Startpoint();
			_delay_ms(100);
			//Y_Move_Startpoint();

		}

		else if( Instruction[1] == 1)
		{
			Instruction[1] = 0;
			Moving(); // until start point 

			for(ccnt=0; ccnt<17; ccnt++)
			{
				while(1)
				{	
					_delay_ms(500);
					WRONG_SIG = 0;
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					_delay_ms(500);
					
					if( BREAK_NUM0 == 1)
					{
						BREAK_NUM0 = 0;
						_delay_ms(1);
						for(cnt=199; cnt>=0; cnt--) 
						{
							X_Move_deg(CCW);
							SENSING_CCW[cnt] = Dis;
						}
					}	
					_delay_ms(500);
					Compare_Dis();
					_delay_ms(5);
					if( WRONG_SIG == 0 )		
					break;					//wonder the closest repeat sentence ..while(1)?
				}	
				_delay_ms(500);
				///////////////////////////// X_sensing and return until this line
				Y_Move_Simple(CCW);
				_delay_ms(1);
				
				if( BREAK_NUM1 == 1 )
				{
					BREAK_NUM1 = 0;
					break;
				}
			}
				
		}
		
		else if( Instruction[2] == 1)
		{
			Instruction[2] = 0;
			for(cnt=0; cnt<200; cnt++)
			{
				X_Move_deg();
			}
			_delay_ms(1);
			
			if( BREAK_NUM0 == 1)
			{
				BREAK_NUM0 = 0;
				_delay_ms(1);
				X_Move_Return();
			}	
		}
	

		else if(Instruction[3] == 1)
		{	
			Instruction[3] = 0;
			//X_Move_deg(CW);
			//Read_ADC_NOSTOP(0);
			//Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
			//Uart_U16Bit_PutNum(1,Dis);

			
			for(cnt=0;cnt<200;cnt++)
			{
			Uart_U16Bit_PutNum(1,SENSING_CW[cnt]);
			}
			_delay_ms(1000);
			for(cnt=0;cnt<200;cnt++)
			{
			Uart_U16Bit_PutNum(1,SENSING_CCW[cnt]);
			}
			
		}
		
	
	}
	
	
	
	
	return 0;
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------

void Main_Init(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	
	//Init_IO();				// 초기화_입출력포트	
	Init_Ext_Interrupt(INT0);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7
	Init_Ext_Interrupt(INT1);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7
	//Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(UART0,9600);  		// 초기화_시리얼통신0
	Init_Uart(UART1,9600);  	// 초기화_시리얼통신1
	Init_ADC();					// 초기화_ADC
    //Init_SPI(MASTER);			// 초기화_SPI통신 
	//Init_TWI(MASTER);			// 초기화_TWI통신

	//Uart_Getch(1);					
						
	Motor_Init();

	Enable_ISR();            	// 전체인터럽트 사용허가
}

void Compare_Dis(void)
{
	U16 cnt;
	Uart_Putch(1,999);
	for(cnt=0; cnt<200; cnt++)
	{
		if( SENSING_CW[cnt] == SENSING_CCW[cnt] )
		{
			SENSING_CW[cnt] = SENSING_CW[cnt];
		}
		else if( SENSING_CW[cnt] > SENSING_CCW[cnt] )
		{
			if( SENSING_CW[cnt] - SENSING_CCW[cnt] <= 2 )
			SENSING_CW[cnt] = SENSING_CW[cnt];
			else if( SENSING_CW[cnt] - SENSING_CCW[cnt] > 2 )
			{
				WRONG_SIG = 1;
				break;
			}
		}
		else if( SENSING_CW[cnt] < SENSING_CCW[cnt] )
		{
			if( SENSING_CCW[cnt] - SENSING_CW[cnt] <= 2 )	
			SENSING_CW[cnt] = SENSING_CCW[cnt];	
			else if( SENSING_CCW[cnt] - SENSING_CW[cnt] > 2 )
			{
				WRONG_SIG = 1;
				break;
			}
		}
	}
}
			
