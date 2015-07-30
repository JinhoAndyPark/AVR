#include "sprinkler.h"

#define MOTORON		sbi(PORTG, 0)
#define MOTOROFF	cbi(PORTG, 0)


volatile unsigned int CNTsonic;
volatile unsigned char VALsonic;

float sens_temp, sens_humi;
unsigned char humi, temp;
unsigned char target_humi, target_temp;

unsigned char Get_data;


volatile unsigned char mAUTO; 
volatile unsigned char sMOTOR, sSENSOR;
volatile unsigned char Timerflag=0, nTime, TargetTime=30;
volatile unsigned char nFND[2] = {0,0};
volatile unsigned char DISFND[10] = {0x7E, 0x18, 0x6D, 0x3D, 0x1B, 0x37, 0x73, 0x1E, 0x7F, 0x3F};

unsigned char state_motor, state_sensor;
unsigned char autolcdflag, manulcdflag;

unsigned int cnt1s;
unsigned char cnt2s;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 131;

	cnt1s++;
	if(cnt1s >= 500)
	{
		cnt1s = 0;
		cnt2s++;
		SendRemote();
		if(cnt2s >= 2)
		{
			temp = (char)(((sens_temp/1024)*5 - 0.5)*50 - 50);		//calc temp
			humi = (char)(((sens_humi/1024)*5 - 0.5)*25);			//calc humi
			cnt2s = 0;
		}

		if(Timerflag == 1)
		{
			nTime++;
			nFND[0] = (TargetTime - nTime) / 10;
			nFND[1] = (TargetTime - nTime) % 10;
			PORTB = DISFND[nFND[1]]; 
			PORTD = DISFND[nFND[0]];
		}
	}
}

ISR(TIMER2_OVF_vect)	// Sonic Trigger Pulse
{
	TCNT2 = 0;
	sbi(PORTE,4);
	_delay_us(10);
	cbi(PORTE,4);
}

ISR(INT5_vect)
{
	TCCR2 = 0x00;
	CNTsonic = TCNT2;
	VALsonic = (((CNTsonic * 64) * 34300)/2000000);		//초음파 거리연산

	TCCR2 = ( 1 << CS20 ) | ( 0 << CS21 ) | ( 1 << CS22 );
}

ISR(INT6_vect)
{
	TCNT2 = 0;
}

ISR(INT7_vect)
{
	if(mAUTO == 1)			mAUTO = 0;
	else if(mAUTO == 0)	mAUTO = 1;
	else {}
}

ISR(USART0_RX_vect)
{
	Disable_ISR();
	
	Get_data = UDR0;
	if(1)	//not use
	{
		if(Get_data == 'A')
		{
			if(mAUTO == 1)			mAUTO = 0;
			else if(mAUTO == 0)	mAUTO = 1;
			else {}
			Get_data = 0;
		}

		else if(Get_data == 'B')
		{
			if(state_sensor == 1)			state_sensor = 0;
			else if(state_sensor == 0)	state_sensor = 1;
			Get_data = 0;
		}
		else if(Get_data == 'D')
		{
			target_temp+=5;
			Get_data = 0;
		}
		else if(Get_data == 'E')
		{
			target_temp-=5;
			Get_data = 0;
		}
		else if(Get_data == 'F')
		{
			target_humi+=5;
			Get_data = 0;
		}
		else if(Get_data == 'G')
		{
			target_humi-=5;
			Get_data = 0;
		}
		else if(Get_data == 'H')
		{
			if(mAUTO ==0)	TargetTime++;
			Get_data = 0;
		}
		else if(Get_data == 'I')
		{
			if(mAUTO ==0)	TargetTime--;
			Get_data = 0;
		}
		else if(Get_data == 'C')
		{
			Timerflag = 1;
			Get_data = 0;
		}
	}
	Enable_ISR();
}

