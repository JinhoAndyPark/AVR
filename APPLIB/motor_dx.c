/*==============================================================================
 *
 *	Dynamixel Drive Module
 *
 *		File Name   	: motor_dx.c
 *   	Version        	: 1.3
 *    	Date           	: 2005.10.20
 *    	Author         	: Yoonseok Pyo (ROLAB 19th, Kwangwoon University)
 *    	MPU_Type       	: ATmega128(16MHz)
 *    	Modified       	: 2006.07.05 By Yoonseok Pyo
 *		Compiler		: IAR Eebedded Workbench 4.1
 *    	Copyright(c) 1985 - 2006 ROLAB, Kwangwoon University. 
 *     	All Rights Reserved.
 *
==============================================================================*/
//------------------------------------------------------------------------------
//	===== Description =====
// 	1. DX 모터 제어를 위한 모듈
// 	2. UART0 설정
//     	- 통신속도 1M bps
//		- 수신인터럽트 설정
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//                 			=== Include Headerfile ===
//------------------------------------------------------------------------------
#include <iom128.h>
#include "../define.h"
#include "../AVRLIB/uart.h"
#include "motor_dx.h"


//------------------------------------------------------------------------------
//					===== Gloval Variable Number =====
//------------------------------------------------------------------------------
volatile U8 RxInterruptBuffer[256];		// 수신인터럽트버퍼 
volatile U8 RxBufferWritePointer;		// 수신버퍼쓰기포인터
U8 RxBufferReadPointer;					// 수신버퍼읽기포인터
U8 Parameter[128];						// 매개변수
U8 RxBuffer[128]; 						// 수신버퍼
U8 TxBuffer[128]; 						// 송신버퍼

//------------------------------------------------------------------------------
//									== TxPacket ==
// 통신방식 = RS485 
// 매개변수 = ID, Instruction, Length of Parameters.
//
// 0xFF -> 0xFF -> ID -> LENGTH -> Instruction -> Parameters (1 ~ N) -> CheckSum
//------------------------------------------------------------------------------
U8 TxPacket(U8 ID, U8 Instruction, U8 ParameterLength) 
{
    //--------------------------------------------------------------------------
    //		===== 패킷 생성 =====
    //--------------------------------------------------------------------------
    
    U8 Count;					// 패킷의 전송 번호
    U8 CheckSum;				// 패킷의 오류 검출 방법
    U8 PacketLength;			// 매개변수들의 총 갯수
	
	TxBuffer[0] = 0xff;						// Start CODE
	TxBuffer[1] = 0xff;						// Start CODE
	TxBuffer[2] = ID;						// 모터ID (0~253), BroadcastingID=0xFE
	TxBuffer[3] = ParameterLength + 2;		// Length(Instruction + ParamterLength + Checksum)
	TxBuffer[4] = Instruction;				// 명령어 선택(단일쓰기,다중쓰기,읽기 등)
	
	for(Count = 0; Count < ParameterLength; Count++)
	{
		TxBuffer[Count+5] = Parameter[Count];			// 매개변수 지정
	}
	
    CheckSum = 0;										// CheckSum 초기화
	PacketLength = ParameterLength + 4 + 2;				// 패킷의 전체 길이 설정
	
	for(Count = 2; Count < PacketLength-1; Count++)  	// Except 0xFF, Checksum
	{
		CheckSum += TxBuffer[Count];
	}
	
	TxBuffer[Count] = ~CheckSum;                       	// Checksum 생성

    //--------------------------------------------------------------------------    
    //		===== 패킷 전송 =====
    //--------------------------------------------------------------------------   
    
	RS485_TXD;                                         	// RS485 출력모드로 설정
	
    for(Count = 0; Count < PacketLength; Count++)
	{
		sbi(UCSR0A,6);						     		// 송신완료 상태로 전환
		Uart_Putch( UART0,(TxBuffer[Count]) );         	// 순차적 패킷전송 MCU->DX
	}
	
	while(!CHECK_TXD0_FINISH);                         	// 송신버퍼 빌때까지 기다림
	RS485_RXD;                                         	// RS485 입력모드로 설정
	
	return(PacketLength);								// 패킷의 전체길이 리턴
}

//------------------------------------------------------------------------------
//									== RxPacket ==
// 통신방식 = RS485 
// 필요한 파라미터 = Total Length of Return Packet.
//------------------------------------------------------------------------------
U8 RxPacket(U8 RxPacketLength)
{
	#define RX_TIMEOUT_COUNT2   3000L  
	#define RX_TIMEOUT_COUNT1  (RX_TIMEOUT_COUNT2 * 10L)  

	U32 Counter;					// 전송시간 측정 변수
	U8  Timeout;					// 전송오류 시간설정
    
    U8  Count;						// 패킷의 수신 번호
    U8 	Length;						// Length(Instruction + ParamterLength + Checksum)
    U8	Checksum;					// 패킷의 오류 검출 방법


	Timeout = 0;
    
	for(Count = 0; Count < RxPacketLength; Count++)
	{
		Counter = 0;

        while(RxBufferReadPointer == RxBufferWritePointer)
		{
			if(Counter++ > RX_TIMEOUT_COUNT1)		
			{
				Timeout = 1;	// 전송 타이밍 에러 발생
				break;
			}
		}
        
		if(Timeout) 
            break;
        
        // 수신된 데이터를 수신버퍼에 저장
		RxBuffer[Count] = RxInterruptBuffer[RxBufferReadPointer++];
	}
    
	Length = Count;
	Checksum = 0;

	if(TxBuffer[2] != BROADCASTING_ID)
	{
		if(Timeout && RxPacketLength != 255) 
		{
            //----- 에러01 : 전송 타이밍 에러
			Uart_Print(UART1,"\r\n [Error:RxD Timeout]");
			CLEAR_BUFFER;
		}
	
		if(Length > 3)
		{
			if(RxBuffer[0] != 0xff || RxBuffer[1] != 0xff ) 
			{
                //----- 에러02 : 스타트 코드
				Uart_Print(UART1,"\r\n [Error:Wrong Header]");
				CLEAR_BUFFER;
				return 0;
			}
			if(RxBuffer[2] != TxBuffer[2] )
			{
                //----- 에러03 : 타셋 ID
				Uart_Print(UART1,"\r\n [Error:TxID != RxID]");
				CLEAR_BUFFER;
				return 0;
			}  
			if(RxBuffer[3] != Length-4) 
			{
                //----- 에러04 : 패킷의 길이
				Uart_Print(UART1,"\r\n [Error:Wrong Length]");
				CLEAR_BUFFER;
				return 0;
			}  
			
			for(Count = 2; Count < Length; Count++) 
				Checksum += RxBuffer[Count];
			
			if(Checksum != 0xff) 
			{
                //----- 에러05 : CheckSum 문제
				Uart_Print(UART1,"\r\n [Error:Wrong CheckSum]");
				CLEAR_BUFFER;
				return 0;
			}
		}
	}
	
    return Length;
}

//------------------------------------------------------------------------------
