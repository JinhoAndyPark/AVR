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
#include "main.h"		// ���α׷��� ������� ����

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------

#define vel_Kp	1.5
#define vel_Ki	0.2
#define	vel_Kd	0.05

#define pos_Kp	0.9
#define pos_Ki	0.01
#define	pos_Kd	0.05

extern U16 nFND;

S16 test_vel_cnt=0;
S16 test_pos_cnt=0;
S08 test_ocr=0;
U08 data;

S16 TMR_10ms_CNT=0;

S16 temp_vel_cnt=0, ECD_RPM_cnt=0, nRPM=0;

S16 vel_err=0, vel_err_sum=0,vel_err_div=0,vel_err_old=0;
S16 vel_target = 100;
S16 vel_PWM = 0;

S16 pos_err=0, pos_err_sum=0,pos_err_div=0,pos_err_old=0;
S16 pos_target = 0;
S16 pos_dir=0;


//------------------------------------------------------------------------------
//                   		=== Interrupt Service Routine ===
//------------------------------------------------------------------------------
ISR(TIMER1_OVF_vect)	//1//1ms
{
	TCNT1 = 65285;
	Display_FND_ISR();
	temp_vel_cnt++;
	//if(temp_vel_cnt > 3000)	nRPM = 0;
	TMR_10ms_CNT++;
	if(TMR_10ms_CNT >= 10)
	{
		TMR_10ms_CNT = 0;
		
		/*velocity PID
		vel_err_sum += vel_err;
		vel_err = vel_target - nRPM;
		vel_err_div = vel_err - vel_err_old;
		vel_PWM = (float)(vel_Kp*vel_err) + (float)(vel_Ki*vel_err_sum) + (float)(vel_Kd*vel_err_div);
		if(vel_PWM<0)	vel_PWM=0;
		Spin_Positive(vel_PWM);
		vel_err_old = vel_err;
		*/
		
		pos_err_sum += pos_err;
		pos_err = pos_target - test_pos_cnt;
		pos_dir = (float)(pos_Kp*pos_err) + (float)(pos_Ki*pos_err_sum);
		if(pos_dir<0)	Spin_Negative(20);
		else	Spin_Positive(20);
		
		//else Spin_Stop();
	}
}

ISR(INT0_vect)
{
	if(Check_Dir() == 0)	test_pos_cnt--;
	else					test_pos_cnt++;

	test_vel_cnt++;

	if(test_vel_cnt >= 19)
	{
		ECD_RPM_cnt = temp_vel_cnt;
		temp_vel_cnt = 0;
		test_vel_cnt = 0;

		nRPM = 3000 / ECD_RPM_cnt;
	}
}

ISR(USART0_RX_vect)
{
	Disable_ISR();

	data = UDR0;
	Enable_ISR();
}

//------------------------------------------------------------------------------
//                      	=== Main Function ===
//------------------------------------------------------------------------------
void main(void)
{ 
	Init_Main();		// �ʱ�ȭ_MCU
	
	
	while(1)
	{         
	//--------------------------------------------------------------------------
	//		=== Function Module ===
	//--------------------------------------------------------------------------
		Uart_Print(0, "\r\n");
		Uart_U16Bit_PutNum(0,pos_dir);
		Uart_Print(0, "		");
		Uart_U16Bit_PutNum(0,test_pos_cnt);
		Uart_Print(0, "		");
		Uart_U16Bit_PutNum(0,vel_err_sum);
		_delay_ms(500);
		Display_FND();
		//nFND = ADC_Average( 0, 20 );
		nFND = nRPM;
		if(data == '1')
		{
			SPIN_POSITIVE();
			data = 0;
		}
		else if(data == '2')
		{
			SPIN_NEGATIVE();
			data = 0;
		}
		else if(data == 'a')
		{
			test_ocr += 10;
			data = 0;
		}
		else if(data == 'd')
		{
			test_ocr -= 10;
			data = 0;
		}
		else if(data == 'p')
		{
			pos_target+= 50;
			data = 0;
		}
		else if(data == 'o')
		{
			pos_target-= 50;
			data = 0;
		}
		//OCR0 = test_ocr;
		//if(test_cnt >= 380) Spin_Stop();
		//else Spin_Positive(17);
		//Spin_Positive(ADC_Average( 0, 20 ));
	//--------------------------------------------------------------------------    
	}
}


//------------------------------------------------------------------------------
//                       	=== Initialize Function ===
//------------------------------------------------------------------------------
void Init_Main(void)
{
	Disable_ISR();           	// ��ü���ͷ�Ʈ ������
	 
	//Init_IO();				// �ʱ�ȭ_�������Ʈ	
	Init_Ext_Interrupt(INT0);	// �ʱ�ȭ_�ܺ����ͷ�Ʈ0/1/2/3/4/5/6/7
	Init_Timer();				// �ʱ�ȭ_Ÿ�̸�0/1/2/3
    Init_Uart(0,57600);  		// �ʱ�ȭ_�ø������0
	//Init_Uart(UART1,57600);  	// �ʱ�ȭ_�ø������1
	Init_ADC();				// �ʱ�ȭ_ADC
    //Init_SPI(MASTER);			// �ʱ�ȭ_SPI��� 
	//Init_TWI(MASTER);			// �ʱ�ȭ_TWI���

	Init_Dynamic_FND();
	Init_DCmotor_Control();
	Init_Encoder();
    
	Enable_ISR();            	// ��ü���ͷ�Ʈ ����㰡
}

//------------------------------------------------------------------------------ 
//		=== Function Module ===
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
