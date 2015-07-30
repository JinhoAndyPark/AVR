/*==============================================================================
 *
 *   ANSI/VT100 Menu Module
 *
 *     	File Name   	: menu.c
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

//------------------------------------------------------------------------------
//                 			=== Include Headerfile ===
//------------------------------------------------------------------------------
#include <iom128.h>
#include "../define.h"
#include "ansi_menu.h"
#include "ansi.h"
#include "../AVRLIB/uart.h"

//------------------------------------------------------------------------------
//                   		=== Variable Declaration ===
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------ 
//				===== 메인메뉴 =====
//------------------------------------------------------------------------------
void View_MainMenu(void)
{
 	ANSI_ClearScreen(ALL);					// 터미널 전체 클리어
    ANSI_Normal();
    ANSI_Line(1);
    ANSI_Line(2);
    ANSI_Line(3);
    ANSI_Line(4); 
    ANSI_Line(5);
    ANSI_Line(6);     
    ANSI_Line(7); 
    ANSI_Line(8);  
    
    ANSI_GotoXY(5,3);
    Uart_Print(UART1,"■■■■■■■■■■\n");
    ANSI_GotoXY(5,4);
    Uart_Print(UART1,"■                ■■■■■■■■■■\n");
    ANSI_GotoXY(5,5);
    Uart_Print(UART1,"■    광운대학교                    ■■■\n");
   	ANSI_GotoXY(5,6);
    Uart_Print(UART1,"■■■         로보트연구회(ROLAB)      ■\n");
    ANSI_GotoXY(5,7);
    Uart_Print(UART1,"──■■■                              ■\n");    
    ANSI_GotoXY(5,8);
    Uart_Print(UART1,"────■■■■■■■■■■■■■■■■■\n");
    
    ANSI_Line(9);
    ANSI_Line(10);
	
    ANSI_Reverse(1);
	ANSI_GotoXY(57,4);
    Uart_Print(UART1," KwangWoon University \r\n"); 
    ANSI_GotoXY(58,6);
    Uart_Print(UART1," Robotics Laboratory \r\n");     
	ANSI_GotoXY(67,8);
    Uart_Print(UART1," SINCE 1985 \r\n"); 
    ANSI_Reverse(0);
    
    ANSI_Normal();
            
    ANSI_GotoXY(41,12);
    Uart_Print(UART1,"◆◆◆  ◆◆◆  ◆        ◆    ◆◆◆");
    ANSI_GotoXY(41,13);
    Uart_Print(UART1,"◆  ◆  ◆  ◆  ◆      ◆  ◆  ◆  ◆");
    ANSI_GotoXY(41,14);
    Uart_Print(UART1,"◆◆◆  ◆  ◆  ◆      ◆◆◆  ◆◆  ");
    ANSI_GotoXY(41,15);
    Uart_Print(UART1,"◆◆    ◆  ◆  ◆      ◆  ◆  ◆  ◆");
    ANSI_GotoXY(41,16);
    Uart_Print(UART1,"◆  ◆  ◆◆◆  ◆◆◆  ◆  ◆  ◆◆◆");
    ANSI_GotoXY(41,18);
    Uart_Print(UART1,"                       로랩19기 표윤석");
    

    ANSI_GotoXY(6,12);
    Uart_Print(UART1, "========== M E N U ==========");
    ANSI_GotoXY(5,14);
    Uart_Print(UART1," 1. 프로그램       6. 프로그램 ");
    ANSI_GotoXY(5,15);
    Uart_Print(UART1," 2. 프로그램       7. 프로그램 "); 
    ANSI_GotoXY(5,16);
    Uart_Print(UART1," 3. 프로그램       8. 프로그램 ");
    ANSI_GotoXY(5,17);
    Uart_Print(UART1," 4. 프로그램       9. 프로그램 ");
    ANSI_GotoXY(5,18);
    Uart_Print(UART1," 5. 프로그램       0. 프로그램 ");

    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  이전(B)   다음(N)   처음(S)   도움말(H)   종료(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"명령어 >");
    ANSI_Normal();  

}

//------------------------------------------------------------------------------ 
//				===== Help =====
//------------------------------------------------------------------------------
void View_Help(void)
{
    ANSI_GotoXY(0,11);    
    ANSI_ClearScreen(FROM);
    
    ANSI_Normal();
      
    ANSI_GotoXY(5,12);    Uart_Print(UART1," [ HELP ] ");
    ANSI_GotoXY(5,14);    Uart_Print(UART1," ① 개발자 : 표윤석(ROLAB 19th)");
	ANSI_GotoXY(5,15);    Uart_Print(UART1," ② 소  속 : 광운대 로보트연구회");
    ANSI_GotoXY(5,16);    Uart_Print(UART1," ③ 버  전 : ANSI-MENU 1.0");
    ANSI_GotoXY(5,17);    Uart_Print(UART1," ④ 설  명 : ATmega128을 이용한 비쥬얼 메뉴구성");
    
    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  이전(B)   다음(N)   처음(S)   도움말(H)   종료(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"명령어 >");
    ANSI_Normal(); 
}   

//------------------------------------------------------------------------------ 
//				===== Sub Menu 01 =====
//------------------------------------------------------------------------------
void View_SubMenu01(void)
{
    ANSI_GotoXY(0,11);    
    ANSI_ClearScreen(FROM);
    
    ANSI_Normal();
    
    ANSI_GotoXY(41,12);
    Uart_Print(UART1,"◆◆◆  ◆◆◆  ◆        ◆    ◆◆◆");
    ANSI_GotoXY(41,13);
    Uart_Print(UART1,"◆  ◆  ◆  ◆  ◆      ◆  ◆  ◆  ◆");
    ANSI_GotoXY(41,14);
    Uart_Print(UART1,"◆◆◆  ◆  ◆  ◆      ◆◆◆  ◆◆  ");
    ANSI_GotoXY(41,15);
    Uart_Print(UART1,"◆◆    ◆  ◆  ◆      ◆  ◆  ◆  ◆");
    ANSI_GotoXY(41,16);
    Uart_Print(UART1,"◆  ◆  ◆◆◆  ◆◆◆  ◆  ◆  ◆◆◆");
    ANSI_GotoXY(41,18);
    Uart_Print(UART1,"                       로랩19기 표윤석");
    
    ANSI_GotoXY(5,12);
    Uart_Print(UART1," [ MAIN MENU ] ");
    ANSI_GotoXY(5,14);
    Uart_Print(UART1," 1. 프로그램 ");

    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  이전(B)   다음(N)   처음(S)   도움말(H)   종료(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"명령어 >");
    ANSI_Normal(); 
}        
 

        

