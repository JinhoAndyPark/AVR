/*==============================================================================
 *
 *   Ir_Remocon_Data Module
 *
 *        File Name      : data_ir.h
 *        Version        : 1.2
 *        Date           : 2006.02.11
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.02.11 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#ifndef __IRDA_LIB_H
#define __IRDA_LIB_H

void Ir_Data_Init(void);
void Ir_Data_Key(U8 Data);
void Ir_Data_Key_Change(void);
void Ir_Data_Clear(void);
void Ir_Data_Check(void);
void Ir_Data_Read(void);
void Ir_Main(void);
void Init_Ext(void);
void Init_Timer(void);

#endif

