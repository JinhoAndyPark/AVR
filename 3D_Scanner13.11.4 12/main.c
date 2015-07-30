
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
#include "main.h"		// ���α׷��� ������� ����

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
//U16 Packet[3] = {0,0,0}
ISR(USART1_RX_vect)
{	
		U08 Getch_USART1=UDR1;
		
		switch(Getch_USART1)
		{
		
			case 'A':
				
			Instruction[0] = 1 ;	// MOVE START POINT
			Uart_Putch(1,1);
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
	
	S16 cnt; // when operation for x_move_deg(ccw), it makes cnt<0
	U16 ccnt;
	
	Main_Init();

	while(1)	
	{	
		
		if( Instruction[0] == 1 )
		{
			
			_delay_ms(100);
			X_Move_Startpoint();
			_delay_ms(100);
			//Y_Move_Startpoint();
			Instruction[0] = 0;
		}

		else if( Instruction[1] == 1)
		{
			
			Moving(); // until start point 

			for(ccnt=0; ccnt<17; ccnt++)
			{
				while(1)
				{	
					_delay_ms(1500);
					WRONG_SIG = 0;
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					/*
					Compare_Dis();
					if( WRONG_SIG == 0 )
					{	
						BREAK_NUM0 = 0;
						for(cnt=0; cnt<200; cnt++) 
						{
							X_Move_deg(CCW);
						}
					}*/
					///////////////////////////////////////////////once
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
						for(cnt=0; cnt<400; cnt++) 
						{
							X_Move_deg(CCW);
						}
					}	
					_delay_ms(500);
					Compare_Dis();
					_delay_ms(5);
					if( WRONG_SIG == 0 )		
					break;					//wonder the closest repeat sentence ..while(1)? yeap!
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
			_delay_ms(100);
			X_Move_Startpoint();
			_delay_ms(100);
			Y_Move_Startpoint();
			Instruction[1] = 0;
		}
		
		else if( Instruction[2] == 1)
		{
			
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
			Instruction[2] = 0;
		}
	

		else if(Instruction[3] == 1)
		{	
			
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
			Instruction[3] = 0;
		}
		
	
	}
	
	
	
	
	return 0;
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------

void Main_Init(void)
{
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������
	
	//Init_IO();				// �ʱ�ȭ_�������Ʈ	
	Init_Ext_Interrupt(INT0);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	Init_Ext_Interrupt(INT1);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	//Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(UART0,57600);  		// �ʱ�ȭ_�ø������0
	Init_Uart(UART1,57600);  	// �ʱ�ȭ_�ø������1
	Init_ADC();					// �ʱ�ȭ_ADC
    //Init_SPI(MASTER);			// �ʱ�ȭ_SPI��� 
	//Init_TWI(MASTER);			// �ʱ�ȭ_TWI���

	//Uart_Getch(1);					
						
	Motor_Init();

	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

void Compare_Dis(void)
{
	U16 cnt;

	for(cnt=0; cnt<200; cnt++)
	{
		if( SENSING_CW[cnt] > 80 )
		{
			WRONG_SIG=1;
		}
		
	}
}
/*
void Data_Packet(void)
{
	U16 ccnt;
	U16 cnt;
	for(ccnt=0; ccnt<200; ccnt++)
	{
		Packet[0] = ff;
		Packet[1] = SENSING_CW[ccnt];
		Packet[2] = ee;

		
		for(cnt=0; cnt<3; cnt++)
		{
			Uart_Putch(1, Packet[cnt]);
		}







void for_hyesook(void)		//���� �����͸� ��Ŷ�������� �������� �̤� ���������ǹ����� ���� 
{							//�׷��� FF DATA EE �̷��������� �����ǵ� �� �̰� ������ ���ϱ� �׷����ϴµ� 
							//���ǻ� �̷��� ... �ʰ� ��������������� �װɷ������ ������
	for(cnt=0; cnt<200 ; cnt++)
	{
		if(parameter[0] == FF)
		{
			parameter[1] = save_data[cnt] //save_data �� ���� �迭�� �ִ°�,

			if(parameter[2] == EE)
			{
				check = check++;
			}
		}
	}

	if(check == 200)
	Drawing();			//�׸��� �Լ� ����
	else
	request_data  //data ���� ���û 
}
		*/			
		
