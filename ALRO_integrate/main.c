
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define sbi(PORTX , BitX)   PORTX |=  (1 << BitX)   
#define cbi(PORTX , BitX)   PORTX &= ~(1 << BitX)


/////////////////////////////////////////////////////////////
void main_init(void);
void Init_Timer0_Timer3(void);
void Init_Ext_Interrupt5(void);
void Init_Ext_Interrupt7(void);
void Motor_Encoder(void);
void Timer_PWMset(void);
void Motor_PWM_Up(void);
void Motor_PWM_Down(void);
unsigned char Servo_angle(unsigned char angle);
void Move_Forward(double dt);
void Move_Right(double dt);
void Move_Left(double dt);
void Move_Backward(double dt);
void Uart_Init(unsigned char com,unsigned long Uart_Baud);
unsigned char Uart_Getch(unsigned char Com);
void Uart_Putch(unsigned char Com, unsigned char PutData);
void Uart_U16Bit_PutNum(unsigned int NumData);   // print in decimal
void Uart_Speed_PutNum(unsigned int NumData);
void Uart_Distance_PutNum(unsigned int NumData);
////////////////////////////////////////////////////////////

unsigned char Getch_USART0=0,Getch_USART1=0;
int count=32,count1,count2; //servo count,pwm count count3,4=encoder
unsigned int count3=0,count4=0,time,speed;//count3,4=encoder
volatile unsigned  int Sonic_val = 0, Sonic_cm1 = 0 , Sonic_cm2 = 0;
unsigned char dis[10];
//------------------------------------------------------------------------------
//     				===== bluetooth control in RX vect =====
//------------------------------------------------------------------------------
ISR(USART0_RX_vect)
{
 		Getch_USART0=UDR0;
		switch(Getch_USART0)
		{
			
		//bluetooth control on
		case 'E':
		
		DDRB = 0xff;		//enable remote mode
	
		sbi( TIMSK, TOIE0 );    	 //timer0 overflow interrupt enable
		sbi(DDRG, 0),sbi(DDRG, 1);		// front sensor trigger disable
		
		sbi(PORTA,1);
		_delay_ms(130);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(130);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(130);
		cbi(PORTA,0);		////let you know the 'ON signal'
							
		break;
		
		//bluetooth control off, trigger disable
		case 'h':
			
		OCR1C = Servo_angle(90); //hold at angle 90'
		_delay_ms(300);
		
		cbi(DDRG, 0);			// back sensor trigger disable
		cbi(DDRG, 1);			// front sensor trigger disable  
		DDRB=0;		// DC,SERVO(B7) disable
		cbi( TIMSK, TOIE0 );	//return initial set
		
		sbi(PORTA,1);
		_delay_ms(130);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(130);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(130);
		cbi(PORTA,0);		////let you know the 'OFF signal' 

		break;

		
		//FORWARD
		case 'A': 
		

		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1); //right dc forward direction
		cbi(PORTB,2);   sbi(PORTB,3); //left dc forward direction
		Motor_PWM_Up();
		sbi(PORTA,1),sbi(PORTA,2);
		_delay_ms(300);
		Motor_PWM_Down();
		cbi(PORTA,1),cbi(PORTA,2);		//Forward led set
		}
		break;

		//turn right
		case 'D':  
			
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1);//right dc forward direction
		sbi(PORTB,2);   cbi(PORTB,3);//left dc backward direction
		Motor_PWM_Up();
		sbi(PORTA,1);
		_delay_ms(200);
		Motor_PWM_Down();
		cbi(PORTA,1);				//left led set
		}
		break;

		//turn left
		case 'B':    

		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		cbi(PORTB,0);   sbi(PORTB,1);//right dc backward direction
		cbi(PORTB,2);   sbi(PORTB,3);//left dc forward direction
		Motor_PWM_Up();
		sbi(PORTA,2);
		_delay_ms(200);
		Motor_PWM_Down();
		cbi(PORTA,2);			//right led set
		}
		break;

		//BACKWARD
		case 'C':		
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(80);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		cbi(PORTB,0);   sbi(PORTB,1);// dc backward
		sbi(PORTB,2);   cbi(PORTB,3);
		Motor_PWM_Up();
		sbi(PORTA,0);
		_delay_ms(300);
		Motor_PWM_Down();
		cbi(PORTA,0);
		}
		break;

		//Sonic trigger
		case 'G':		
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{	
				// Back,front sensor trigger enable
			
			dis[4] = Sonic_cm1;
			Uart_Distance_PutNum(dis[4]);

						//Back,front sensor trigger disable
		}
		break;

		//SPIN
		case 's':		
		
		//Uart_Putch(0, 'S');
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1);//right dc forward direction
		sbi(PORTB,2);   cbi(PORTB,3);//left dc backward direction
		Motor_PWM_Up();
		sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
		_delay_ms(1500);
		Motor_PWM_Down();
		cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		break;
		
		//servo left
		case 'F':			
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else if(DDRB==0xff)
		{
			if(OCR1C>=130)			//protect motor limit
			{
				OCR1C=130;
				sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(100);
				cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
			}
			else
			{
			count=(OCR1C+25);
			OCR1C=count;
			_delay_ms(500);
			}
		}
		
		break;

		//servo right
		case 'H':			
	
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else if(DDRB==0xff)
		{
			if(OCR1C<=30)			//protect motor limit
			{
				OCR1C=30;
				sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(100);
				cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
			}
			else
			{
			count=(OCR1C-25);
			OCR1C=count;
			_delay_ms(500);
			}
		}
		
		break;
		
		//text alarm (no led)
		case 'z':			

				OCR1C = Servo_angle(0);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(180);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(0);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(180);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
		
		break;

		//battery alarm (no led)
		case 'Z':			
	

				OCR1C = Servo_angle(0),sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(180);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(0);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500);
				OCR1C = Servo_angle(180);
				_delay_ms(500);
				OCR1C = Servo_angle(90);
				_delay_ms(500), cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);

			break;
		
		//Auto mode start(led set)
		case 't':
		
		sbi(DDRG, 0);			// back sensor trigger enable : auto mode 
		sbi(DDRG, 1);			// front sensor trigger enable : auto mode
		DDRB = 0xef;			// Auto mode on, direct action (all off) -> (auto)
		cbi( TIMSK, TOIE0 );	// initial set

		sbi(PORTA,1);
		_delay_ms(80);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(80);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(80);
		cbi(PORTA,0);		////let you know the 'ON signal'
		
		break;

		}

}
//------------------------------------------------------------------------------
//     				===== computer control in RX vect =====
//------------------------------------------------------------------------------
ISR(USART1_RX_vect)
{
 		Getch_USART1=UDR1;
		switch(Getch_USART1)
		{
		//bluetooth control on
		case 'E':
		
		DDRB = 0xff;		//enable remote mode
	
		sbi( TIMSK, TOIE0 );    	 //timer0 overflow interrupt enable
		sbi(DDRG, 0),sbi(DDRG, 1);		// front sensor trigger disable
		
		sbi(PORTA,1);
		_delay_ms(130);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(130);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(130);
		cbi(PORTA,0);		////let you know the 'ON signal'
							
		break;
		
		//bluetooth control off, trigger disable
		case 'h':
			
		OCR1C = Servo_angle(90); //hold at angle 90'
		_delay_ms(300);
		
		cbi(DDRG, 0);			// back sensor trigger disable
		cbi(DDRG, 1);			// front sensor trigger disable  
		DDRB=0;		// DC,SERVO(B7) disable
		cbi( TIMSK, TOIE0 );	//return initial set
		
		sbi(PORTA,1);
		_delay_ms(130);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(130);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(130);
		cbi(PORTA,0);		////let you know the 'OFF signal' 

		break;

		
		//FORWARD
		case 'A': 
		

		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1); //right dc forward direction
		cbi(PORTB,2);   sbi(PORTB,3); //left dc forward direction
		Motor_PWM_Up();
		sbi(PORTA,1),sbi(PORTA,2);
		_delay_ms(300);
		Motor_PWM_Down();
		cbi(PORTA,1),cbi(PORTA,2);		//Forward led set
		}
		break;

		//turn right
		case 'D':  
			
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1);//right dc forward direction
		sbi(PORTB,2);   cbi(PORTB,3);//left dc backward direction
		Motor_PWM_Up();
		sbi(PORTA,1);
		_delay_ms(200);
		Motor_PWM_Down();
		cbi(PORTA,1);				//left led set
		}
		break;

		//turn left
		case 'B':    

		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		cbi(PORTB,0);   sbi(PORTB,1);//right dc backward direction
		cbi(PORTB,2);   sbi(PORTB,3);//left dc forward direction
		Motor_PWM_Up();
		sbi(PORTA,2);
		_delay_ms(200);
		Motor_PWM_Down();
		cbi(PORTA,2);			//right led set
		}
		break;

		//BACKWARD
		case 'C':		
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(80);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		cbi(PORTB,0);   sbi(PORTB,1);// dc backward
		sbi(PORTB,2);   cbi(PORTB,3);
		Motor_PWM_Up();
		sbi(PORTA,0);
		_delay_ms(300);
		Motor_PWM_Down();
		cbi(PORTA,0);
		}
		break;

		//Sonic trigger
		case 'G':		
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{	
				// Back,front sensor trigger enable
			
			dis[4] = Sonic_cm1;
			Uart_Distance_PutNum(dis[4]);

						//Back,front sensor trigger disable
		}
		break;

		//SPIN
		case 's':		
		
		//Uart_Putch(0, 'S');
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else
		{
		sbi(PORTB,0);   cbi(PORTB,1);//right dc forward direction
		sbi(PORTB,2);   cbi(PORTB,3);//left dc backward direction
		Motor_PWM_Up();
		sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
		_delay_ms(1500);
		Motor_PWM_Down();
		cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		break;
		
		//servo left
		case 'F':			
		
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else if(DDRB==0xff)
		{
			if(OCR1C>=130)			//protect motor limit
			{
				OCR1C=130;
				sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(100);
				cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
			}
			else
			{
			count=(OCR1C+25);
			OCR1C=count;
			_delay_ms(500);
			}
		}
		
		break;

		//servo right
		case 'H':			
	
		
		if(DDRB==0)
		{
			sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
			_delay_ms(100);
			cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
		}
		else if(DDRB==0xff)
		{
			if(OCR1C<=30)			//protect motor limit
			{
				OCR1C=30;
				sbi(PORTA,0),sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(100);
				cbi(PORTA,0),cbi(PORTA,1),cbi(PORTA,2);
			}
			else
			{
			count=(OCR1C-25);
			OCR1C=count;
			_delay_ms(500);
			}
		}
		
		break;
		
		
		//Auto mode start
		case 't':
		
		sbi(DDRG, 0);			// back sensor trigger enable : auto mode 
		sbi(DDRG, 1);			// front sensor trigger enable : auto mode
		DDRB = 0xef;			// Auto mode on, direct action (all off) -> (auto)
		cbi( TIMSK, TOIE0 );	// initial set

		sbi(PORTA,1);
		_delay_ms(80);
		cbi(PORTA,1),sbi(PORTA,2);	 
		_delay_ms(80);
		cbi(PORTA,2),sbi(PORTA,0);
		_delay_ms(80);
		cbi(PORTA,0);		////let you know the 'ON signal'
		
		break;

		}

}
//------------------------------------------------------------------------------
//     				===== Sonic Trigger Pulse =====
//						: Trigger front & back
//------------------------------------------------------------------------------
ISR(TIMER0_OVF_vect)	// Sonic Trigger Pulse
{

	sbi(PORTG,0),sbi(PORTG,1);   // front & back trigger
	_delay_us(10);				//per 10us
	cbi(PORTG,0),cbi(PORTG,1); 
	TCNT0 = 0; 
	
}
//------------------------------------------------------------------------------
//     				===== front sensor =====
//------------------------------------------------------------------------------