int main(void)
{
	Init_main();

	while(1)
	{
		PORTB = DISFND[nFND[1]]; 
		PORTD = DISFND[nFND[0]];
		
		sens_humi = (float)ADC_Read(1);
		sens_temp = (float)ADC_Read(0);

		//if(PING & (1 << 0))		mAUTO = 1;		//auto mode on
		//else					mAUTO = 0;		//auto mode off


		if(mAUTO == 1)
		{			
			Lcd_Print_Num(0, 0, temp);
			Lcd_Print_Xy(0, 2, "C/");
			Lcd_Print_Num(0, 4, target_temp);
			Lcd_Print_Xy(0, 6, "C ");
			
			Lcd_Print_Num(0, 8, humi);
			Lcd_Print_Xy(0, 10, "%/");
			Lcd_Print_Num(0, 12, target_humi);
			Lcd_Print_Xy(0, 14, "%");

			if(sMOTOR == 1)		Lcd_Print_Xy(1, 0, "M_ON  ");
			else				Lcd_Print_Xy(1, 0, "M_OFF ");

			if(sSENSOR == 1)	Lcd_Print_Xy(1, 6, " S_ON ");
			else				Lcd_Print_Xy(1, 6, " S_OFF");

			if(state_sensor == 1)
			{
				sSENSOR = 1;
				if(((temp > target_temp)||(humi < target_humi))&&(VALsonic > 50))
				{
					MOTORON;
					sMOTOR = 1;
				}
				else 
				{
					MOTOROFF;
					sMOTOR = 0;
				}
			}
			else
			{
				sSENSOR = 0;
				if((temp > target_temp)||(humi < target_humi))
				{
					MOTORON;
					sMOTOR = 1;
				}
				else 
				{
					MOTOROFF;
					sMOTOR = 0;
				}
			}
		}

		else
		{
			Lcd_Print_Xy(0, 0, "MODE:Manual  ");
			Lcd_Print_Num(0,13,TargetTime);

			if(state_sensor == 1)	sSENSOR = 1;
			else					sSENSOR = 0;

			if(sMOTOR == 1)		Lcd_Print_Xy(1, 0, "M_ON  ");
			else				Lcd_Print_Xy(1, 0, "M_OFF ");

			if(sSENSOR == 1)	Lcd_Print_Xy(1, 6, " S_ON ");
			else				Lcd_Print_Xy(1, 6, " S_OFF");

			if(Timerflag == 1)
			{
				if(nTime >= TargetTime)	
				{
					Timerflag = 0;
					nTime = 0;
					MOTOROFF;
					sMOTOR = 0;
					nFND[0] = 0;//TargetTime / 10;
					nFND[1] = 0;//TargetTime % 10;
				}
				else
				{
					//nFND[0] = (TargetTime - nTime) / 10;
					//nFND[1] = (TargetTime - nTime) % 10;

					if(state_sensor == 1)
					{
						if(VALsonic > 50)
						{
							sSENSOR = 1;
							MOTORON;
							sMOTOR = 1;
						}
						else
						{
							sSENSOR = 1;
							MOTOROFF;
							sMOTOR = 0;
						}
					}

					else
					{
						sSENSOR = 0;
						MOTORON;
						sMOTOR = 1;
					}
				}
					
				
			}
			else
			{
				MOTOROFF;
				sMOTOR = 0;
			}
		}
			
		
		//_delay_ms(50);
		
	}
	return 0;
}

void Init_main(void)
{
	Disable_ISR();
	
	Lcd_Init();
	Timer0_Init();
	Timer2_Init();
	Ext_Interrupt5_Init();
	Ext_Interrupt6_Init();
	Ext_Interrupt7_Init();
	ADC_Init();
	Init_Uart(9600);
	
	//sbi(DDRE,3);
	sbi(DDRE,4);
	
	sbi(DDRG, 0);
	
	DDRB = 0xFF;
	DDRD = 0xFF;
	
	Enable_ISR();
}

void Lcd_Init(void)
{
	
	DDRC = 0xff; 
	DDRA = 0x07;
	
	_delay_ms(50);

	Command(0x3C);
	_delay_us(40);
	Command(0x0F);
	_delay_us(40);
	Command(0x01);
	_delay_ms(2);
	Command(0x06);
}

void Command(unsigned char byte)
{
	_delay_ms(30);
	PORTA = 0x00;
	_delay_us(1);
	PORTA = 0x04;
	_delay_us(1);
	PORTC = byte;
	PORTA = 0x03;
	_delay_ms(30);
	PORTA = 0x00;
}

void Data(unsigned char byte)
{
	PORTA = 0x01;
	_delay_us(1);
	PORTA = 0x05;
	_delay_us(1);
	PORTC = byte;
	PORTA = 0x01;
	_delay_ms(30);
	PORTA = 0x00;
}

void Put_Lcd_Char(char Lcd_Data)
{ 
     Data(Lcd_Data); 
     _delay_ms(20);
}

void Put_Lcd_String( char *Lcd_Data) 
{ 
	while(*Lcd_Data != 0x00) 
    { 
    	Put_Lcd_Char(*Lcd_Data); 
        ++Lcd_Data;
    } 
}

void Display_Position(unsigned char line, unsigned char col) 
{ 
     if( line == 0 ) 
     	Command( 0x80 + col );
     else 
        Command( 0xc0 + col ); 
}

void Lcd_Put_Char_Xy(unsigned char line, unsigned char col, unsigned char Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_Char( Lcd_Data );
}

