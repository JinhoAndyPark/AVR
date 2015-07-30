/*==============================================================================
 *
 *   Main Function
 *
 *    	File Name   	: main.c
 *    	Version        	: 1.0
 *    	Date           	: 2012.12.24
 *		Modified       	: 2012.12.24 By Kim, Hyun-Jun
 *		Author         	: Kim, Hyun-Jun  (23rd)
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

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------
#define FORWARD			0
#define BACKWARD		1

#define STPULSEWIDE		400
#define STEP05MM		320


volatile U16 tic_10ms=0;

U08 DIR;
U08 data;

volatile U08 nXCD, nYCD;
volatile U08 XCD, YCD;

volatile U08 CoordinateX[5][10] = {
	{10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
	{30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
	{50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
	{70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
	{90, 91, 92, 93, 94, 95, 96, 97, 98, 99}
};


volatile U08 CoordinateY[5][10] = {
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}
};

//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------

void X_StepMotor_Move_1step( U08 Direction )
{
	Direction == FORWARD ? (PORTG &= ~( 1 << 1 )) : (PORTG |= 1 << 1);

	PORTG ^= 1 << 0;	//비트 xor 0110, PORTG0 이 0이면 1로 , 1이면 0로  
}

void Y_StepMotor_Move_1step( U08 Direction )
{
	Direction == FORWARD ? (PORTG &= ~( 1 << 4 )) : (PORTG |= 1 << 4);

	PORTG ^= 1 << 3;	//
}

void Homing_Plotter(void)
{
	//while(!)
}

void Moving_StartPoint(void)
{
	U16 stCNT;
	for( stCNT=0; stCNT<13*STEP05MM*2; stCNT++ )
	{
		X_StepMotor_Move_1step(FORWARD);
		Y_StepMotor_Move_1step(FORWARD);
		_delay_us(STPULSEWIDE);
	}
	nXCD = 0;
	nYCD = 0;
}

void Moving_XYCoordinate(U08 XCd, U08 YCd)
{
	volatile U08 GoalPositonX, GoalPositonY;
	volatile U08 MoveSpaceX=0, MoveSpaceY=0;
	volatile U08 MoveDirectionX=0, MoveDirectionY=0, HoldPositionX=0,HoldPositionY=0;
	GoalPositonX = XCd;
	GoalPositonY = YCd;

/*//-------------------------------------------------------------------*/

	if(GoalPositonX > nXCD)
	{
		MoveDirectionX = FORWARD;
		MoveSpaceX = GoalPositonX - nXCD;
		nXCD = GoalPositonX;
	}
	else if(GoalPositonX < nXCD)
	{
		MoveDirectionX = BACKWARD;
		MoveSpaceX = nXCD - GoalPositonX;
		nXCD = GoalPositonX;
	}
	else
	{
		HoldPositionX = 1;
	}


	if(GoalPositonY > nYCD)
	{
		MoveDirectionY = FORWARD;
		MoveSpaceY = GoalPositonY - nYCD;
		nYCD = GoalPositonY;
	}
	else if(GoalPositonY < nYCD)
	{
		MoveDirectionY = BACKWARD;
		MoveSpaceY = nYCD - GoalPositonY;
		nYCD = GoalPositonY;
	}
	else
	{
		HoldPositionY = 1;
	}

/*//-------------------------------------------------------------------*/

	if(HoldPositionX == 0)
	{
		for(U16 stCNT=0; stCNT < MoveSpaceX*STEP05MM; stCNT++)
		{
			X_StepMotor_Move_1step(MoveDirectionX);
			_delay_us(STPULSEWIDE);
		}
	}
	else { HoldPositionX = 0; }

	if(HoldPositionY == 0)
	{
		for(U16 stCNT=0; stCNT < MoveSpaceY*STEP05MM; stCNT++)
		{
			Y_StepMotor_Move_1step(MoveDirectionY);
			_delay_us(STPULSEWIDE);
		}
	}
	else { HoldPositionY = 0; }

/*//-------------------------------------------------------------------*/	

	
	
}

ISR(TIMER0_OVF_vect)	//1//1ms
{
	TCNT0 = 160;
	tic_10ms++;
	//if(tic_10ms > 100)
	//{
		tic_10ms = 0;
		//PORTG = ~PORTG;
		
		//PORTG |= 0x02;
	//}
}


ISR(USART0_RX_vect)
{
	Disable_ISR();

	data = UDR0;
	if(data == 'f') DIR = 1;
	else if(data=='b') DIR = 2;
	else if(data=='h') DIR = 3;
	else if(data=='a') DIR = 4;
	else if(data=='d') DIR = 5;
	else if(data=='w') DIR = 6;
	else if(data=='s') DIR = 7;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// 초기화_MCU
	
	
	while(1)
	{      		
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
		if(DIR == 1)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				X_StepMotor_Move_1step(FORWARD);
				Y_StepMotor_Move_1step(FORWARD);
				_delay_us(STPULSEWIDE);
			}
		}
		else if(DIR==2)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				X_StepMotor_Move_1step(BACKWARD);
				Y_StepMotor_Move_1step(BACKWARD);
				_delay_us(STPULSEWIDE);
			}
		}

		else if(DIR==3)
		{
			DIR = 0;
			Moving_StartPoint();
			_delay_ms(1000);
			Uart_Putch(0,nXCD);
			Uart_Putch(0,nYCD);

			for(U08 i=0; i<5; i++)
			{
				for(U08 j=0; j<10; j++)
				{
					Moving_XYCoordinate(CoordinateX[i][j], CoordinateY[i][j]);
					_delay_ms(100);
					Uart_Putch(0,nXCD);
					Uart_Putch(0,nYCD);
				}
				//Moving_XYCoordinate(CoordinateX[i], CoordinateY[i]);
				_delay_ms(1000);
				//Uart_Putch(0,nXCD);
				//Uart_Putch(0,nYCD);
			}
		}

		else if(DIR==4)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				X_StepMotor_Move_1step(BACKWARD);
				_delay_us(STPULSEWIDE);
			}
		}

		else if(DIR==5)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				X_StepMotor_Move_1step(FORWARD);
				_delay_us(STPULSEWIDE);
			}
		}

		else if(DIR==6)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				Y_StepMotor_Move_1step(FORWARD);
				_delay_us(STPULSEWIDE);
			}
		}

		else if(DIR==7)
		{
			DIR = 0;
			for(U16 cnt=0; cnt<STEP05MM; cnt++)
			{
				Y_StepMotor_Move_1step(BACKWARD);
				_delay_us(STPULSEWIDE);
			}
		}
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// 전체인터럽트 사용금지
	 
	//Init_IO();				// 초기화_입출력포트	
	//Init_Ext_Interrupt(INT0);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7
	Init_Timer();				// 초기화_타이머0/1/2/3
    Init_Uart(0,57600);  		// 초기화_시리얼통신0
	//Init_Uart(UART1,57600);  	// 초기화_시리얼통신1
	Init_ADC();				// 초기화_ADC
    //Init_SPI(MASTER);			// 초기화_SPI통신 
	//Init_TWI(MASTER);			// 초기화_TWI통신

	sbi(DDRG,0);	//step
	sbi(DDRG,1);	//dir
	sbi(DDRG,3);
	sbi(DDRG,4);
    
	Enable_ISR();            	// 전체인터럽트 사용허가
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
