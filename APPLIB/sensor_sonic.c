/*==============================================================================
 *
 *   Ultra Sonic Sensor Module
 *
 *        File Name      : sensor_sonic.c
 *        Version        : 1.3
 *        Date           : 2006.07.01
 *        Author         : Eun Hye Kim (ROLAB 21th, Kwangwoon University)
 *        MPU_Type       : ATmega128(16MHz)
 *        Modified       : 2006.02.11 By k.e.h
 *        Copyright(c) ROLAB. All Rights Reserved.
 *
==============================================================================*/
#include <iom128.h>
#include "../define.h"
#include "sonic_sensor.h"

U8 Sensor_Select = 0;

volatile U8 Sonic_Value[2];
U8 Sonar_Select[2] = {0x01, 0x01};
U8 Sonic_Vlaue_0;
U8 Sonic_Vlaue_1;


#pragma vector=TIMER0_OVF_vect     //������ �ð� ���� �ɸ��� Ÿ�̸�0 ���񽺷�ƾ
__interrupt void timer0_ovf_isr( void )
{
     U8 i;
     Disable_ISR()
     PORTG = 0x00;

     for(i=0;i<35;i++)
     {
	PORTG = 0xff;
     }
     PORTG = 0x00;

     PORTC = Sonar_Select[Sensor_Select];
     Enable_ISR()

}

#pragma vector=INT0_vect					//Falling edge ��������
__interrupt void int0_isr( void )
{

     TCCR0 = 0x00;
     PORTC = Sonar_Select[Sensor_Select];


     Sonic_Value[Sensor_Select] = TCNT0;


     Sonic_Vlaue_0 = Sonic_Value[0];
     Sonic_Vlaue_1 = Sonic_Value[1];

     Sensor_Select++;
     if(Sensor_Select == 2)
     Sensor_Select = 0;


     TCCR0 = 0x07;	

}
#pragma vector=INT1_vect 			 //Rising edge �������� �ɸ��� ���ͷ�Ʈ //���� ��ƾ
__interrupt void int1_isr( void )
{

     TCNT0 = 0x00;
     TCCR0 = 0x07; 					 //Timer0 start Ŭ�� 1024���ַ�

}
void Init_Ext0(void)
{ 	
    sbi( EIMSK, 0);      //INT0      //EXT_0 INTERRUPT ENABLE
    sbi( EICRA, 1 );     // ISC01    //������ ��¶����� �ϴ� FALLING EDGE�� ��´�.
    cbi( EICRA, 0 );     // ISC00
}
void Init_Ext1(void)
{
    sbi( EIMSK, 1);      //INT0    //EXT_1 INTERRUPT ENABLE
    sbi( EICRA, 2 );     // ISC11  //������ ��¶����� RISING EDGE�� ��´�
    sbi( EICRA, 3 );     // ISC10
}
void Init_Timer(void)
{
     TIMSK = 0x01;         //�����÷ο� ���ͷ�Ʈ�� �ɸ��� �Ѵ�.
     TCNT0 = 0x00;       //�ʱⰪ 0���ؼ� �ִ��� ���� ������ �Ѵ�.

}
void Init_Port(void)
{

     DDRC = 0xff;
     PORTC = 0x00;
     DDRG = 0xff;
     PORTG = 0x00;
     DDRD = 0x00;
     PORTD = 0x00;
}
void Init_Sonic_Sensor(void)
{
    Init_Port();
    Init_Ext0();
    Init_Ext1();
    Init_Timer();
}










