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


#ifndef __STEP_MOTOR_H
#define __STEP_MOTOR_H

//#define LEFT_ENABLE      sbi(PORTA,7) 
//#define LEFT_DISABLE     cbi(PORTA,7)
#define LEFT_CW			   sbi(PORTA,7) 
#define LEFT_CCW		   cbi(PORTA,7)	
//#define RIGHT_ENABLE 	   sbi(PORTA,7)
//#define RIGHT_DISABLE	   sbi(PORTA,7)
#define RIGHT_CW		   sbi(PORTA,1)
#define RIGHT_CCW		   cbi(PORTA,1)
#define HALF_MODE		   sbi(PORTA,3)	
#define FULL_MODE		   cbi(PORTA,3)
#define RESET_LOW		   sbi(PORTA,4)
#define RESET_HIGH		   cbi(PORTA,4)		////you need to change port
#define LEFT_MOVE

#define CW				0
#define CCW				1

#define XSTPULSEWIDE		5
#define YSTPULSEWIDE		850
//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Motor_Init(void);
void X_StepMotor_Move_1step( U08 Direction );
void Y_StepMotor_Move_1step( U08 Direction );
void X_Move_Startpoint(void);
void Y_Move_Simple( U08 Direction );
void Range_Out(U08 DIR);
void X_Move_Return(void);


#endif


