/*==============================================================================
 *
 *   Step Motor Drive
 *
 *        File Name      : Step_Motor.h
 *        Version        : 1.0
 *        Date           : 2013.10.30
 *        Author         : Park, Jin-Ho (ROLAB 27th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Add_Description: SST42D1100 / SLA7026M
 *        Modified       : 2013.10.30 By Park, Jin-Ho
 *        Copyright(c)ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../Define.h"
#include "motor_step.h"
#include <util/delay.h>

extern U08 BREAK_NUM0;
extern U08 BREAK_NUM1;

void Motor_Init(void)
{
	DDRA = 0xff;	//PORTA OPEN
	
	FULL_MODE;		//2//2_phase	
	RESET_LOW;	

	LEFT_CW;		//left motor cw dir	
	RIGHT_CW;		//right motor cw dir		 
}


void X_StepMotor_Move_1step( U08 Direction )
{
	Direction == CW ? (PORTA |= 1 << 7) : (PORTA &= ~( 1 << 7 ));

	PORTA ^= 1 << 6;	//비트 xor 0110, PORTG0 이 0이면 1로 , 1이면 0로  so then, twice make a move
}

void Y_StepMotor_Move_1step( U08 Direction )
{
	Direction == CW ? (PORTA |= 1 << 1) : (PORTA &= ~( 1 << 1 ));

	PORTA ^= 1 << 5;	
}

void X_Move_Startpoint(void)
{
	U16 stCNT;
	
		
	//Range_Out(CW);
		
	for( stCNT=0; stCNT<500; stCNT++ )
	{
		X_StepMotor_Move_1step(CCW);
		_delay_ms(5);
		
		if( BREAK_NUM0 == 1 )
		break;
	}
	/*
	if( BREAK_NUM0 == 1)
	{
		BREAK_NUM0 = 0;
	}		
	else if( BREAK_NUM0 == 0);
	{
		for( stCNT=0; stCNT<10; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_us(700);

			if( BREAK_NUM0 == 1)
				break;
		}
		
		BREAK_NUM0 = 0;
	}
	*/
}

void Y_Move_Startpoint(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<60000; stCNT++ )
	{
		Y_StepMotor_Move_1step(CCW);
		_delay_us(YSTPULSEWIDE);
		
		if( BREAK_NUM1 == 1 )
		break;
	}
	BREAK_NUM1 = 0;
}

void Range_Out(U08 DIR)			////photo interrupt range out
{
	U16 stCNT;
	
	if(DIR == CW)
	{
		for( stCNT=0; stCNT<2; stCNT++ )
		{
			X_StepMotor_Move_1step(CW);
			_delay_ms(XSTPULSEWIDE);
		}						
	}
	else if(DIR == CCW)
	{
		for( stCNT=0; stCNT<2; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_ms(XSTPULSEWIDE);
		}	
		sbi(PORTA,6);	//clk set
	}
}

void X_Move_deg(void)	
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<2; stCNT++ )
	{
		X_StepMotor_Move_1step(CW);
		_delay_us(700);
	}
	_delay_ms(8);
	
	//Read_ADC(0);
}

void X_Move_Return(void)
{
	U16 stCNT;
	
		
	Range_Out(CW);
		
	for( stCNT=0; stCNT<500; stCNT++ )
	{
		X_StepMotor_Move_1step(CW);
		_delay_ms(4);
		
		if( BREAK_NUM0 == 2 )
		break;
	}
	BREAK_NUM0 = 0;
}

void Y_Move_Up(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<1500; stCNT++ )
	{
		Y_StepMotor_Move_1step(CW);
		_delay_us(YSTPULSEWIDE);
		
		//if( BREAK_NUM1 == 1 )
		//break;
	}
	BREAK_NUM1 = 0;
}

void Moving(void)
{
		sbi(PORTA,5);
		_delay_us(850);
		cbi(PORTA,5);
		_delay_us(850);
		/*
	U16 stCNT;
	for( stCNT=0; stCNT<400; stCNT++ )
	{
		//X_StepMotor_Move_1step(CW);
	//	Y_StepMotor_Move_1step(CW);
		//_delay_us(800);
		sbi(PORTA,6);
		_delay_us(2);
		cbi(PORTA,6);
	}
	//nXCD = 0;
	//nYCD = 0;
	*/
}

