/*
 * Real clock.cpp
 *
 * Created: 08-Jun-17 11:17:36 AM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define usingGeneralAVR
#define usingI2C

/****** PIN DECLARATION OF THE
**********    RTC    ********/
#define i2cSclDir DDRD_B5
#define i2cSdaDir DDRD_B4
#define i2cSdaPin PIND_B4
#define i2cScl   PORTD_B5
#define i2cSda   PORTD_B4

#include "C:\Emancipator\Emancipator.h"

i2c rtcDs1307(0x68, I2C_8Bit);  //(Address, bit size (RTC)

/*****************************
VARIABLE DECLARATION
*****************************/

int second2, minute2, hour2, day2, date2, month2, year2;

int second = 00;
int minute = 23;
int hour   = 23;
int day    = 05;
int date   = 01;
int month  = 11;
int year   = 18; 

/*********************  This function sets the RTC time to
  04:21:00 PM, July 16,2017  ***************************/
void SetTime(void)
{		
	/*** Converts Decimal to BCD *****/
	second2 =  ((second/10*16) + (second%10));       //___second
	minute2 =  ((minute/10*16) + (minute%10));      //___minute
	hour2   =  ((hour/10*16)   +   (hour%10));     //___hour
	day2    =  ((day/10*16)    +    (day%10));    //___day
	date2   =  ((date/10*16)   +   (date%10));   //___date
	month2  =  ((month/10*16)  +  (month%10));  //___month
	year2   =  ((year/10*16)   +   (year%10)); //___year


	/*** Writes time(in BCD) to the
    appropriate addresses of the RTC *****/
	rtcDs1307.writeByte(0x0000, second2);
	rtcDs1307.writeByte(0x0001, minute2);
	rtcDs1307.writeByte(0x0002, hour2);
	rtcDs1307.writeByte(0x0003, day2);
	rtcDs1307.writeByte(0x0004, date2);
	rtcDs1307.writeByte(0x0005, month2);
	rtcDs1307.writeByte(0x0006, year2);
}


int main (void)
{
	rtcDs1307.init(); //Initialize the RTC
	_delay_ms(100);
	
	SetTime();  //Set the RTC
	
	while(1)
	{
		;
	}
		
}