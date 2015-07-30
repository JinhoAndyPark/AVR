/*==============================================================================
 *
 *  Ax Motor_Module
 *
 *        File Name      : ax_exampe.h
 *        Version        : 1.0
 *        Date           : 2006.12.29
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.12.96 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/

#ifndef __AX_EXAMPLE_H
#define __AX_SETTING_H

void ID_Setting(U8 bID, U8 cID);
void Baud_Setting(U8 ID, U8 BAUD);
void Ax_Test(U8 ID,U8 Position_H,U8 Position_L,U8 Spped_H, U8 Spped_L );
void Torque_Enable(U8 ID);
void Endless_Turn(U8 ID);
void Position_View(U8 ID);


#endif