ISR(INT5_vect)           //front sensor echo 
{	
	
	
	if(EICRB == 0x0c)		    //only front sensor RISING   (back RISING이면 DISABLE 이라두 영향을미침)
	{
		
		TCNT0 = 0;			//count reset
		EICRB=0x08; 		//right FALLING 
		
	}
	else if(EICRB == 0x08)    //front FALLING  ,back RISING   
	{
		
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt		
		Sonic_cm1 = (((Sonic_val * 64) * 34300)/2000000) +1;			//measure distance in cm
		//Uart_U16Bit_PutNum(Sonic_cm);
		//_delay_ms(10);
		EICRB=0xc0;    // back RISING, rightx 

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024 timer start 
		TCNT0 = 100;                                                 //256-100=156   64us*156 =약10ms

		sbi( EIMSK, INT7  );    // EXT_INT 7 ENABLE
		cbi( EIMSK, INT5  );    // EXT_INT 5 DISABLE 
		
	}
}
//------------------------------------------------------------------------------
//     				===== back sensor =====
//------------------------------------------------------------------------------
ISR(INT7_vect)
{	
	if(EICRB==0xc0)		    //back RISING EDGE  
	{	
		TCNT0 = 0;		//count reset
		
		EICRB=0x80;   // back FALLING SET 
		
	}
	
	else if(EICRB==0x80)    //back FALLING
	{
		TCCR0 = 0x00;			//off timer cnt
		Sonic_val = TCNT0;		//check cnt

		Sonic_cm2 = (((Sonic_val * 64) * 34300)/2000000) +1;			//measure distance in cm
		//Uart_U16Bit_PutNum(Sonic_cm);
		//_delay_ms(10);

		EICRB=0x0c;    // back FALLING

		TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//freescale : 1024
		TCNT0 = 100;                                                 //256-100=156   64us*156 =약10ms 

		sbi( EIMSK, INT5  );    // EXT_INT 5 ENABLE 
		cbi( EIMSK, INT7  );    // EXT_INT 7 DISABLE
	}
}
//------------------------------------------------------------------------------
//     				===== right encoder interrupt =====
//------------------------------------------------------------------------------

