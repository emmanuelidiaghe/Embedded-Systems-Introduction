/*
 * Real clock.cpp
 *
 * Created: 08-Jun-17 11:17:36 AM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define usingGeneralAVR
#define usingI2C
#define usingLcd

/**************************************
******** PIN CONFIGURATIONS ***********
**************************************/

/******  SHIFT_REGISTER   ******/
#define HC595_DDR 	DDRB
#define HC595_4_DDR DDRD
#define HC595_PORT 	 PORTB
#define HC595_4_PORT PORTD

#define HC595_DS1_POS       PB0
#define HC595_DS2_POS       PB1
#define HC595_DS3_POS       PB2
#define HC595_DS4_POS       PB3	
#define HC595_SH1_CP_POS    PB4
#define HC595_SH2_CP_POS    PB5
#define HC595_SH3_CP_POS    PB6
#define HC595_ST_CP_POS     PB7
#define HC595_4_SH4_CP_POS  PD7

/*******   RTC   *********/
#define i2cSclDir DDRD_B5
#define i2cSdaDir DDRD_B4
#define i2cSdaPin PIND_B4
#define i2cScl   PORTD_B5
#define i2cSda   PORTD_B4

/********   LCD   ********/
#define lcdD4Dir DDRA_B0
#define lcdD5Dir DDRA_B1
#define lcdD6Dir DDRA_B2
#define lcdD7Dir DDRA_B3
#define lcdRsDir DDRA_B7
#define lcdEnDir DDRA_B5

#define lcdD4 PORTA_B0
#define lcdD5 PORTA_B1
#define lcdD6 PORTA_B2
#define lcdD7 PORTA_B3
#define lcdRs PORTA_B7
#define lcdEn PORTA_B5

#include "c://Emancipator/Emancipator.h"

lcd display (16,2);             //LCD resolution 16x2
i2c rtcDs1307(0x68, I2C_8Bit);  //Address, bit size (RTC)

/*****************************
     VARIABLE DECLARATION
*****************************/
uint8_t rtcHour;
uint8_t rtcData[8];
uint8_t rtcTime[15];
uint8_t year            = 20;
uint8_t led_pattern[10] = {63,6,91,79,102,109,125,7,127,111};
const char* DOW[][8]    = {"        ","  SUNDAY   ","  MONDAY   ","  TUESDAY   "," WEDNESDAY  ","  THURSDAY  ","  FRIDAY   "," SATURDAY    "};
const char* MONTH[][13] = {"        "," JANUARY ","     FEB. ","   MARCH ","   APRIL ","     MAY ","    JUNE ","    JULY "," AUGUST ","  SEPT. ","OCTOBER ","NOVEMBER ","DECEMBER "};


/**********************************
      FUNCTION DECLARATION
**********************************/
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

void HC595Latch()
{
	//Common Latch for all Shift Registers
	HC595_PORT|=(1<<HC595_ST_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT&=(~(1<<HC595_ST_CP_POS));//LOW
	_delay_loop_1(1);
}

void HC595Pulse1()
{
	//Pulse the 1st Shift Clock
	HC595_PORT|=(1<<HC595_SH1_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH1_CP_POS));//LOW
}

void HC595Pulse2()
{
	//Pulse the 2nd Shift Clock

	HC595_PORT|=(1<<HC595_SH2_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH2_CP_POS));//LOW

}

void HC595Pulse3()
{
	//Pulse the 3rd Shift Clock

	HC595_PORT|=(1<<HC595_SH3_CP_POS);//HIGH

	HC595_PORT&=(~(1<<HC595_SH3_CP_POS));//LOW

}

void HC595Pulse4()
{
	//Pulse the 4th Shift Clock

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
	//This function writes the 1st shift register
}

