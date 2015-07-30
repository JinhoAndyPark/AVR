
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


#define Fisrtpoint_SIG  1


//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------
U08 BREAK_NUM0 = 0;		//x ex interrupt
U08 BREAK_NUM1 = 0;		//y ex interrupt
U08 Instruction[5]={0,0,0,0,0};	//for main
U08 Instruction2 = 0;
U08 SIG_To2[5] = {1,2,3,4,5};
U16 SENSING_CW[210] = {0};
U16 Filtering[200] = {0};
U08 WRONG_SIG = 0; 	
U16 Dis = 0;
U08 Fisrtpoint_Flag = 0;
U16 op_cnt = 0; //measuring opertaion count
U08 result_op_cnt = 0;
U16 Height = 0;
U08 Percent[15] = {0};
U08 Percent10[15] = {0};
U08 Percent1[15] = {0};
//------------------------------------------------------------------------------
//                   		=== Text Variable Declaration ===
//------------------------------------------------------------------------------
S08 *str1="<Welcome to>";
S08 *str2="<3D Scanner>";
S08 *str3="< Auto Mode >";
S08 *str4="<Measure Height>";
S08 *str5="<The Height is: >";
S08 *str6="<Scanning.. ";
S08 *str8="<100% Done>";
S08 *str9="<Laser Off>";
S08 *str10="<Complete ^_^ >";
S08 *str11="< Fast Mode >";
S08 arr[8] = {0};

ISR(USART0_RX_vect)
{	
	U08 Getch_USART = UDR0;

	if( Getch_USART == 1)
	{
		Fisrtpoint_Flag = 1;
	}
	else
	{
		Dis = Getch_USART;
	}
}


ISR(USART1_RX_vect)
{	
		U08 Getch_USART1=UDR1;

	//	Uart_Putch(0, Getch_USART1);
	//	Uart_Putch(1, Getch_USART1);
		
		switch(Getch_USART1)
		{
		
			case 'A':
				
			Instruction[0] = 1 ;	// AUTOMODE
			break;
			
			case 'B' :

			Instruction[1] = 1;	// FASTMODE
			break;
			
			case 'C' :
				
			Instruction[2] = 1;	// RIGHT 
			break;

			case 'D' :

			Instruction[3] = 1;	  // LEFT
			break;

			case 'E' :
			
			Uart_Putch(0,SIG_To2[2]);	//Laser off
			
			break;
	
			case 'U' :			// UP 
			
			Y_Move_Simple(CW);
			break;

			case 'O' :			// DOWN 
			
			Y_Move_Simple(CCW);
			break;
			
	}

}