ISR(INT6_vect)
{
	count3 +=2;
	//Uart_Putch(1,count3);
	//Uart_U16Bit_PutNum(count3);
}

//------------------------------------------------------------------------------
//     				===== left encoder interrupt =====
//------------------------------------------------------------------------------

ISR(INT1_vect)
{	
	

	if(count4 == 0)
	{	
		count4++;
		TCNT3 = 0;
		//Uart_U16Bit_PutNum(TCNT3);		//0줘도 90정도로 시작 
	}
	else if(count4 == 32)
	{	
		if(TCNT3<=5000)		//TCNT3 error protect : If the time over 65535 when count4=32  
		{	
			count4 = 0;
			TCNT3 = 0;
		}
		else
		{
		time = (0.64*TCNT3);
		speed = (110000 / time);  //// cm/s
		//Uart_Speed_PutNum(speed);		//SPEED
		//_delay_ms(500);		//SPEED display in 3s
		TCNT3 = 0;	
		count4 = 0;
		}
		
	}
	
	//Uart_U16Bit_PutNum(count4);
	//Uart_U16Bit_PutNum(TCNT3);
	count4++;
	
}

//------------------------------------------------------------------------------
//     					===== main =====
//------------------------------------------------------------------------------
int main(void)
{
	main_init();
	
	while(1)
	{   
		if(DDRB == 0xef)		//Auto mode
		{
			//----------------------------------------------------------------------
			//     					===== Sensor Control =====
			//----------------------------------------------------------------------
			OCR1C = Servo_angle(0);
			_delay_ms(330);    		//wait for stable!! minimum speed
			sbi( TIMSK, TOIE0 );
			_delay_ms(25);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[1] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[1]);
			
			_delay_ms(50);		
			
			OCR1C = Servo_angle(45);
			_delay_ms(300);    		//wait for stable
			sbi( TIMSK, TOIE0 );
			_delay_ms(20);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[2] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[2]);
			
			
			_delay_ms(50);		//moving speed


			OCR1C = Servo_angle(90);
			_delay_ms(300);    		//wait for stable
			sbi( TIMSK, TOIE0 );
			_delay_ms(20);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[3] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[3]);

			
			_delay_ms(50);		//moving speed
			
			OCR1C = Servo_angle(137);
			_delay_ms(300);    		//wait for stable
			sbi( TIMSK, TOIE0 );
			_delay_ms(20);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[4] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[4]);
				
			_delay_ms(50);		//moving speed
			
			OCR1C = Servo_angle(183);
			_delay_ms(300);    		//wait for stable
			sbi( TIMSK, TOIE0 );
			_delay_ms(20);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[5] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[5]);

			_delay_ms(50);		//moving speed
			
			OCR1C = Servo_angle(90);
			_delay_ms(300);    		//wait for stable
			sbi( TIMSK, TOIE0 );
			_delay_ms(20);			//at least once trigger, protect duplication with before info
			cbi( TIMSK, TOIE0 );
			_delay_ms(10);
			dis[3] = Sonic_cm1;
			//Uart_U16Bit_PutNum(dis[3]);
			dis[9] = Sonic_cm2;
			//Uart_U16Bit_PutNum(dis[9]);


		//----------------------------------------------------------------------
		//     					===== Motor Control =====
		//----------------------------------------------------------------------
		
		//----------------------------------------------------------------------
		//     					===== Closer Sensor2,3 Control =====
		//----------------------------------------------------------------------
		if( ( dis[2] <= 13 ) )				
		{	
			sbi(PORTA,0);
			_delay_ms(80);
			cbi(PORTA,0);		//let you know signal

			_delay_ms(100);

			cbi(PORTB,0);   sbi(PORTB,1);// dc backward
			sbi(PORTB,2);   cbi(PORTB,3);
			Motor_PWM_Up();
			_delay_ms(130);
			Motor_PWM_Down();
				
			_delay_ms(500);
				
			cbi(PORTB,0);   sbi(PORTB,1);	
			cbi(PORTB,2);   sbi(PORTB,3);	//// turn left
			Motor_PWM_Up();
			sbi(PORTA,2);
			_delay_ms(300);
			Motor_PWM_Down();
			cbi(PORTA,2);			//left led set
			
			_delay_ms(50);
		}
		
		if( ( dis[4] <= 13 ) )
		{	
			sbi(PORTA,0);
			_delay_ms(80);
			cbi(PORTA,0);		//let you know signal


			cbi(PORTB,0);   sbi(PORTB,1);	// dc backward
			sbi(PORTB,2);   cbi(PORTB,3);
			Motor_PWM_Up();
			_delay_ms(130);
			Motor_PWM_Down();
			
			_delay_ms(500);
				
			sbi(PORTB,0);   cbi(PORTB,1);
			sbi(PORTB,2);   cbi(PORTB,3);	////turn right
			Motor_PWM_Up();
			sbi(PORTA,1);
			_delay_ms(300);
			Motor_PWM_Down();
			cbi(PORTA,1);				//right led set

			_delay_ms(50);
		}			
		
		if( ( dis[3] >= 22 ) && (dis[2] >= 14 ) && ( dis[4] >= 14) )		// front sensor control section
		{	
			sbi(PORTA,0);
			_delay_ms(100);
			cbi(PORTA,0);		//let you know signal
			_delay_ms(100);
			sbi(PORTA,0);
			_delay_ms(100);
			cbi(PORTA,0);		//let you know signal

			_delay_ms(100);
		
			if( ( dis[1] <= 12 ) && ( dis[1] < dis[5] ) ) // turn left 100
			{
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(100);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				cbi(PORTB,0);   sbi(PORTB,1);	
				cbi(PORTB,2);   sbi(PORTB,3);	//// turn left
				Motor_PWM_Up();
				sbi(PORTA,2);
				_delay_ms(235);
				Motor_PWM_Down();
				cbi(PORTA,2);			//left led set
				
				_delay_ms(50);
			}
		
			if( ( dis[5] <= 12 ) && ( dis[5] < dis[1]) )		//turn right 100
			{	
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(100);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				sbi(PORTB,0);   cbi(PORTB,1);
				sbi(PORTB,2);   cbi(PORTB,3);	////turn right
				Motor_PWM_Up();
				sbi(PORTA,1);
				_delay_ms(235);
				Motor_PWM_Down();
				cbi(PORTA,1);				//right led set

				_delay_ms(50);
			}
		
			if(  ( dis[1] >= 13 ) && ( dis[5] >= 13 ) )
			{
				sbi(PORTB,0);   cbi(PORTB,1); 
				cbi(PORTB,2);   sbi(PORTB,3);  ////just forward 
				Motor_PWM_Up();
				sbi(PORTA,1),sbi(PORTA,2);
				_delay_ms(225);		
				Motor_PWM_Down();
				cbi(PORTA,1),cbi(PORTA,2);
				
				_delay_ms(50);
			}
				
		}
		//----------------------------------------------------------------------
		//     					===== Closer Front Sensor Control =====
		//----------------------------------------------------------------------
		if( (  dis[3] < 22 ) && ( dis[2] >= 14 ) && ( dis[4] >= 14 ) )
		{	
			sbi(PORTA,0);
			_delay_ms(100);
			cbi(PORTA,0);		//let you know signal
			_delay_ms(100);
			sbi(PORTA,0);
			_delay_ms(100);
			cbi(PORTA,0);		//let you know signal
			_delay_ms(100);
			sbi(PORTA,0);
			_delay_ms(100);
			cbi(PORTA,0);		//let you know signal

			
			
			if( ( dis[1] ) > ( dis[5] ) )	//dc backward 200 then turn right 150
			{	
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(155);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				sbi(PORTB,0);   cbi(PORTB,1);
				sbi(PORTB,2);   cbi(PORTB,3);	////turn right
				Motor_PWM_Up();
				sbi(PORTA,1);
				_delay_ms(255);
				Motor_PWM_Down();
				cbi(PORTA,1);				//right led set

				_delay_ms(50);
				
			}
			else if( ( dis[1] ) < ( dis[5] ) )		//case2_b - turn left more than case1
			{	
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(155);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				cbi(PORTB,0);   sbi(PORTB,1);	
				cbi(PORTB,2);   sbi(PORTB,3);	//// turn left
				Motor_PWM_Up();
				sbi(PORTA,2);
				_delay_ms(255);
				Motor_PWM_Down();
				cbi(PORTA,2);			//left led set

				_delay_ms(50);
			}
		
		}	
		
		//----------------------------------------------------------------------
		//     					===== Back Sensor Control =====
		//----------------------------------------------------------------------
		if( ( dis[9] < 5 ) && ( dis[3] > 100 ) )			
		{
			sbi(PORTB,0);   cbi(PORTB,1);// dc forward
			cbi(PORTB,2);   sbi(PORTB,3);
			Motor_PWM_Up();
			sbi(PORTA,0);
			_delay_ms(120);
			Motor_PWM_Down();
			cbi(PORTA,0);
			
			if( ( dis[1] ) > ( dis[5] ) )	//dc backward 115 then turn right 135
			{	
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(120);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				sbi(PORTB,0);   cbi(PORTB,1);
				sbi(PORTB,2);   cbi(PORTB,3);	////turn right
				Motor_PWM_Up();
				sbi(PORTA,1);
				_delay_ms(160);
				Motor_PWM_Down();
				cbi(PORTA,1);				//right led set

				_delay_ms(50);
			
			}
			if( ( dis[1] ) > ( dis[5] ) )	//dc backward 115 then turn left 135
			{	
				cbi(PORTB,0);   sbi(PORTB,1);// dc backward
				sbi(PORTB,2);   cbi(PORTB,3);
				Motor_PWM_Up();
				_delay_ms(120);
				Motor_PWM_Down();
				
				_delay_ms(500);
				
				cbi(PORTB,0);   sbi(PORTB,1);	
				cbi(PORTB,2);   sbi(PORTB,3);	//// turn left
				Motor_PWM_Up();
				sbi(PORTA,2);
				_delay_ms(160);
				Motor_PWM_Down();
				cbi(PORTA,2);			//left led set

				_delay_ms(50);
			}
			
		}
		
		Uart_Speed_PutNum(speed);

		sbi(PORTB,0);   cbi(PORTB,1); 
		cbi(PORTB,2);   sbi(PORTB,3);  ////just forward 
		Motor_PWM_Up();
		sbi(PORTA,1),sbi(PORTA,2);
		_delay_ms(35);		
		Motor_PWM_Down();
		cbi(PORTA,1),cbi(PORTA,2);

		_delay_ms(50);
		
	}
	}
	return 0;
}
//------------------------------------------------------------------------------
//     					===== main_init =====  					
//------------------------------------------------------------------------------
void main_init(void)
{
	cbi(SREG,7);				//all interrupt disable

	//USART 
	Uart_Init(0,9600);			//bluetooth uart enable
	Uart_Init(1,9600);			//computer uart enable  
	
	//DC motor,servo motor
 	DDRB=0xff;		//DC on, Servo on  initial condition	
 	
	Timer_PWMset();
	
    //left right sensor
	cbi(DDRG, 0);			// back sensor trigger disable : initial conditon 
	cbi(DDRG, 1);			// front sensor trigger disable : initial conditon 
	sbi(SREG, 7);			// interrupt enable		
	Init_Timer0_Timer3();	// timer0 overflow set, timer3 set
	Init_Ext_Interrupt7();	// back sensor interrupt
	Init_Ext_Interrupt5();	// front sensor interrupt

	//Motor encoder set
	Motor_Encoder();
	
	//LED SET
	DDRA=0xff;
	
	sbi(SREG,7);
	
}




