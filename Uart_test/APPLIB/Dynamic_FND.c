/*==============================================================================
 *
 *   Dynamic Display FND Module
 *
 *   File Name   	: Dynamic_FND.c
 *   Version        	: 1.0
 *   Date           	: 2013.01.03
 *	 Modified       	: 2013.01.03 By Kim, Hyun-Jun
 *	 Author         	: Kim, Hyun-Jun  (23rd)
 *	 MPU_Type       	: ATmega128(16MHz)
 *	 Compiler		: WINAVR use AVRstudio 4.18
 *	 Copyright(c) ROLAB, Kwangwoon University.
 *   All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../define.h"
#include "Dynamic_FND.h"

//------------------------------------------------------------------------------
// * Dynamic Display - 초당 30 프레임 이상의 속도로 빠르게 두개 이상의 FND를 토글하여
//	  				   모든 FND가 점등되있는 효과가 가능.
// * Active Low
// * not using 7447
// * Using common anode Type
// * PORTC[0:7] -> FND A~Dp	,	PORTA[4:7] -> FND[1:4]
//------------------------------------------------------------------------------

#define NUMBERFND		4			//number of FND
#define FNDPORT			PORTC		//FND connect Port
#define FNDSEL			PORTA


//FND number      0,   1,   2,   3,   4,   5,   6,   7,   8,   9, Non
U08 FND[11] = {0x11,0xD7,0x32,0x52,0xD4,0x58,0x1C,0xD1,0x10,0xD0,0xFF};

U08 FND_pos = 0, Fcnt = 0, Fmask;
U08 FND_digit[NUMBERFND];
U16 nFND = 0;

//------------------------------------------------------------------------------
//					===== Dynamic_FND 초기화 설정 =====
//------------------------------------------------------------------------------

void Init_Dynamic_FND(void)
{
	DDRC = 0xFF;		//FND Port Output setting
	
	sbi( DDRA, 4 );		//Port For FND Toggle
	sbi( DDRA, 5 );
	sbi( DDRA, 6 );
	sbi( DDRA, 7 );
}

//------------------------------------------------------------------------------
//					===== Display_FND Function ===== 
//				 (* This module should be added to ISR )
//------------------------------------------------------------------------------

void Display_FND_ISR(void)
{
	FND_pos++;
	if(FND_pos >= NUMBERFND*2)	FND_pos = 0;

	if(FND_pos % 2 == 0)
	{
		FNDPORT = FND[FND_digit[FND_pos/2]];

		Fcnt	&=	0x0F;
		Fmask 	=	0x80;
		Fmask 	>>=	FND_pos/2;
		Fcnt 	|=	Fmask;
		FNDSEL	=	Fcnt;
	}
	else
		FNDPORT = 0xFF;	
}

//------------------------------------------------------------------------------
//					===== Display_FND Function =====
//			  	  (* This module should be added to main roop )
//------------------------------------------------------------------------------

void Display_FND(void)
{
	U08 cFND, size=0;
	U16 square = 1;
		
	for(cFND=0; cFND<NUMBERFND; cFND++)
	{
		if(cFND==0)		FND_digit[cFND] = nFND % 10;	
		else
		{
			for(size=0; size<cFND; size++)
			{
				square *= 10;
			}
			if(cFND == NUMBERFND-1)	FND_digit[cFND] = nFND / square;
			else	FND_digit[cFND] = (nFND % (square*10)) / square;
			square = 1;
		}
	}
	cFND = 0;
}

