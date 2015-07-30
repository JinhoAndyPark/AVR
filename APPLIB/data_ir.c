/*==============================================================================
 *
 *   Ir_Remocon_Data Module
 *
 *        File Name      : data_ir.c
 *        Version        : 1.3
 *        Date           : 2006.02.11
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.02.11 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#include <iom128.h>
#include "../define.h"
#include "data_ir.h"

U8 Ir_Key_Value;
U8 Ir_Data_Code1;
U8 Ir_Data_Code2;
U8 Ir_Data[];

volatile U8 Ir_Code_Count;
volatile U8 Ir_Int_Count;
volatile U8 Ir_Bit_Start;
volatile U8 Ir_Time_Count;

void Ir_Data_Init(void)
{
     DDRA = 0xff;		// 값 확인용 LED 포트
     Ir_Int_Count = 0;
     Ir_Code_Count = 0;
     Ir_Bit_Start = false;
     Ext_Init();
     Timer_Init();
}
void Init_Timer(void)
{
     sbi( TIMSK, 0 );    //타이머0번 사용 Overflow Interrupt 인에이블
     sbi( TCCR0, 1 );    //8분주 사용
     TCNT0 = 56;
}
void Init_Ext(void)
{
     sbi(EIMSK, 4);  //외부인터럽트 4번사용
     sbi(EICRB, 1);    //폴링엣지 사용
     cbi(EICRB, 0);
}
#pragma vector=TIMER0_OVF_vect     	// 타이머  Overflow 인터럽트 처리 루틴
__interrupt void OVF_Interrupt( void )
{
     Disable_ISR();
     Ir_Int_Count++;
     sbi( TCCR0, 1 );
     TCNT0=56;            //100us로 만들어줌
     Enable_ISR();
}
#pragma vector=INT4_vect    			        // INT4 인터럽트 처리 루틴
__interrupt void INT4_Interrupt( void )
{
     Disable_ISR();
     Ir_Time_Count = Ir_Int_Count;      //타이머 카운트 인터럽트 값 대입
     Ir_Bit_Start = true;          //수신값 들어오면 true
     Ir_Main();
     Ir_Int_Count = 0;
     Enable_ISR();
}

void Ir_Data_Read(void)
{
     if((7<Ir_Time_Count)&&(Ir_Time_Count<13))     //0값(1.125ms)
     {
          Ir_Data[Ir_Code_Count]=0;
          Ir_Code_Count++;
     }
     else if((18<Ir_Time_Count)&&(Ir_Time_Count<25))    //1값(2.5ms)
     {
          Ir_Data[Ir_Code_Count]=1;
          Ir_Code_Count++;
     }
     else if((80<Ir_Time_Count)&&(Ir_Time_Count<100))   //리드코드
     {
          Ir_Code_Count=0;
          Ir_Data_Clear();
     }
     else
     {
          Ir_Data_Clear();
          Ir_Code_Count=0;
     }
     if(Ir_Code_Count>31)          //데이터를 모두 읽었을경우 Ir_Data_Check함수로 이동
     {
          Ir_Data_Check();
          Ir_Data_Clear();
          Ir_Code_Count=0;
     }
}
void Ir_Data_Check(void)           //데이터 코드와 데이터 코드의 보수를 체크하여 데이터값을 넣음
{
     Ir_Data_Key_Change();
     if((Ir_Data_Code1 | Ir_Data_Code2)==0xff)
     {
          Ir_Data_Key(Ir_Data_Code1);
     }
}

void Ir_Data_Key_Change(void)      //비트 데이터를 바이트로 변경
{
     U8 bit;
     U8 byte;
     for(bit=16;bit<24;bit++)      //리모콘 데이터 값
     {
          byte = byte << 1;
          byte = byte | Ir_Data[bit];
     }
     Ir_Data_Code1 = byte;

     for(bit=24;bit<32;bit++)      //리모콘 데이터 보수 값
     {
          byte = byte << 1;
          byte = byte | Ir_Data[bit];
     }
     Ir_Data_Code2 = byte ;
     Ir_Data_Clear();
}

void Ir_Data_Key(U8 Data)
{
     Disable_ISR();
     switch(Data)
     {
          case 0x20:                    //1번키 값
                    Ir_Key_Value=0x01;
                    PORTA=0x01;
                    break;
          case 0xA0:                    //2번키 값
                    Ir_Key_Value=0x02;
                    PORTA=0x02;
                    break;
          case 0x60:                    //3번키 값
                    Ir_Key_Value=0x03;
                    PORTA=0x04;
                    break;
          case 0x10:                    //4번키 값
                    Ir_Key_Value=0x04;
                    PORTA=0x08;
                    break;
          case 0x90:                    //5번키 값
                    Ir_Key_Value=0x05;
                    PORTA=0x10;
                    break;
          case 0x50:                    //6번키 값
                    Ir_Key_Value=0x06;
                    PORTA=0x20;
                    break;
          case 0x30:                    //7번키 값
                    Ir_Key_Value=0x07;
                    PORTA=0x40;
                    break;
          case 0xB0:                    //8번키 값
                    Ir_Key_Value=0x08;
                    PORTA=0x80;
                    break;
          case 0x70:                    //9번키 값
                    Ir_Key_Value=0x09;
                    PORTA=0x03;
                    break;
          case 0x88:                    //0번키 값
                    Ir_Key_Value=0x10;
                    PORTA=0x06;
                    break;
          case 0x40:                    //전원키 값
                    Ir_Key_Value=0x00;
                    PORTA=0x00;
                    break;
          case 0xE0:                    //음량+키 값
                    Ir_Key_Value=0x0A;
                    PORTA=0x0A;
                    break;
          case 0xD0:                    //음량-키 값
                    Ir_Key_Value=0x0B;
                    PORTA=0x0B;
                    break;
          case 0x48:                    //채널+키 값
                    Ir_Key_Value=0x0C;
                    PORTA=0x0C;
                    break;
          case 0x08:                    //채널-키 값
                    Ir_Key_Value=0x0D;
                    PORTA=0x0D;
                    break;
     	  default:
                    Ir_Key_Value=0xff;
                    PORTA=0xff;
                    break;
     }
     Enable_ISR();
}

void Ir_Data_Clear(void)      //비트 데이터 버퍼 모두 클리어
{
     U8 bit;
     for(bit=0;bit<32;bit++)
     {
          Ir_Data[bit] = 0;
     }
}

void Ir_Main(void)
{
     if(Ir_Bit_Start==true)        //인터럽트발생
     {
          Ir_Data_Read();
          Ir_Bit_Start=false;
     }
}