//------------------------------------------------------------------------------
//     				===== timer overflow set =====
//  					:(trigger per 10ms)
//------------------------------------------------------------------------------
void Init_Timer0_Timer3(void)   
{   
	
	cbi( TIMSK, TOIE0 );     //timer0 overflow interrupt disable(initial)
	TCCR0 = ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );		//prescale 1024 
	TCNT0 = 100;					 // //256-100=156   64us*156 =약10ms  , timerovf interrupt per 10ms

	
	TCCR3B = ( 1 << CS30 ) | ( 0 << CS31 ) | ( 1 << CS32 );		//timer3 prescale 1024 = 64us	
	TCNT3 = 0;		
		
}


//------------------------------------------------------------------------------
//     				===== front sensor INT set =====  					
//------------------------------------------------------------------------------
void Init_Ext_Interrupt5(void) 
{
	sbi( EICRB, ISC51 );    // INT5 RISING EDGE ENABLE
	sbi( EICRB, ISC50 );    // INT5 RISING EDGE ENABLE
	
	sbi( EIMSK, INT5  );    // EXT_INT 5 ENABLE
	cbi( EIFR, INTF5 );     // INTERRUPT FLAG CLEAR	
	cbi( DDRE, 5 );  	    // sensor signal input
	//SET_BIT( PORTE, 4 );		// Input Set, Pull-Up Setting?????????
}

