
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
extern U08 Fisrtpoint_Flag;
extern U08 Instruction2;
extern U08 SIG_To2[3];
//U16 step_table[14] = {650,625,610,600,590,580,580,580,580,580,590,600,610,625,650};
					  
					  
					   

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

void X_Move_Startpoint( U08 Direction )
{
	U16 stCNT;

	if( Direction == CCW )
	{	
		for( stCNT=0; stCNT<30; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_ms(5);
		}
		BREAK_NUM0 = 0;
		for( stCNT=0; stCNT<420; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_ms(5);
			if( BREAK_NUM0 == 1 )
			break;
			
		}
		BREAK_NUM0 = 0;
	}
	else if( Direction == CW )
	{	
		for( stCNT=0; stCNT<6; stCNT++ )
		{
			X_StepMotor_Move_1step(CW);
			_delay_ms(5);
		}
		BREAK_NUM0 = 0;
		for( stCNT=0; stCNT<450; stCNT++ )
		{
			X_StepMotor_Move_1step(CW);
			_delay_ms(5);
			if( BREAK_NUM0 == 1 )
			break;
			
		}
		BREAK_NUM0 = 0;
	}
}

void Y_Move_Startpoint(void)
{
	U16 stCNT;
	
	for( stCNT=0; stCNT<35000; stCNT++ )
	{
		Y_StepMotor_Move_1step(CW);
		_delay_us(650);
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
		Uart_Putch(0,SIG_To2[1]);	
		_delay_ms(6);
	}
	
	else if( Direction == CCW )
	{
		for( stCNT=0; stCNT<2; stCNT++ )
		{
			X_StepMotor_Move_1step(CCW);
			_delay_ms(6);
		}
	}
}


void Y_Move_Simple( U08 Direction )
{
	U16 stCNT;

	if( Direction == CW )
	{
		for( stCNT=0; stCNT<3000; stCNT++ )
		{
			Y_StepMotor_Move_1step(CW);
			_delay_us(YSTPULSEWIDE);
		}
	}
	else if( Direction == CCW )
	{
		for( stCNT=0; stCNT<1500; stCNT++ )		//1//1500 : 0.4cm down
		{
			Y_StepMotor_Move_1step(CCW);
			_delay_us(YSTPULSEWIDE);

			if( BREAK_NUM1 == 1 )
			break;
		}
		//BREAK_NUM1 = 0;
	}
}

void Lets_Do_FirstStep(void)	//x&y go first point
{
	//X_Move_Startpoint(); 
	
	U16 stCNT;
	
	for( stCNT=0; stCNT<30000; stCNT++ )
	{
		Y_StepMotor_Move_1step(CCW);
		_delay_us(700);
		
		if( Fisrtpoint_Flag == 1)
		break;
	}
	Fisrtpoint_Flag = 0;
	
	sbi( TIMSK, TOIE0 );
	_delay_ms(100);

	//sbi( TIMSK, TOIE0 );
	
	for( stCNT=0; stCNT<2300; stCNT++ )
	{
		Y_StepMotor_Move_1step(CCW);
		_delay_us(YSTPULSEWIDE);
	}
	
////////////////////////////////////////// fisrt sensing and set start location until this line
	
	
}
