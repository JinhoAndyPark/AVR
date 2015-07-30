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
//             모터 초기화 설정
//------------------------------------------------------------------------------
void Motor_Init(void)
{
     MOTOR_OUTPUT_SETUP();         //PORTD제어 -> 스텝모터
     R_Value = 0;
     L_Value = 0;
     Robot.Timer_Constant[0]=0;
     Robot.Timer_Constant[1]=0;
     Robot.Acc_Left_Parameter=0;
     Robot.Acc_Right_Parameter=0;
}

//------------------------------------------------------------------------------
//             왼쪽 모터 최대 가속
//------------------------------------------------------------------------------
void Acc_MaxSpeed_Left(void)
{
     if(Robot.Acc_Left_Parameter < 150)      //(150=44678, 최고199=50000)
          Robot.Acc_Left_Parameter++;
     else 
          Robot.Acc_Left_Parameter = 150;
     
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             오른쪽 모터 최대 가속
//------------------------------------------------------------------------------
void Acc_MaxSpeed_Right(void)
{
     if(Robot.Acc_Right_Parameter < 150)     //(150=44678, 최고199=50000)
          Robot.Acc_Right_Parameter++;
     else
          Robot.Acc_Right_Parameter = 150;

     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             왼쪽 모터 가속
//------------------------------------------------------------------------------
void Acc_Left(U8 Acc_Parameter_Left)
{
     if(Robot.Acc_Left_Parameter < Acc_Parameter_Left)      //(150=44678, 최고199=50000)
          Robot.Acc_Left_Parameter++;
     else 
          Robot.Acc_Left_Parameter = Acc_Parameter_Left;
          
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             오른쪽 모터 가속
//------------------------------------------------------------------------------
void Acc_Right(U8 Acc_Parameter_Right)
{
     if(Robot.Acc_Right_Parameter < Acc_Parameter_Right)      //(150=44678, 최고199=50000)
          Robot.Acc_Right_Parameter++;
     else 
          Robot.Acc_Right_Parameter = Acc_Parameter_Right;
          
     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             왼쪽 모터 감속
//------------------------------------------------------------------------------
void Dec_Left(U8 Dec_Parameter_Left)
{
     if(Robot.Acc_Left_Parameter > Dec_Parameter_Left)      //(150=44678, 최고199=50000)
          Robot.Acc_Left_Parameter--;
     else 
          Robot.Acc_Left_Parameter = Dec_Parameter_Left;
          
     Robot.Timer_Constant[0] = Acc_Table[Robot.Acc_Left_Parameter];
}

//------------------------------------------------------------------------------
//             오른쪽 모터 감속
//------------------------------------------------------------------------------
void Dec_Right(U8 Dec_Parameter_Right)
{
     if(Robot.Acc_Right_Parameter > Dec_Parameter_Right)      //(150=44678, 최고199=50000)
          Robot.Acc_Right_Parameter--;
     else 
          Robot.Acc_Right_Parameter = Dec_Parameter_Right;
          
     Robot.Timer_Constant[1] = Acc_Table[Robot.Acc_Right_Parameter];
}

//------------------------------------------------------------------------------
//             오른쪽 스텝모터 : PORTD 상위비트  
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
//             왼쪽 스텝모터 : PORTD 하위비트  
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
//			타이머1 오버플로우 인터럽트 서비스 루틴
//			좌측 모터 제어
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
//			타이머3 오버플로우 인터럽트 서비스 루틴
//			우측 모터 제어
//------------------------------------------------------------------------------

#pragma vector=TIMER3_OVF_vect
__interrupt void Right_Motor_ISR( void )
{
     Disable_ISR();
	TCNT3 = Robot.Timer_Constant[1];
	R_Motor();
     Enable_ISR();
}
