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

#define   MOTOR_OUTPUT_SETUP()    DDRD = 0xFF;   PORTD = 0x00;


//------------------------------------------------------------------------------
//                            === ����� ���� ���� ===
//------------------------------------------------------------------------------
typedef struct
{
     U16 Timer_Constant[2];        // Ÿ�̸ӽû�� 0->T1/�������� 1->T3/��������
     
     U8 Acc_Left_Parameter;        // �������̺� �������� ����
     U8 Acc_Right_Parameter;       // �������̺� �������� ����
     
} DATA_OBJ;
extern DATA_OBJ  Robot;

//------------------------------------------------------------------------------
//                   2�� ���ڹ���� ���ܸ��� ���� �޽�
//
//           0  1  2  3         4  5  6  7
//   PORTD   25 26 27 28        29 30 31 32
//       (L) A  B  /A /B    (R) A  B  /A /B
//
//   1100 -> C           0011 1001
//   0110 -> 6           0110 1100
//   0011 -> 3           1100 0110
//   1001 -> 9           1001 0011
//                       (��) (��)
//------------------------------------------------------------------------------
//const U8 Step_Pulse[4] = {0xc9 , 0x63 , 0x36 , 0x9c};
//------------------------------------------------------------------------------
//                   2�� ���ڹ���� ���ܸ��� ���� �޽�
//
//           7  6  5  4         3  2  1  0
//   PORTD   32 31 30 29        28 29 28 27
//       (L) A  B  /A /B    (R) A  B  /A /B
//
//   1100 -> C           0011 1001
//   0110 -> 6           0110 1100
//   0011 -> 3           1100 0110
//   1001 -> 9           1001 0011
//                       (��) (��)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                       ===== Funtion Prototype =====
//------------------------------------------------------------------------------
void Motor_Init(void);
void Acc_MaxSpeed_Left(void);
void Acc_MaxSpeed_Right(void);
void Acc_Left(U8 Acc_Parameter_Left);
void Acc_Right(U8 Acc_Parameter_Right);
void Dec_Left(U8 Acc_Parameter_Left);
void Dec_Right(U8 Dec_Parameter_Right);
void R_Motor(void);
void L_Motor(void);

#endif


