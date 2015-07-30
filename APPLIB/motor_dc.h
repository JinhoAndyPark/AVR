/*==============================================================================
 *
 *   L298 Driver Module
 *
 *        File Name      : motor_dc.h
 *        Version        : 1.0
 *        Date           : 2006.06.08
 *        Author         : Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 * 		  Compiler		 : IAR Eebedded Workbench 4.1
 *        Modified       : 2006.06.08 By Yoonseok Pyo
 *        Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *        All Rights Reserved.
 *
==============================================================================*/
//#ifndef __L298_H
//#define __L298_H

void Init_L298(void);
void Init_Timer(void);
void Forward(void);
void Back(void);
void Left(void);
void Right(void);
void Stop(void);	


//#endif
