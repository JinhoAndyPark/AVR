/*==============================================================================
 *
 *   Define Header File
 *
 *    	File Name   	: define.c
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

#ifndef __DEFINE_H 
#define __DEFINE_H 
	
//------------------------------------------------------------------------------
//       			=== ��Ʈ���� ===
//------------------------------------------------------------------------------
#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT

//------------------------------------------------------------------------------
//            			=== ��ü���ͷ�Ʈ ���� ===
//------------------------------------------------------------------------------
#define 	Disable_ISR()    cbi(SREG, 7)			// ���ͷ�Ʈ ������
#define 	Enable_ISR()     sbi(SREG, 7)			// ���ͷ�Ʈ ����㰡

//------------------------------------------------------------------------------
//               		=== ����� ���� �ڷ��� ===
//------------------------------------------------------------------------------
typedef   signed  char    S08;
typedef unsigned  char    U08;
typedef   signed   int    S16;
typedef unsigned   int    U16;
typedef   signed  long    S32;
typedef unsigned  long    U32;

typedef unsigned  char    BYTE;
typedef unsigned   int    WORD;

#endif 