ISR(TIMER0_OVF_vect)
{
	op_cnt = op_cnt++;

	if( op_cnt == 125)
	{
		result_op_cnt=result_op_cnt++;
		op_cnt = 0;
	}
	
	TCNT0=131;
}
int main(void)
{	
	
	S16 cnt; // when operation for x_move_deg(ccw), it makes cnt<0
	U16 ccnt;
	U16 stCNT;
	U08 i;
	Main_Init();

	lcd_iw(0x01);
	lcd_str(str1);	//Welcome to 3D
	lcd_iw(0xc0);	
	lcd_str(str2);	//Scanning world
	
	while(1)	
	{	

		//------------------------------------------------------------------------------ 
		//		=== AUTO MODE ===
		//------------------------------------------------------------------------------
		if( Instruction[0] == 1)
		{	
			Instruction[0] = 0;
			
			Uart_Putch( 0,SIG_To2[0] );	//SIG_To2
			
			lcd_iw(0x01);
			lcd_str(str3);	//<Sensing...>
			lcd_iw(0xc0);	
			lcd_str(str4);	//<Please, Wait^^>"
			
			Lets_Do_FirstStep(); // until start point 
			_delay_ms(1);
			
			for( stCNT=0; stCNT<55000; stCNT++ )
			{
				Y_StepMotor_Move_1step(CCW);
				_delay_us(600);
		
				if( BREAK_NUM1 == 1 )
				{	
					cbi( TIMSK, TOIE0 );
					_delay_ms(10);
					
					Height = (56 * result_op_cnt);
					arr[1] = (Height/1000);
					arr[2] = (Height%1000)/100;
					arr[4] = ((Height%100)/10);
					arr[5] = ((Height%10));

					lcd_iw(0x01); // ALL CLEAR
					lcd_str(str5);	//<The Height is: >				
					lcd_iw(0xc0);
					
					lcd_dw('<');	//1//0
					for(i=1 ;i<3 ;i++)
					{
						lcd_dw(arr[i]+48);	//1//1,2
					}			//4
					lcd_dw('.');	//3//3
					for(i=4 ;i<6 ;i++)
					{
						lcd_dw(arr[i]+48);	//1//4,5
					}			//4//4,5
					lcd_dw('c');	//6		
					lcd_dw('m');	//7
					lcd_dw('>');	//8
					break;
				}
			}
			_delay_ms(10);	//system delay
			
			Y_Move_Startpoint();
			///////////////////////////////measuring op_time until this line
			Uart_Putch(0,SIG_To2[0]);	
			
			lcd_iw(0x01);
			lcd_str(str6);	//<Scanning..>
			lcd_iw(0xc0);	
			lcd_str(str4);	//<Please, Wait^^>"
			
			Lets_Do_FirstStep();
			
			for(ccnt=0; ccnt<25; ccnt++)
			{
				while(1)
				{	
					WRONG_SIG = 0;

					X_Move_Startpoint(CCW);
		
					_delay_ms(10);	//system delay
					
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					for(cnt=0; cnt<210; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}

					_delay_ms(10);
					Filter();
					_delay_ms(10);
					
					X_Move_Startpoint(CCW);
						
					//Compare_Dis();
					
					//if( WRONG_SIG == 0 )
						//{
						Percent[ccnt] = ((5200/Height)*(ccnt+2));
						Percent10[ccnt] = Percent[ccnt]/10;
						Percent1[ccnt] = Percent[ccnt]%10;
						
						lcd_iw(0x01);
						lcd_str(str6);
						lcd_dw(Percent10[ccnt]+48);
						lcd_dw(Percent1[ccnt]+48);
						lcd_dw('%');
						lcd_dw('>');
						
						break;					//wonder the closest repeat sentence ..while(1)? yeap!
					//}
					
				}	
				_delay_ms(10);
				///////////////////////////// X_sensing and return until this line
				Y_Move_Simple(CCW);
				
				if( BREAK_NUM1 == 1 )
				{
					BREAK_NUM1 = 0;
					
					X_Move_Startpoint(CCW);
					
					_delay_ms(10);
					
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					for(cnt=0; cnt<210; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}

					_delay_ms(10);
					Filter();
					_delay_ms(10);
					
					X_Move_Startpoint(CCW);
					
					
					lcd_iw(0x01);
					lcd_str(str8);	//100% Done
					Y_Move_Startpoint();
			
					Uart_Putch(0,SIG_To2[2]);	//sig to2 : laser off

					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);	//laser off complete
					_delay_ms(1000);
					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);
					_delay_ms(1000);
					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);
					_delay_ms(1000);

				 break;
				}
			}
		}

		//------------------------------------------------------------------------------ 
		//		=== FAST MODE ===
		//------------------------------------------------------------------------------		
		else if( Instruction[1] == 1)
		{
			Instruction[1] = 0;
			
			Uart_Putch(0,SIG_To2[0]);	
			
			lcd_iw(0x01), lcd_str(str11), lcd_iw(0xc0), lcd_str(str6);	//< Fast Mode > <Scanning..>
			
			Lets_Do_FirstStep();
			
			for(ccnt=0; ccnt<25; ccnt++)
			{
				while(1)
				{	
					WRONG_SIG = 0;

					X_Move_Startpoint(CCW);
		
					_delay_ms(10);	//system delay
					
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					for(cnt=0; cnt<210; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}

					_delay_ms(10);
					Filter();
					_delay_ms(10);
				
					X_Move_Startpoint(CCW);

					break;
					/*
					Compare_Dis();
					if( WRONG_SIG == 0 )
					{			
						break;					//wonder the closest repeat sentence ..while(1)? yeap!
					}
					*/
				}	
				_delay_ms(10);
				///////////////////////////// X_sensing and return until this line
				Y_Move_Simple(CCW);
				
				if( BREAK_NUM1 == 1 )
				{
					BREAK_NUM1 = 0;
					
					X_Move_Startpoint(CCW);
					_delay_ms(10);
					
					for(cnt=0; cnt<200; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					for(cnt=0; cnt<210; cnt++)
					{
						X_Move_deg(CW);
						SENSING_CW[cnt] = Dis;
					}
					
					_delay_ms(10);
					Filter();
					_delay_ms(10);
					
					X_Move_Startpoint(CCW);

					//X_Move_Startpoint(CCW);
					
					lcd_iw(0x01);
					lcd_str(str8);	//100% Done
					
					Y_Move_Startpoint();
					_delay_ms(10);
					
					Uart_Putch(0,SIG_To2[2]);	//sig to2 : laser off

					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);	//laser off	Complete
					_delay_ms(1000);
					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);	//laser off	Complete
					_delay_ms(1000);
					lcd_iw(0x01), lcd_str(str9), lcd_iw(0xc0), lcd_str(str10);	//laser off	Complete

					break;
				}
			}
		}
		
		//------------------------------------------------------------------------------ 
		//		=== X_MOVE_LEFT ===
		//------------------------------------------------------------------------------
		else if( Instruction[2] == 1 )
		{
			Instruction[2] = 0;
			
			X_Move_Startpoint(CCW);
			_delay_ms(3);
			//X_Move_Startpoint();
			//_delay_ms(3);
			
		}
		
		//------------------------------------------------------------------------------ 
		//		=== X_MOVE_RIGHT ===
		//------------------------------------------------------------------------------
		else if( Instruction[3] == 1 )
		{	
			Instruction[3] = 0;
			X_Move_Startpoint(CW);
			_delay_ms(3);
		}
		/////////////////////////////////////////////////////////////////////////////
		else if(Instruction[4] == 1)
		{	
			Instruction[4] = 0;
			//Data_to_PC();
			
					/*
					for(i=1 ;i<6 ;i++)
					{
						Uart_Putch(1,arr[i]);
					}		
					*/
					for(ccnt=0;ccnt<10;ccnt++)
					{
						Height = 896;
						Percent[ccnt] = ((Height/80)*(ccnt+1));
					
						Percent10[ccnt] = Percent[ccnt]/10;
						Percent1[ccnt] = Percent[ccnt]%10;
						
						lcd_iw(0x01);
						lcd_str(str6);
						//lcd_iw(0xc0);
						lcd_dw(Percent10[ccnt]+48);
						lcd_dw(Percent1[ccnt]+48);
						lcd_dw('%');
						lcd_dw('>');
						_delay_ms(2000);
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
	

	Init_Ext_Interrupt(INT0);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7
	Init_Ext_Interrupt(INT1);	// 초기화_외부인터럽트0/1/2/3/4/5/6/7

    Init_Uart(UART0,9600);  		// 초기화_시리얼통신0
	Init_Uart(UART1,9600);  	// 초기화_시리얼통신1
	Init_ADC();					// 초기화_ADC
	Init_Timer();	

	init_lcd();						
	Motor_Init();

	Enable_ISR();            	// 전체인터럽트 사용허가
}

void Compare_Dis(void)
{
	U16 cnt;

	for(cnt=0; cnt<200; cnt++)
	{
		if( SENSING_CW[cnt] > 80 )
		{
			WRONG_SIG = 1;
		}
	}
}

void Data_to_PC(void)
{
	U16 cnt;
	
	for(cnt=0;cnt<200;cnt++)
	{
		Uart_U16Bit_PutNum(1,SENSING_CW[cnt]);
	}
}

void Filter(void)
{
	U16 cnt;

	for(cnt=0;cnt<200;cnt++)
	{
		Filtering[cnt] = (SENSING_CW[cnt]+SENSING_CW[cnt+1]) / 2;
		if(cnt == 199)
		{
			Filtering[199] = (SENSING_CW[199]+SENSING_CW[0]) / 2	;
		}
	}
	for(cnt=0;cnt<200;cnt++)
	{
		Uart_U16Bit_PutNum(1,SENSING_CW[cnt]), Uart_U16Bit_PutNum(1,Filtering[cnt]);
	}
	
}


void lcd_iw(U08 inst) // LCD 명령출력함수.
{
	PORTG = 0x04; // LCD를명령쓰기모드로설정
	PORTD = inst & 0xf0; // 명령어상위4비트전송
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x04;
	PORTD = inst << 4; // 명령어하위4비트전송
	PORTG &= 0xfb; // LCD Disable
	_delay_ms(2);
}
void lcd_dw(U08 dw) // LCD 데이터출력함수.
{
	PORTG = 0x05; // LCD를데이터쓰기모드로설정
	PORTD = dw & 0xf0; // 데이터상위4비트전송	6,5,4, 핀에 101
	PORTG &= 0xfb; // LCD Disable (E=0)
	PORTG = 0x05;
	PORTD = dw << 4; // 데이터하위4비트전송
	PORTG &= 0xfb;
	_delay_us(40);
}
void init_lcd(void) // LCD 초기화
{
	DDRD = 0xf0; //포트D 상위4비트를출력으로설정
	DDRG = 0x07; //포트G 하위3비트를출력으로설정
	
	lcd_iw(0x20);
	lcd_iw(0x28); // FUNCTION SET	2행
	lcd_iw(0x06); // ENTRY MODE 	어드레드+1
	lcd_iw(0x0c); // DISPLAY ON 	lcd키고 커서점멸off
	lcd_iw(0x01); // ALL CLEAR
}

void lcd_str(S08 *str) // 문자열출력함수.
{
	U08 i;
	while(*str){		//while(null=0) 이라서 멈침 while(1)만 무한루프가 아니라 while(2,3,4~~~xxx)도 무한루프
	lcd_dw(*str++);
	for(i=0; i<10; i++)
	_delay_ms(1); // 시간지연.
}
}
