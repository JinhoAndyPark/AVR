/*==============================================================================
 *
 *   ANSI/VT100 Menu Module
 *
 *     	File Name   	: menu.h
 *    	Version        	: 1.0
 *    	Date           	: 2006.07.10
 * 		Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *     	MPU_Type       	: ATmega128(16MHz)
 *		Compiler		: IAR Eebedded Workbench 4.1
 *    	Modified       	: 2006.07.10 By Yoonseok Pyo
 *     	Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *    	All Rights Reserved.
 *
 *		NOTE : 이 모듈은 '이야기멀티'를 기반으로 작성하였으며 ANSI 규약과
 *			  VT100 터미널 규약을 기반으로 짜여져 있습니다.
==============================================================================*/

#ifndef _ANSI_MENU_H_
#define _ANSI_MENU_H_

//------------------------------------------------------------------------------
//                      	===== Funtion Prototype =====
//------------------------------------------------------------------------------

void View_MainMenu(void);
void View_Help(void);
void View_SubMenu01(void);


#endif
