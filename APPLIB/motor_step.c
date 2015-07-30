/*==============================================================================
 *
 *   Step Motor Drive
 *
 *        File Name      : Step_Motor.c
 *        Version        : 1.0
 *        Date           : 2005.12.10
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Add Description: SST42D1100 / SLA7026M
 *        Modified       : 2005.12.11 By P.Y.S
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/

#include <iom128.h>
#include "../Define.h"
#include "motor_step.h"
#include "motor_step_table.h"


const U8 Step_Pulse[4] = {0x9C , 0x36 , 0x63 , 0xC9};
U8 R_Value;
U8 L_Value;

DATA_OBJ  Robot;

//------------------------------------------------------------------------------
//             ���� �ʱ�ȭ ����
//------------------------------------------------------------------------------
void Motor_Init(void)
{
     MOTOR_OUTPUT_SETUP();         //PORTD���� -> ���ܸ���
     R_Value = 0;
     L_Value = 0;
     Robot.Timer_Constant[0]=0;
     Robot.Timer_Constant[1]=0;
     Robot.Acc_Left_Parameter=0;
     Robot.Acc_Right_Parameter=0;
}

//------------------------------------------------------------------------------
//             ���� ���� �ִ� ����
//------------------------------------------------------------------------------
void Acc_MaxSpeed_Left(void)
{
     if(Robot.Acc_Left_Parameter < 150)      //(150=44678, �ְ�199=50000)
          Robot.Acc_Left_Parameter++;
     else 
          Robot.Acc_Left_Parameter = 150;
     
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             ������ ���� �ִ� ����
//------------------------------------------------------------------------------
void Acc_MaxSpeed_Right(void)
{
     if(Robot.Acc_Right_Parameter < 150)     //(150=44678, �ְ�199=50000)
          Robot.Acc_Right_Parameter++;
     else
          Robot.Acc_Right_Parameter = 150;

     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             ���� ���� ����
//------------------------------------------------------------------------------
void Acc_Left(U8 Acc_Parameter_Left)
{
     if(Robot.Acc_Left_Parameter < Acc_Parameter_Left)      //(150=44678, �ְ�199=50000)
          Robot.Acc_Left_Parameter++;
     else 
          Robot.Acc_Left_Parameter = Acc_Parameter_Left;
          
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             ������ ���� ����
//------------------------------------------------------------------------------
void Acc_Right(U8 Acc_Parameter_Right)
{
     if(Robot.Acc_Right_Parameter < Acc_Parameter_Right)      //(150=44678, �ְ�199=50000)
          Robot.Acc_Right_Parameter++;
     else 
          Robot.Acc_Right_Parameter = Acc_Parameter_Right;
          
     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             ���� ���� ����
//------------------------------------------------------------------------------
void Dec_Left(U8 Dec_Parameter_Left)
{
     if(Robot.Acc_Left_Parameter > Dec_Parameter_Left)      //(150=44678, �ְ�199=50000)
          Robot.Acc_Left_Parameter--;
     else 
          Robot.Acc_Left_Parameter = Dec_Parameter_Left;
          
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             ������ ���� ����
//------------------------------------------------------------------------------
void Dec_Right(U8 Dec_Parameter_Right)
{
     if(Robot.Acc_Right_Parameter > Dec_Parameter_Right)      //(150=44678, �ְ�199=50000)
          Robot.Acc_Right_Parameter--;
     else 
          Robot.Acc_Right_Parameter = Dec_Parameter_Right;
          
     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             ������ ���ܸ��� : PORTD ������Ʈ  
//             PORTD 29 30 31 32
//                   A  B  /A /B 
//------------------------------------------------------------------------------
void R_Motor(void)
{
	PORTD = (Step_Pulse[R_Value] & 0xf0)+(PORTD & 0x0f); 		//R_motor
	R_Value++;
	if(R_Value==4)
		R_Value=0;
}

//------------------------------------------------------------------------------
//             ���� ���ܸ��� : PORTD ������Ʈ  
//             PORTD 25 26 27 28
//                   A  B  /A /B 
//------------------------------------------------------------------------------

void L_Motor(void)
{
	PORTD = (Step_Pulse[L_Value] & 0x0f)+(PORTD & 0xf0); 		//L_motor
	L_Value++;
	if(L_Value==4)
		L_Value=0;
}


//------------------------------------------------------------------------------
//			Ÿ�̸�1 �����÷ο� ���ͷ�Ʈ ���� ��ƾ
//			���� ���� ����
//------------------------------------------------------------------------------

#pragma vector=TIMER1_OVF_vect
__interrupt void Left_Motor_ISR( void )
{
     Disable_ISR();
	TCNT1 = Robot.Timer_Constant[0];
     L_Motor();
     Enable_ISR();
}


//------------------------------------------------------------------------------
//			Ÿ�̸�3 �����÷ο� ���ͷ�Ʈ ���� ��ƾ
//			���� ���� ����
//------------------------------------------------------------------------------

#pragma vector=TIMER3_OVF_vect
__interrupt void Right_Motor_ISR( void )
{
     Disable_ISR();
	TCNT3 = Robot.Timer_Constant[1];
	R_Motor();
     Enable_ISR();
}
