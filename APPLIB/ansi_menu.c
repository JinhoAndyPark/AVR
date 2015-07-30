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
 *		NOTE : �� ����� '�̾߱��Ƽ'�� ������� �ۼ��Ͽ����� ANSI �Ծ��
 *			  VT100 �͹̳� �Ծ��� ������� ¥���� �ֽ��ϴ�.
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
//				===== ���θ޴� =====
//------------------------------------------------------------------------------
void View_MainMenu(void)
{
 	ANSI_ClearScreen(ALL);					// �͹̳� ��ü Ŭ����
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
    Uart_Print(UART1,"�����������\n");
    ANSI_GotoXY(5,4);
    Uart_Print(UART1,"��                �����������\n");
    ANSI_GotoXY(5,5);
    Uart_Print(UART1,"��    ������б�                    ����\n");
   	ANSI_GotoXY(5,6);
    Uart_Print(UART1,"����         �κ�Ʈ����ȸ(ROLAB)      ��\n");
    ANSI_GotoXY(5,7);
    Uart_Print(UART1,"��������                              ��\n");    
    ANSI_GotoXY(5,8);
    Uart_Print(UART1,"��������������������������\n");
    
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
    Uart_Print(UART1,"�ߡߡ�  �ߡߡ�  ��        ��    �ߡߡ�");
    ANSI_GotoXY(41,13);
    Uart_Print(UART1,"��  ��  ��  ��  ��      ��  ��  ��  ��");
    ANSI_GotoXY(41,14);
    Uart_Print(UART1,"�ߡߡ�  ��  ��  ��      �ߡߡ�  �ߡ�  ");
    ANSI_GotoXY(41,15);
    Uart_Print(UART1,"�ߡ�    ��  ��  ��      ��  ��  ��  ��");
    ANSI_GotoXY(41,16);
    Uart_Print(UART1,"��  ��  �ߡߡ�  �ߡߡ�  ��  ��  �ߡߡ�");
    ANSI_GotoXY(41,18);
    Uart_Print(UART1,"                       �η�19�� ǥ����");
    

    ANSI_GotoXY(6,12);
    Uart_Print(UART1, "========== M E N U ==========");
    ANSI_GotoXY(5,14);
    Uart_Print(UART1," 1. ���α׷�       6. ���α׷� ");
    ANSI_GotoXY(5,15);
    Uart_Print(UART1," 2. ���α׷�       7. ���α׷� "); 
    ANSI_GotoXY(5,16);
    Uart_Print(UART1," 3. ���α׷�       8. ���α׷� ");
    ANSI_GotoXY(5,17);
    Uart_Print(UART1," 4. ���α׷�       9. ���α׷� ");
    ANSI_GotoXY(5,18);
    Uart_Print(UART1," 5. ���α׷�       0. ���α׷� ");

    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  ����(B)   ����(N)   ó��(S)   ����(H)   ����(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"��ɾ� >");
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
    ANSI_GotoXY(5,14);    Uart_Print(UART1," �� ������ : ǥ����(ROLAB 19th)");
	ANSI_GotoXY(5,15);    Uart_Print(UART1," �� ��  �� : ����� �κ�Ʈ����ȸ");
    ANSI_GotoXY(5,16);    Uart_Print(UART1," �� ��  �� : ANSI-MENU 1.0");
    ANSI_GotoXY(5,17);    Uart_Print(UART1," �� ��  �� : ATmega128�� �̿��� ����� �޴�����");
    
    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  ����(B)   ����(N)   ó��(S)   ����(H)   ����(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"��ɾ� >");
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
    Uart_Print(UART1,"�ߡߡ�  �ߡߡ�  ��        ��    �ߡߡ�");
    ANSI_GotoXY(41,13);
    Uart_Print(UART1,"��  ��  ��  ��  ��      ��  ��  ��  ��");
    ANSI_GotoXY(41,14);
    Uart_Print(UART1,"�ߡߡ�  ��  ��  ��      �ߡߡ�  �ߡ�  ");
    ANSI_GotoXY(41,15);
    Uart_Print(UART1,"�ߡ�    ��  ��  ��      ��  ��  ��  ��");
    ANSI_GotoXY(41,16);
    Uart_Print(UART1,"��  ��  �ߡߡ�  �ߡߡ�  ��  ��  �ߡߡ�");
    ANSI_GotoXY(41,18);
    Uart_Print(UART1,"                       �η�19�� ǥ����");
    
    ANSI_GotoXY(5,12);
    Uart_Print(UART1," [ MAIN MENU ] ");
    ANSI_GotoXY(5,14);
    Uart_Print(UART1," 1. ���α׷� ");

    ANSI_Line(21);
    ANSI_GotoXY(0,22);
    Uart_Print(UART1,"|  ����(B)   ����(N)   ó��(S)   ����(H)   ����(Q)  |");    
    ANSI_Line(23); 
    ANSI_GotoXY(0,24);
    Uart_Print(UART1,"��ɾ� >");
    ANSI_Normal(); 
}        
 

        