void Lcd_Print_Xy(unsigned char line, unsigned char col, char *Lcd_Data)
{
	Display_Position( line, col );
	Put_Lcd_String( Lcd_Data );
}

void Lcd_Print_Num(unsigned char line, unsigned char col, unsigned char data)
{
	unsigned char Temp;
	
	Temp = data / 10;
	Lcd_Put_Char_Xy(line, col, Temp+48);
	Temp = data % 10;
	Lcd_Put_Char_Xy(line, col+1, Temp+48);
}

void Lcd_Print_U16digit(unsigned char line, unsigned char col, unsigned int data)	//0~65535
{
	unsigned char Temp;
	
	Temp = data / 10000;
	Lcd_Put_Char_Xy(line, col, Temp+48);
	Temp = (data % 10000) / 1000;
	Lcd_Put_Char_Xy(line, col+1, Temp+48);
	Temp = (data % 1000) / 100;
	Lcd_Put_Char_Xy(line, col+2, Temp+48);
	Temp = (data % 100) / 10;
	Lcd_Put_Char_Xy(line, col+3, Temp+48);
	Temp = data % 10;
	Lcd_Put_Char_Xy(line, col+4, Temp+48);
}

void Timer0_Init(void)

{                
	sbi( TIMSK, TOIE0 ); 
	TCNT0 = 0;	
		
	TCCR0 = ( 0 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02 );	
}

void Timer2_Init(void)        
{   
	sbi( TIMSK, TOIE2 );    
	TCNT2 = 55;
		
	TCCR2 = ( 1 << CS20 ) | ( 0 << CS21 ) | ( 1 << CS22 );	
}

void Ext_Interrupt5_Init(void)
{
	sbi( EICRB, ISC51 );    // FALLING EDGE ENABLE
	cbi( EICRB, ISC50 );  
	sbi( EIMSK, INT5  ); 
	cbi( EIFR , INTF5 ); 
	cbi(DDRE, 5);  
	sbi(PORTE, 5);	
}

void Ext_Interrupt6_Init(void)
{
	sbi( EICRB, ISC61 );    // RISING EDGE ENABLE
	sbi( EICRB, ISC60 );  
	sbi( EIMSK, INT6  ); 
	cbi( EIFR , INTF6 );  
	cbi(DDRE, 6);  
	sbi(PORTE, 6);
}

void Ext_Interrupt7_Init(void)
{
	sbi( EICRB, ISC71 );    // FALLING EDGE ENABLE
	cbi( EICRB, ISC70 );  
	sbi( EIMSK, INT7  ); 
	cbi( EIFR , INTF7 );  
	cbi(DDRE, 7);  
	sbi(PORTE, 7);
}


void ADC_Init(void)
{
	DDRF = 0x00;

	ADMUX = 0x00;
	ADCSRA = 0x00;

	sbi( ADCSRA, ADPS0 );
	sbi( ADCSRA, ADPS1 );
	sbi( ADCSRA, ADPS2 );		//프리스케일러 128분주

	sbi( ADCSRA, ADEN );		   	// ADC EN

	ADMUX = 1;
}

unsigned int ADC_Read(unsigned char Channel)
{
	unsigned int value = 0;

	ADMUX = Channel;
	
	sbi( ADCSRA, ADSC );		// ADC Conversion Start
	
	while( ADCSRA & ( 1 << ADSC ) ); 	// wait ADC conversion complete

	value = ADCL;
	value |= (unsigned int)ADCH << 8;
	
	return value;
}

void Init_Uart(unsigned int want_Baud)
{
	unsigned int Temp_UBRR;

	Temp_UBRR = 16000000L/(16L * want_Baud) - 1;   	
													
	UBRR0H = (Temp_UBRR >> 8);            
	UBRR0L = (Temp_UBRR & 0x00FF);
		
	UCSR0A = (0<<RXC0)  | (1<<UDRE0);		
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);  		
	UCSR0C = (3<<UCSZ00);				
		
	cbi( DDRE, 0 );                     
	sbi( DDRE, 1 );                
	
	UCSR0B |=  (1<<RXCIE0);	       
}

void Uart_Putch(unsigned char PutData)
{
	while(!( UCSR0A & (1<<UDRE0)) ); 
	UDR0 = PutData;            
}

void SendRemote(void)
{
	unsigned char parameter[8];

	parameter[0] = 0xFF;
	parameter[1] = mAUTO;
	parameter[2] = temp;
	parameter[3] = humi;
	parameter[4] = target_temp;
	parameter[5] = target_humi;
	parameter[6] = TargetTime;
	parameter[7] = 0xEE;

	for(unsigned char cnt=0; cnt<=7; cnt++)
	{
		Uart_Putch(parameter[cnt]);
	}	
}
