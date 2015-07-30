/*==============================================================================
 *
 *   Define Header File
 *
 *        File Name   		: Define.c
 *        Version        	: 1.4
 *        Date           	: 2005.07.02
 *        Author         	: Yoonseok Pyo (ROBIT 1th, Kwangwoon University)
 *        MPU_Type       	: ATmega128(16MHz)
 *        Modified       	: 2006.11.27 By Yoonseok Pyo
 *        Copyright(c) 2006 ROBIT, Kwangwoon University.
 *        All Rights Reserved.
 *
==============================================================================*/

#ifndef __DEFINE_H 
#define __DEFINE_H 
	
//------------------------------------------------------------------------------
//       				=== ��Ʈ���� ===
//------------------------------------------------------------------------------
#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT
#define 	tbi(PORTX , BitX)   PORTX &   (1 << BitX)	// TEST  BIT

//------------------------------------------------------------------------------
//            			=== ��ü���ͷ�Ʈ ���� ===
//------------------------------------------------------------------------------
#define 	Disable_ISR()    cbi(SREG, 7)				// ���ͷ�Ʈ ������
#define 	Enable_ISR()     sbi(SREG, 7)				// ���ͷ�Ʈ ����㰡

//------------------------------------------------------------------------------
//       				=== ��ũ�� ===
//------------------------------------------------------------------------------
#define 	MIN(a,b)	( (a<b) ? (a):(b) )			// �񱳸�ũ��(����������)
#define 	MAX(a,b)	( (a>b) ? (a):(b) )			// �񱳸�ũ��(ū������)

//------------------------------------------------------------------------------
//                   	=== ����� ���� ��� ===
//------------------------------------------------------------------------------
#define   	TRUE    	1 
#define   	true    	1 
#define   	FALSE   	0 
#define   	false   	0 

#define 	ON 		1
#define 	OFF 		0
#define 	_ON 		0
#define 	_OFF 		1

//------------------------------------------------------------------------------
//               		=== ����� ���� �ڷ��� ===
//------------------------------------------------------------------------------
typedef   signed  char    S8;					// �� �ڷ����� ���� ������ ������� �ʱ� �ٶ�
typedef unsigned  char    U8;					// �� �ڷ����� ���� ������ ������� �ʱ� �ٶ�
typedef   signed  char    S08;
typedef unsigned  char    U08;
typedef   signed   int    S16; 
typedef unsigned   int    U16; 
typedef   signed  long    S32; 
typedef unsigned  long    U32; 

typedef unsigned  char    BYTE;
typedef unsigned   int    WORD;

#endif 
