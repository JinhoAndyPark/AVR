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
extern U16 Dis;

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
	
	for( stCNT=0; stCNT<500; stCNT++ )
	{
		X_StepMotor_Move_1step(CCW);
		_delay_ms(5);
		
		if( BREAK_NUM0 == 1 )
		break;
	}
	BREAK_NUM0 = 0;
}

void Y_Move_Startpoint(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<42000; stCNT++ )
	{
		Y_StepMotor_Move_1step(CW);
		_delay_us(YSTPULSEWIDE);
		
	}
	BREAK_NUM1 = 0;
}


void X_Move_deg( U08 Direction )	
{
	U16 stCNT;

	if( Direction == CW )
	{
		for( stCNT=0; stCNT<2; stCNT++ )
		{
			X_StepMotor_Move_1step(CW);
			_delay_us(700);
		}
		
		Read_ADC(0);
		Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
		Uart_U16Bit_PutNum(1,Dis);
		
		_delay_ms(5);

		sbi( ADCSRA, ADEN );
	}
	
	else if( Direction == CCW )
	{
		for( stCNT=0; stCNT<2; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_us(700);
		}
		
		Read_ADC(0);
		Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
		Uart_U16Bit_PutNum(1,Dis);
		
		
		_delay_ms(5);
		
		sbi( ADCSRA, ADEN );
	}
}

void X_Move_Return(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<400; stCNT++ )
	{
		X_StepMotor_Move_1step(CCW);
		_delay_ms(5);
	}
	_delay_ms(1);
	if(BREAK_NUM0 == 0)
	{
		X_StepMotor_Move_1step(CCW);
		_delay_ms(5);
		X_StepMotor_Move_1step(CCW);
		_delay_ms(5);
	}
}

void Y_Move_Simple( U08 Direction )
{
	U16 stCNT;

	if( Direction == CW )
	{
		for( stCNT=0; stCNT<1500; stCNT++ )
		{
			Y_StepMotor_Move_1step(CW);
			_delay_us(YSTPULSEWIDE);
		}
	}
	else if( Direction == CCW )
	{
		for( stCNT=0; stCNT<3000; stCNT++ )		//1//1500 : 0.4cm down
		{
			Y_StepMotor_Move_1step(CCW);
			_delay_us(YSTPULSEWIDE);

			if( BREAK_NUM1 == 1 )
			break;
		}
		//BREAK_NUM1 = 0;
	}
}

void Moving(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<30000; stCNT++ )
	{
		Y_StepMotor_Move_1step(CCW);
		_delay_us(20);

		Read_ADC_NOSTOP(0);
		Dis = (( (11.65/(( ADC/204.8) - 0.147 )) - 0.42 ) * 10)-4;
		
		if( Dis <  65 )
		break;
	}
	_delay_ms(1500);
	
	for( stCNT=0; stCNT<1500; stCNT++ )
	{
		Y_StepMotor_Move_1step(CCW);
		_delay_us(YSTPULSEWIDE);
	}

////////////////////////////////////////// fisrt sensing and set start location until this line
	
	
}