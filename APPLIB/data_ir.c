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
     DDRA = 0xff;		// �� Ȯ�ο� LED ��Ʈ
     Ir_Int_Count = 0;
     Ir_Code_Count = 0;
     Ir_Bit_Start = false;
     Ext_Init();
     Timer_Init();
}
void Init_Timer(void)
{
     sbi( TIMSK, 0 );    //Ÿ�̸�0�� ��� Overflow Interrupt �ο��̺�
     sbi( TCCR0, 1 );    //8���� ���
     TCNT0 = 56;
}
void Init_Ext(void)
{
     sbi(EIMSK, 4);  //�ܺ����ͷ�Ʈ 4�����
     sbi(EICRB, 1);    //�������� ���
     cbi(EICRB, 0);
}
#pragma vector=TIMER0_OVF_vect     	// Ÿ�̸�  Overflow ���ͷ�Ʈ ó�� ��ƾ
__interrupt void OVF_Interrupt( void )
{
     Disable_ISR();
     Ir_Int_Count++;
     sbi( TCCR0, 1 );
     TCNT0=56;            //100us�� �������
     Enable_ISR();
}
#pragma vector=INT4_vect    			        // INT4 ���ͷ�Ʈ ó�� ��ƾ
__interrupt void INT4_Interrupt( void )
{
     Disable_ISR();
     Ir_Time_Count = Ir_Int_Count;      //Ÿ�̸� ī��Ʈ ���ͷ�Ʈ �� ����
     Ir_Bit_Start = true;          //���Ű� ������ true
     Ir_Main();
     Ir_Int_Count = 0;
     Enable_ISR();
}

void Ir_Data_Read(void)
{
     if((7<Ir_Time_Count)&&(Ir_Time_Count<13))     //0��(1.125ms)
     {
          Ir_Data[Ir_Code_Count]=0;
          Ir_Code_Count++;
     }
     else if((18<Ir_Time_Count)&&(Ir_Time_Count<25))    //1��(2.5ms)
     {
          Ir_Data[Ir_Code_Count]=1;
          Ir_Code_Count++;
     }
     else if((80<Ir_Time_Count)&&(Ir_Time_Count<100))   //�����ڵ�
     {
          Ir_Code_Count=0;
          Ir_Data_Clear();
     }
     else
     {
          Ir_Data_Clear();
          Ir_Code_Count=0;
     }
     if(Ir_Code_Count>31)          //�����͸� ��� �о������ Ir_Data_Check�Լ��� �̵�
     {
          Ir_Data_Check();
          Ir_Data_Clear();
          Ir_Code_Count=0;
     }
}
void Ir_Data_Check(void)           //������ �ڵ�� ������ �ڵ��� ������ üũ�Ͽ� �����Ͱ��� ����
{
     Ir_Data_Key_Change();
     if((Ir_Data_Code1 | Ir_Data_Code2)==0xff)
     {
          Ir_Data_Key(Ir_Data_Code1);
     }
}

void Ir_Data_Key_Change(void)      //��Ʈ �����͸� ����Ʈ�� ����
{
     U8 bit;
     U8 byte;
     for(bit=16;bit<24;bit++)      //������ ������ ��
     {
          byte = byte << 1;
          byte = byte | Ir_Data[bit];
     }
     Ir_Data_Code1 = byte;

     for(bit=24;bit<32;bit++)      //������ ������ ���� ��
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
          case 0x20:                    //1��Ű ��
                    Ir_Key_Value=0x01;
                    PORTA=0x01;
                    break;
          case 0xA0:                    //2��Ű ��
                    Ir_Key_Value=0x02;
                    PORTA=0x02;
                    break;
          case 0x60:                    //3��Ű ��
                    Ir_Key_Value=0x03;
                    PORTA=0x04;
                    break;
          case 0x10:                    //4��Ű ��
                    Ir_Key_Value=0x04;
                    PORTA=0x08;
                    break;
          case 0x90:                    //5��Ű ��
                    Ir_Key_Value=0x05;
                    PORTA=0x10;
                    break;
          case 0x50:                    //6��Ű ��
                    Ir_Key_Value=0x06;
                    PORTA=0x20;
                    break;
          case 0x30:                    //7��Ű ��
                    Ir_Key_Value=0x07;
                    PORTA=0x40;
                    break;
          case 0xB0:                    //8��Ű ��
                    Ir_Key_Value=0x08;
                    PORTA=0x80;
                    break;
          case 0x70:                    //9��Ű ��
                    Ir_Key_Value=0x09;
                    PORTA=0x03;
                    break;
          case 0x88:                    //0��Ű ��
                    Ir_Key_Value=0x10;
                    PORTA=0x06;
                    break;
          case 0x40:                    //����Ű ��
                    Ir_Key_Value=0x00;
                    PORTA=0x00;
                    break;
          case 0xE0:                    //����+Ű ��
                    Ir_Key_Value=0x0A;
                    PORTA=0x0A;
                    break;
          case 0xD0:                    //����-Ű ��
                    Ir_Key_Value=0x0B;
                    PORTA=0x0B;
                    break;
          case 0x48:                    //ä��+Ű ��
                    Ir_Key_Value=0x0C;
                    PORTA=0x0C;
                    break;
          case 0x08:                    //ä��-Ű ��
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

void Ir_Data_Clear(void)      //��Ʈ ������ ���� ��� Ŭ����
{
     U8 bit;
     for(bit=0;bit<32;bit++)
     {
          Ir_Data[bit] = 0;
     }
}

void Ir_Main(void)
{
     if(Ir_Bit_Start==true)        //���ͷ�Ʈ�߻�
     {
          Ir_Data_Read();
          Ir_Bit_Start=false;
     }
}
