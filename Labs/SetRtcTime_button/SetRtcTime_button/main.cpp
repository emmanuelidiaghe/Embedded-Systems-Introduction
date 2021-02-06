/*
 * Real clock.cpp
 *
 * Created: 08-Jun-17 11:17:36 AM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


/****** PIN DECLARATION OF THE
**********    RTC    ********
#define i2cSclDir DDRD_B5
#define i2cSdaDir DDRD_B4
#define i2cSdaPin PIND_B4
#define i2cScl   PORTD_B5
#define i2cSda   PORTD_B4*/

#define lcdD4Dir DDRA_B0
#define lcdD5Dir DDRA_B1
#define lcdD6Dir DDRA_B2
#define lcdD7Dir DDRA_B3
#define lcdEnDir DDRA_B5
#define lcdRsDir DDRA_B7

#define lcdD4 PORTA_B0
#define lcdD5 PORTA_B1
#define lcdD6 PORTA_B2
#define lcdD7 PORTA_B3
#define lcdEn PORTA_B5
#define lcdRs PORTA_B7

#define keypadPort PORTC
#define keypadPortDirection DDRC

#define keypadRow0 PORTC_B0
#define keypadRow1 PORTC_B1
#define keypadRow2 PORTC_B2
#define keypadRow3 PORTC_B3
#define keypadCol0 PORTC_B4
#define keypadCol1 PORTC_B5
#define keypadCol2 PORTC_B6
#define keypadCol3 PORTC_B7

#define usingLcd
//#define usingSoftI2c
#define usingKeypad4X4

#include "c:/Afrouno/afrouno.h"

lcd display(16,2);
i2c rtcDs1307(0x68, I2C_8Bit);  //Address, bit size (RTC)

/*****************************
VARIABLE DECLARATION
*****************************/

uint8_t i = 0;
char RTC[20];
//int keypadCode[17] = {1,2,3,0,4,5,6,0,7,8,9,0,0,0,0,0};
char keyPadCode[17] = "123A456B789C*0#D";
char second[2], minute[2], hour[2], day[2], date[2], month[2], year[2];
int second1, minute1, hour1, day1, date1, month1, year1;
int key,press;

void SetTime(void)
{
		
	/*** Function to set the time of the RTC
	     in Binary-coded-Decimal(BCD) *****/
	second1 =  ((second/10*16) + (second%10));       //___second
	minute1 =  ((minute/10*16) + (minute%10));      //___minute
	hour1   =  ((hour/10*16)   +   (hour%10));     //___hour
	day1    =  ((day/10*16)    +    (day%10));    //___day
	date1   =  ((date/10*16)   +   (date%10));   //___date
	month1  =  ((month/10*16)  +  (month%10));  //___month
	year1   =  ((year/10*16)   +   (year%10)); //___year


	/*** Function addresses each of the time
	        to be set in the RTC      *****/
	rtcDs1307.writeByte(0x0000, second1);
	rtcDs1307.writeByte(0x0001, minute1);
	rtcDs1307.writeByte(0x0002, hour1);
	rtcDs1307.writeByte(0x0003, day1);
	rtcDs1307.writeByte(0x0004, date1);
	rtcDs1307.writeByte(0x0005, month1);
	rtcDs1307.writeByte(0x0006, year1);
}


int main (void)
{
	_delay_ms(100);
	display.init();
	//rtcDs1307.init(); //Initialize the RTC
	delay_ms(100);
	
	display.clear();
	_delay_ms(1000);
	
	//SetTime();  //Set the RTC
	
	while(1)
	{
		
		display.writeText(0,0,"ENTER PASSWORD:");
		key = readKeypad4X4();
		
		if(key != 255)    //If a key on the keypad is pressed
		{
			display.writeText(1,i+6,"*");
			press = keyPadCode[key];
			RTC[i] = press;
			i++;
			_delay_ms(500);
		}
		
		if(i == 2)
		{
			sprintf(second,"%d%d",RTC[0],RTC[1]);
			sprintf(minute,"%d%d",RTC[2],RTC[3]);
			sprintf(hour,"%d%d",RTC[4],RTC[5]);
			sprintf(day,"%d%d",RTC[6],RTC[7]);
			sprintf(date,"%d%d",RTC[8],RTC[9]);
			sprintf(month,"%d%d",RTC[10],RTC[11]);
			sprintf(year,"%d%d",RTC[12],RTC[13]);
			
			second1 = atoi(second);
			minute1 = atoi(minute);
			hour1   = atoi(hour);
			day1    = atoi(day);
			date1   = atoi(date);
			month1  = atoi(month);
			year1   = atoi(year);
			
			display.write(1,10,second1);
			
		}
	}
		
}