//------------------------------------------------------------------------------
//     				===== back sensor INT set =====  					
//------------------------------------------------------------------------------
void Init_Ext_Interrupt7(void)
{
	cbi( EICRB, ISC71 );    // INT7 edge nothing
	cbi( EICRB, ISC70 );    // INT7 edge nothing  
	
	cbi( EIMSK, INT7  );    // EXT_INT 7 DISABLE
	cbi( EIFR , INTF7 );    // INTERRUPT FLAG CLEAR
	cbi( DDRE, 7);			// sensor signal input  
	//SET_BIT( PORTE, 5);			// Input Set, Pull-Up Setting?????????
}
//------------------------------------------------------------------------------
//     				===== Motor_Encoder =====
//						: Encoder interrupt set
//------------------------------------------------------------------------------
void Motor_Encoder(void)
{	
	
	cbi( DDRD, 1);	//D1 INPUT SET
	//cbi( DDRE, 6);	//E6 INPUT SET
	
	sbi( EIMSK, INT1);
	//sbi( EIMSK, INT6); ////ENABLE
	
	sbi( EICRA, ISC11);
	sbi( EICRA, ISC10);	////INT1 rising edge set
	
	//sbi( EICRB, ISC61);
	//sbi( EICRB, ISC60);	////INT6 rising edge set

	sbi( SREG, 7); //ALL INT ENABLEA
}


