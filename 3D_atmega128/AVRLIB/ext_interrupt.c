/*==============================================================================
 *
 *   External Interrupt Module
 *
 *        File Name   		: ext_interrupt.c
 *        Version        	: 1.2
 *        Date           	: 2013.10.29
 *        Author         	: Park, Jin-Ho  (ROLAB 27th)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2013.10.29 By Park, Jin-Ho
 *        Copyright(c) ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <avr/io.h>
#include "../define.h"
#include <avr/interrupt.h>

extern U08 BREAK_NUM0;
extern U08 BREAK_NUM1;

//------------------------------------------------------------------------------
//                  �ܺ� ���ͷ�Ʈ �ʱ�ȭ 
//------------------------------------------------------------------------------
void Init_Ext_Interrupt(U08 INT)
{
	cbi(DDRD,0);
	cbi(DDRD,1);
	
    if( INT == INT0 )							// �ܺ����ͷ�Ʈ0 �ʱ�ȭ
	{
		sbi( EICRA, ISC01 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC00 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT0  );    // EXT_INT 0 ENABLE
		cbi( EIFR , INTF0 );    // INTERRUPT FLAG CLEAR
		//EXT0_PORT_SETUP();		// Input Set, Pull-Up Setting
    }
    
    else if( INT == INT1 )						// �ܺ����ͷ�Ʈ1 �ʱ�ȭ
	{
		sbi( EICRA, ISC11 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC10 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT1  );    // EXT_INT 1 ENABLE
		cbi( EIFR , INTF1 );    // INTERRUPT FLAG CLEAR
		//EXT1_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT2 )						// �ܺ����ͷ�Ʈ2 �ʱ�ȭ
	{
		sbi( EICRA, ISC21 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC20 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT2  );    // EXT_INT 2 ENABLE
		cbi( EIFR , INTF2 );    // INTERRUPT FLAG CLEAR
		//EXT2_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT3 )						// �ܺ����ͷ�Ʈ3 �ʱ�ȭ
	{        
		sbi( EICRA, ISC31 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC30 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT3  );    // EXT_INT 3 ENABLE
		cbi( EIFR , INTF3 );    // INTERRUPT FLAG CLEAR
		//EXT3_PORT_SETUP;		// Input Set, Pull-Up Setting
    }	
			
  	else if( INT == INT4 )						// �ܺ����ͷ�Ʈ4 �ʱ�ȭ
	{			

		sbi( EICRB, ISC41 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC40 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT4  );    // EXT_INT 4 ENABLE
		cbi( EIFR , INTF4 );    // INTERRUPT FLAG CLEAR
		//EXT4_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
  	else if( INT == INT5 )						// �ܺ����ͷ�Ʈ5 �ʱ�ȭ
	{        
		sbi( EICRB, ISC51 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC50 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT5  );    // EXT_INT 5 ENABLE
		cbi( EIFR , INTF5 );    // INTERRUPT FLAG CLEAR
		//EXT5_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT6 )						// �ܺ����ͷ�Ʈ6 �ʱ�ȭ
	{
		sbi( EICRB, ISC61 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC60 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT6  );    // EXT_INT 6 ENABLE
		cbi( EIFR , INTF6 );    // INTERRUPT FLAG CLEAR
		//EXT6_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT7 )						// �ܺ����ͷ�Ʈ7 �ʱ�ȭ
	{        
		sbi( EICRB, ISC71 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC70 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT7  );    // EXT_INT 7 ENABLE
		cbi( EIFR , INTF7 );    // INTERRUPT FLAG CLEAR
		//EXT7_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    else
    {}

}




//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 0 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT0_vect)
{
	Disable_ISR();
	BREAK_NUM0 = 1;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 1 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT1_vect)
{
	Disable_ISR();
	BREAK_NUM1 = 1;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 2 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT2_vect) 
{
	Disable_ISR();
	//Uart_Putch( 1, 3 );
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 3 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT3_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 4 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT4_vect)
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 5 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT5_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 6 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT6_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					�ܺ� ���ͷ�Ʈ 7 ���񽺷�ƾ
//------------------------------------------------------------------------------
ISR(INT7_vect) 
{
	Disable_ISR();
	Enable_ISR();
}



                                                                                   