void Write2(uint8_t data2)
{
	for(uint8_t j=0;j<8;j++)
	{
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
	//This function writes the 2nd shift register
}

void Write3(uint8_t data3)
{
	for(uint8_t k=0;k<8;k++)
	{
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
	//This function writes the 3rd shift register
}

void Write4(uint8_t data4)
{
	for(uint8_t l=0;l<8;l++)
	{
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
	//This function writes the 4th shift register
}


void HC595WRITE()
{  
	//Sends time data to each 7_segment
		
	Write1(led_pattern[rtcTime[2]]);
	Write2(led_pattern[rtcTime[3]]);
	Write3(led_pattern[rtcTime[4]]);
	Write4(led_pattern[rtcTime[5]]);
	HC595Latch();
}

void Convert(void)
{
	/****** This converts the RTC Data from BCD to Decimal, as well as controls
	                          AM and PM indicators ******/
	
	if (((rtcData[2] > 0b00010010) & (rtcData[2] < 0b00100000)) | (rtcData[2] > 0b00100001))
	{
		rtcHour = (rtcData[2] % 0b00010010);
		PORTC = 0x04; // PM indicator
	}
	else if (rtcData[2] == 0b00000000)
	{
		rtcHour = 0b00010010;
		PORTC = 0x02; //AM indicator
	}
	else if (rtcData[2] == 0b00100000)
	{
		rtcHour = 0b00001000;
		PORTC = 0x04; // PM indicator
	}
	else if (rtcData[2] == 0b00100001)
	{
		rtcHour = 0b00001001;
		PORTC = 0x04; // PM indicator
	}
     else if (rtcData[2] == 0b00010010)
    {
		rtcHour = 0b00010010;
        PORTC = 0x04; //PM indicator
    }
	else
	{ 
		rtcHour = rtcData[2];
		PORTC = 0x02;
	}
	
	rtcTime[0]   =  ( rtcData[0] & 0b00001111);  //second
	rtcTime[1]   = (( rtcData[0] >> 4) & 0b00000111);
	
	rtcTime[2]   =  ( rtcData[1] & 0b00001111);  //minute
	rtcTime[3]   = (( rtcData[1] >> 4) & 0b00000111);
	
	rtcTime[4]   =  ( rtcHour & 0b00001111);     //Hour
	rtcTime[5]   = (( rtcHour >> 4) & 0b00000111);
	
	rtcTime[6]   =  ( rtcData[3] & 0b00001111);  //day of week
	rtcTime[7]   = (( rtcData[3] >> 4) & 0b00000111);
	
	rtcTime[8]   =  ( rtcData[4] & 0b00001111);  //date
	rtcTime[9]   = (( rtcData[4] >> 4) & 0b00000111);
	
	rtcTime[10]  =  ( rtcData[5] & 0b00001111);  //month
	rtcTime[11]  = (( rtcData[5] >> 4) & 0b00000111);
	
	rtcTime[12]  =  ( rtcData[6] & 0b00001111);  //year
	rtcTime[13]  = (( rtcData[6] >> 4) & 0b00000111);

}

void LcdDisplay(void)
{
	/******** Displays Initialization protocols
	as well as Day, Month, Date and Year of the RTC *******/
	
	display.writeText(0,3,DOW[0][rtcTime[6]]);
	
	if (rtcTime[10]==0 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][10]);
	} 
	else if(rtcTime[10]==1 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][11]);
	}
	else if (rtcTime[10]==2 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][12]);
	}
	else
	{
		display.writeText(1,0,MONTH[0][rtcTime[10]]);
	}
	
	display.writeDec(1,9,rtcTime[9]);
	display.writeDec(1,10,rtcTime[8]);
	display.writeText(1,11,",");
	display.writeDec(1,12,year);
	display.writeDec(1,14,rtcTime[13]);
	display.writeDec(1,15,rtcTime[12]);
	_delay_ms(10);
}



int main(void)
{
	DDRC  = 0xFF;
	PORTC = 0x00;
	
	rtcDs1307.init(); //Initialize RTC
	  display.init(); //Initialize LCD
	  HC595Init();    //Initialize 595
	  _delay_ms(100);
	
	display.writeText(0,0,"SYSTEM STARTUP..");
	delay_ms(1000);
	display.clear();
	for (uint8_t i=0;i<101;i++)
	{
		display.writeText(0,0,"UPDATING TIME...");
		display.writeDec(1,7,i);
		display.writeText(1,10,"%");
		_delay_ms(25);
	}
	delay_ms(1000);
	display.clear();
	_delay_ms(500);
	
	sei();
	
	TCCR1B = (1<<CS12);
	TIMSK =  (1<<OCIE1A);
	
	OCR1A = 62499;
	
	/* Replace with your application code */
	while (1)
	{
		rtcDs1307.readBytes(0x0000, rtcData, 8);
		
		Convert();
		
		HC595WRITE();
		
		LcdDisplay();
		
		_delay_ms(1);
	}
}

ISR(TIMER1_COMPA_vect)
{	
	Convert();
	
	PORTC ^= 0x01;
	_delay_ms(500);
}