//------------------------------------------------------------------------------
//     				===== Timer1 PWM setting  =====
//					:PWM for servo, dc motor    0C1A:right dc 0C1B:left dc 0C1C:servo
//------------------------------------------------------------------------------
void Timer_PWMset(void)
{
	TCCR1A = 0xAA;  // OC1A,B,C PORT MODE  10101010
	TCCR1B = 0x1C;  // mode14(fast pwm),prescale256 = 16us  
	ICR1 = 1249;    //ICR1(OVERFLOW) 16us*1250 = 20ms servo motor clock set 
	OCR1C = 80;    // ratio 70:1250 servo motor initial number
}	
//------------------------------------------------------------------------------
//     				===== Motor_PWM_UP  =====
//					: right=0=0C1A  left=1=0C1B    max speed=1249;
//------------------------------------------------------------------------------
void Motor_PWM_Up(void)
{
		for(count1 = 0 ; count1 < 1199 ; count1+=50)
		{
			OCR1A = count1;
			OCR1B = count1;
			_delay_us(200);
		}
			OCR1A = 1249;
			OCR1B = 1150;
}
//------------------------------------------------------------------------------
//     				===== Motor_PWM_Down  =====
//					: right=0=0C1A  left=1=0C1B    min speed=0;
//------------------------------------------------------------------------------
void Motor_PWM_Down(void)
{
	for(count1 = 1249 ; count1 > 49 ; count1-=50)
		{
			OCR1A = count1;
			OCR1B = count1;
			_delay_us(200);
		}
			OCR1A = 0;
			OCR1B = 0;
}			
//------------------------------------------------------------------------------
//     				===== Servo_angle =====
//------------------------------------------------------------------------------
unsigned char Servo_angle(unsigned char angle)
{
	return ((54*angle)+3100)/100 ;
}
/*
//------------------------------------------------------------------------------
//     				===== Move_Forward =====
//------------------------------------------------------------------------------
void Move_Forward(int dt)
{
	sbi(PORTB,0);   cbi(PORTB,1); 
	cbi(PORTB,2);   sbi(PORTB,3);  ////forward
	Motor_PWM_Up();
	sbi(PORTA,1),sbi(PORTA,2);
	_delay_ms((double)dt);		//강제형변환 
	Motor_PWM_Down();
	cbi(PORTA,1),cbi(PORTA,2);		//Forward led set
}	

//------------------------------------------------------------------------------
//     				===== Move_Right =====
//------------------------------------------------------------------------------
void Move_Right(double dt)
{
	sbi(PORTB,0);   cbi(PORTB,1);
	sbi(PORTB,2);   cbi(PORTB,3);	////turn right
	Motor_PWM_Up();
	sbi(PORTA,1);
	_delay_ms(dt);
	Motor_PWM_Down();
	cbi(PORTA,1);				//right led set
}	
//------------------------------------------------------------------------------
//     				===== Move_Left =====
//------------------------------------------------------------------------------
void Move_Left(int dt)
{
	cbi(PORTB,0);   sbi(PORTB,1);	
	cbi(PORTB,2);   sbi(PORTB,3);	//// turn left
	Motor_PWM_Up();
	sbi(PORTA,2);
	_delay_ms((double)dt);
	Motor_PWM_Down();
	cbi(PORTA,2);			//left led set	
}	
//------------------------------------------------------------------------------
//     				===== Move_Backward =====
//------------------------------------------------------------------------------
void Move_Backward(int dt)
{
	cbi(PORTB,0);   sbi(PORTB,1); 
	sbi(PORTB,2);   cbi(PORTB,3);  ////backward
	Motor_PWM_Up();
	sbi(PORTA,0);
	_delay_ms((double)dt);
	Motor_PWM_Down();
	cbi(PORTA,0);		//backward led set
}	
*/
//------------------------------------------------------------------------------
//     				===== Uart_Init =====
//             		: Initial set what num & speed 
//------------------------------------------------------------------------------

