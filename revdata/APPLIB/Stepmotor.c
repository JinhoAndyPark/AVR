/*==============================================================================
 *
 *   Packet Making Module
 *
 *   File Name   	: Stepmotor.c
 *   Version        	: 1.0
 *   Date           	: 2013.05.26
 *	 Modified       	: 2013.05.26 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/
#include "Stepmotor.h"


volatile U08 nXCD, nYCD;
volatile U08 XCD, YCD;


void X_StepMotor_Move_1step( U08 Direction )
{
	Direction == FORWARD ? (PORTG &= ~( 1 << 1 )) : (PORTG |= 1 << 1);

	PORTG ^= 1 << 0;
}

void Y_StepMotor_Move_1step( U08 Direction )
{
	Direction == FORWARD ? (PORTG &= ~( 1 << 4 )) : (PORTG |= 1 << 4);

	PORTG ^= 1 << 3;
}

void Position_Homing(void)
{
	
	//while(/*!Xaxis Photo INT check*/0)
	//{
	//	X_StepMotor_Move_1step(BACKWARD);
	//	_delay_ms(STPULSEWIDE);
	//}
	//while(/*!Yaxis Photo INT check*/0)
	//{
	//	Y_StepMotor_Move_1step(BACKWARD);
	//	_delay_ms(STPULSEWIDE);
	//}
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

