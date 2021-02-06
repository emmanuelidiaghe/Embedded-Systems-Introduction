/*
 * shift reg.cpp
 *
 * Created: 16-May-17 9:27:58 PM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/***************************************

Configure Connections

****************************************/

#define HC595_PORT 	PORTB
#define HC595_DDR 	DDRB
#define HC595_4_PORT PORTD
#define HC595_4_DDR DDRD

#define HC595_DS1_POS PB0
#define HC595_DS2_POS PB1
#define HC595_DS3_POS PB2
#define HC595_DS4_POS PB3		//Data pin (DS) pin location
#define HC595_SH1_CP_POS PB4	
#define HC595_SH2_CP_POS PB5
#define HC595_SH3_CP_POS PB6
#define HC595_4_SH4_CP_POS PD7	//Shift Clock (SH_CP) pin location 
#define HC595_ST_CP_POS PB7		//Store Clock (ST_CP) pin location

/***************************************
Configure Connections ***ENDS***
****************************************/

//Initialize HC595 System
uint8_t led_pattern[10]={63,6,91,79,102,109,125,7,127,111};

void HC595Init()
{
	//Make the Data(DS), Shift clock (SH_CP), Store Clock (ST_CP) lines output
	HC595_DDR|=((1<<HC595_SH1_CP_POS)|(1<<HC595_SH2_CP_POS)|(1<<HC595_SH3_CP_POS)|(1<<HC595_ST_CP_POS)|(1<<HC595_DS1_POS)|(1<<HC595_DS2_POS)|(1<<HC595_DS3_POS)|(1<<HC595_DS4_POS));
	HC595_4_DDR|=(1<<HC595_4_SH4_CP_POS);
}

//Low level macros to change data (DS)lines
#define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
#define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))

#define HC595Data2High() (HC595_PORT|=(1<<HC595_DS2_POS))
#define HC595Data2Low() (HC595_PORT&=(~(1<<HC595_DS2_POS)))

#define HC595Data3High() (HC595_PORT|=(1<<HC595_DS3_POS))
#define HC595Data3Low() (HC595_PORT&=(~(1<<HC595_DS3_POS)))

#define HC595Data4High() (HC595_PORT|=(1<<HC595_DS4_POS))
#define HC595Data4Low() (HC595_PORT&=(~(1<<HC595_DS4_POS)))

//Sends a clock pulse on SH_CP line
//Sends a clock pulse on ST_CP line
void HC595Latch()
{
	//Pulse the Store Clock
	HC595_PORT|=(1<<HC595_ST_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT&=(~(1<<HC595_ST_CP_POS));//LOW
	_delay_loop_1(1);
}


void HC595Pulse1()
{
	//Pulse the Shift Clock

	HC595_PORT|=(1<<HC595_SH1_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH1_CP_POS));//LOW

}

void HC595Pulse2()
{
	//Pulse the Shift Clock

	HC595_PORT|=(1<<HC595_SH2_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH2_CP_POS));//LOW

}
void HC595Pulse3()
{
	//Pulse the Shift Clock

	HC595_PORT|=(1<<HC595_SH3_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH3_CP_POS));//LOW

}
void HC595Pulse4()
{
	//Pulse the Shift Clock

	HC595_4_PORT|=(1<<HC595_4_SH4_CP_POS);//HIGH

	HC595_4_PORT&=(~(1<<HC595_4_SH4_CP_POS));//LOW

}

void Write1(uint8_t data1)
{
	//Send each 8 bits serially
	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data1 & 0b10000000)
		{
			HC595Data1High();
		}
		else
		{
			HC595Data1Low();
		}
		HC595Pulse1();	
		data1=data1<<1;
	}
}


void Write2(uint8_t data2)
{
	//Send each 8 bits serially
	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data2 & 0b10000000)
		{
			HC595Data2High();
		}
		else
		{
			HC595Data2Low();
		}
		HC595Pulse2();
		data2=data2<<1;
	}
}

void Write3(uint8_t data3)
{
	//Send each 8 bits serially
	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data3 & 0b10000000)
		{
			HC595Data3High();
		}
		else
		{
			HC595Data3Low();
		}
		HC595Pulse3();
		data3=data3<<1;
	}
}

void Write4(uint8_t data4)
{
	//Send each 8 bits serially
	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data4 & 0b10000000)
		{
			HC595Data4High();
		}
		else
		{
			HC595Data4Low();
		}
		HC595Pulse4();
		data4=data4<<1;
	}
}

void HC595WRITE()
{
	for(uint8_t i=0;i<10;i++)
	{
		Write1(led_pattern[i]);
		Write2(led_pattern[i]);
		Write3(led_pattern[i]);
		Write4(led_pattern[i]);
		HC595Latch();
		_delay_ms(500);
	}
}

 int main()
{
	DDRC=0xFF;
	PORTC=0x00;
	
	sei();
	
	TCCR1B = (1<<CS12);
	TIMSK =  (1<<OCIE1A);
	
	OCR1A = 62500;
	
	//Initialize HC595 system
	HC595Init();

	while(1)
	{
		//HC595WRITE();
		for(uint8_t i=0;i<10;i++)
		{
			Write1(led_pattern[i]);
			Write2(led_pattern[i]);
			Write3(led_pattern[i]);
			Write4(led_pattern[i]);
			
			_delay_ms(500);
			HC595Latch();
		}
	}
}