void Uart_Init(unsigned char com,unsigned long Uart_Baud) 
{	
	unsigned long Temp_UBRR;
	Temp_UBRR = 16000000/(16L * Uart_Baud) - 1;
	
	
    //---------------------------- UART0 초기화 --------------------------------
	if( com==0 )                           	
	{
		           // 통신속도 설정
		UBRR0H =(Temp_UBRR >> 8);              // Baud set
		UBRR0L =(Temp_UBRR & 0x00FF);
		
		UCSR0A = (0<<RXC0) | (1<<UDRE0);  // nothing in recieve buffer & transmission buffer  
		UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) ;  //recieve & transmission enable ,   
		UCSR0C = (3<<UCSZ00);		//8bit transfer 
		cbi(DDRE,0); 	//RXD input
		sbi(DDRE,1);	//TXD output
		
	}
	
    //---------------------------- UART1 초기화 --------------------------------
	else if( com==1 )
	{
		              
		UBRR1H = (Temp_UBRR >> 8);              // Baud set
		UBRR1L = (Temp_UBRR & 0x00FF);

		
		  
		UCSR1A = (0<<RXC1) | (1<<UDRE1);	//nothing in recieve buffer & transmission buffer
		UCSR1B = (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1);	//recieve & transmission enable
		UCSR1C = (3<<UCSZ10);			//8bit transfer
		cbi(DDRD,2);  	//RXD input
		sbi(DDRD,3);	//TXD output
		
	}
}

