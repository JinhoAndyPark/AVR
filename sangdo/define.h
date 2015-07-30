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
//       				=== 비트제어 ===
//------------------------------------------------------------------------------
#define 	sbi(PORTX , BitX)   PORTX |=  (1 << BitX)	// SET   BIT
#define 	cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)	// CLEAR BIT
#define 	tbi(PORTX , BitX)   PORTX &   (1 << BitX)	// TEST  BIT

//------------------------------------------------------------------------------
//            			=== 전체인터럽트 설정 ===
//------------------------------------------------------------------------------
#define 	Disable_ISR()    cbi(SREG, 7)				// 인터럽트 사용금지
#define 	Enable_ISR()     sbi(SREG, 7)				// 인터럽트 사용허가

//------------------------------------------------------------------------------
//       				=== 매크로 ===
//------------------------------------------------------------------------------
#define 	MIN(a,b)	( (a<b) ? (a):(b) )			// 비교매크로(작은값검출)
#define 	MAX(a,b)	( (a>b) ? (a):(b) )			// 비교매크로(큰값검출)

//------------------------------------------------------------------------------
//                   	=== 사용자 정의 상수 ===
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
//               		=== 사용자 정의 자료형 ===
//------------------------------------------------------------------------------
typedef   signed  char    S8;					// 이 자료형은 삭제 검토중 사용하지 않기 바람
typedef unsigned  char    U8;					// 이 자료형은 삭제 검토중 사용하지 않기 바람
typedef   signed  char    S08;
typedef unsigned  char    U08;
typedef   signed   int    S16; 
typedef unsigned   int    U16; 
typedef   signed  long    S32; 
typedef unsigned  long    U32; 

typedef unsigned  char    BYTE;
typedef unsigned   int    WORD;

#endif 
