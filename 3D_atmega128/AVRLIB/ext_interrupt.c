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
//                  외부 인터럽트 초기화 
//------------------------------------------------------------------------------
void Init_Ext_Interrupt(U08 INT)
{
	cbi(DDRD,0);
	cbi(DDRD,1);
	
    if( INT == INT0 )							// 외부인터럽트0 초기화
	{
		sbi( EICRA, ISC01 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC00 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT0  );    // EXT_INT 0 ENABLE
		cbi( EIFR , INTF0 );    // INTERRUPT FLAG CLEAR
		//EXT0_PORT_SETUP();		// Input Set, Pull-Up Setting
    }
    
    else if( INT == INT1 )						// 외부인터럽트1 초기화
	{
		sbi( EICRA, ISC11 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC10 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT1  );    // EXT_INT 1 ENABLE
		cbi( EIFR , INTF1 );    // INTERRUPT FLAG CLEAR
		//EXT1_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT2 )						// 외부인터럽트2 초기화
	{
		sbi( EICRA, ISC21 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC20 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT2  );    // EXT_INT 2 ENABLE
		cbi( EIFR , INTF2 );    // INTERRUPT FLAG CLEAR
		//EXT2_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT3 )						// 외부인터럽트3 초기화
	{        
		sbi( EICRA, ISC31 );    // FALLING EDGE ENABLE
		cbi( EICRA, ISC30 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT3  );    // EXT_INT 3 ENABLE
		cbi( EIFR , INTF3 );    // INTERRUPT FLAG CLEAR
		//EXT3_PORT_SETUP;		// Input Set, Pull-Up Setting
    }	
			
  	else if( INT == INT4 )						// 외부인터럽트4 초기화
	{			

		sbi( EICRB, ISC41 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC40 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT4  );    // EXT_INT 4 ENABLE
		cbi( EIFR , INTF4 );    // INTERRUPT FLAG CLEAR
		//EXT4_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
  	else if( INT == INT5 )						// 외부인터럽트5 초기화
	{        
		sbi( EICRB, ISC51 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC50 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT5  );    // EXT_INT 5 ENABLE
		cbi( EIFR , INTF5 );    // INTERRUPT FLAG CLEAR
		//EXT5_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT6 )						// 외부인터럽트6 초기화
	{
		sbi( EICRB, ISC61 );    // FALLING EDGE ENABLE
		cbi( EICRB, ISC60 );    // FALLING EDGE ENABLE
		sbi( EIMSK, INT6  );    // EXT_INT 6 ENABLE
		cbi( EIFR , INTF6 );    // INTERRUPT FLAG CLEAR
		//EXT6_PORT_SETUP;		// Input Set, Pull-Up Setting
    }
    
  	else if( INT == INT7 )						// 외부인터럽트7 초기화
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
//					외부 인터럽트 0 서비스루틴
//------------------------------------------------------------------------------
ISR(INT0_vect)
{
	Disable_ISR();
	BREAK_NUM0 = 1;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 1 서비스루틴
//------------------------------------------------------------------------------
ISR(INT1_vect)
{
	Disable_ISR();
	BREAK_NUM1 = 1;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 2 서비스루틴
//------------------------------------------------------------------------------
ISR(INT2_vect) 
{
	Disable_ISR();
	//Uart_Putch( 1, 3 );
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 3 서비스루틴
//------------------------------------------------------------------------------
ISR(INT3_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 4 서비스루틴
//------------------------------------------------------------------------------
ISR(INT4_vect)
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 5 서비스루틴
//------------------------------------------------------------------------------
ISR(INT5_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 6 서비스루틴
//------------------------------------------------------------------------------
ISR(INT6_vect) 
{
	Disable_ISR();
	Enable_ISR();
}

//------------------------------------------------------------------------------
//					외부 인터럽트 7 서비스루틴
//------------------------------------------------------------------------------
ISR(INT7_vect) 
{
	Disable_ISR();
	Enable_ISR();
}



                                                                                   