//------------------------------------------------------------------------------
//     				===== Uart_Getch =====
//------------------------------------------------------------------------------
unsigned char Uart_Getch(unsigned char Com)
{
	switch( Com )
	{
		case 0:
			while(!( UCSR0A & (1<<RXC0)) );    // wait until the point of receive
			return UDR0;                       // receive data
		
		case 1:
			while(!( UCSR1A & (1<<RXC1)) );    // wait until the point of receive
			return UDR1;                       // recieve data
		
        default:
			return 0;
	}
}
//------------------------------------------------------------------------------
//     				===== Uart_Putch =====
//------------------------------------------------------------------------------
void Uart_Putch(unsigned char Com, unsigned char PutData)
{
	switch(Com)
	{
		case 0:
			while(!( UCSR0A & (1<<UDRE0)) );    // wait until the point of trasmission available
			UDR0 = PutData;                     // trasfer data
			break;
		
		case 1:
			while(!( UCSR1A & (1<<UDRE1)) );    // wait until the point of trasmission available
			UDR1 = PutData;                     // trasfer data
			break;
	}
}
//------------------------------------------------------------------------------
//     				===== decimal print in ASC =====  					
//------------------------------------------------------------------------------
void Uart_U16Bit_PutNum(unsigned int NumData)
{
	unsigned int TempData;

	TempData = NumData/10000;
	Uart_Putch(0,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(0,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1's place print 
						
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1's place print 
}

//------------------------------------------------------------------------------
//     				===== speed decimal print  =====  					
//------------------------------------------------------------------------------
void Uart_Speed_PutNum(unsigned int NumData)
{
	unsigned int TempData;

	Uart_Putch(0,83);
	Uart_Putch(0,80);
	Uart_Putch(0,69);
	Uart_Putch(0,69);
	Uart_Putch(0,68);
	Uart_Putch(0,58); // SPEED:

	Uart_Putch(1,83);
	Uart_Putch(1,80);
	Uart_Putch(1,69);
	Uart_Putch(1,69);
	Uart_Putch(1,68);
	Uart_Putch(1,58); // SPEED:
		
	TempData = NumData/10000;
	Uart_Putch(0,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(0,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1's place print 
						
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1's place print 
}
//------------------------------------------------------------------------------
//     				===== distance decimal print  =====  					
//------------------------------------------------------------------------------
void Uart_Distance_PutNum(unsigned int NumData)
{
	unsigned int TempData;
	Uart_Putch(0,68);
	Uart_Putch(0,105);
	Uart_Putch(0,115);
	Uart_Putch(0,58);	// Dis:
	
	Uart_Putch(1,68);
	Uart_Putch(1,105);
	Uart_Putch(1,115);
	Uart_Putch(1,58);   // Dis:
		
	TempData = NumData/10000;
	Uart_Putch(0,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(0,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(0,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(0,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(0,TempData+48);					// 1's place print 
						
	TempData = NumData/10000;
	Uart_Putch(1,TempData+48);					// 10000's place print
	TempData = (NumData%10000)/1000;
	Uart_Putch(1,TempData+48);					// 1000's place print
	TempData = (NumData%1000)/100;
	Uart_Putch(1,TempData+48);					// 100's place print
	TempData = (NumData%100)/10;
	Uart_Putch(1,TempData+48);					// 10's place print
	TempData = (NumData%10);			
	Uart_Putch(1,TempData+48);					// 1's place print 
}
