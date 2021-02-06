/*
 * SetRtcTime_button1.cpp
 *
 * Created: 20-Jul-17 10:33:19 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


#define usingSoftI2c
#define usingLcd
#define usingKeypad4X4

/***************************
****KEYPAD_CONGIGURATION****
***************************/
#define keypadPort           PORTC
#define keypadPortDirection  DDRC

#define keypadRow0 PINC_B0
#define keypadRow1 PINC_B1
#define keypadRow2 PINC_B2
#define keypadRow3 PINC_B3
#define keypadCol0 PINC_B4
#define keypadCol1 PINC_B5
#define keypadCol2 PINC_B6
#define keypadCol3 PINC_B7

/***************************
******LCD_CONGIGURATION*****
***************************/
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

/*************************
*****RTC_CONFIGURATION****
*************************/
#define i2cSclDir DDRD_B5
#define i2cSdaDir DDRD_B4
#define i2cSdaPin PIND_B4
#define i2cScl   PORTD_B5
#define i2cSda   PORTD_B4


#include "C://afrouno/afrouno.h"

lcd display (16,2);
i2c rtcDs1307(0x68, I2C_8Bit);  

/***************************
****VARIABLE DECLARATION****
****************************/
int key;
char press;
uint8_t i = 0;
int pad[17] = {1,2,3,0,4,5,6,0,7,8,9,0,0,0,0,0};
int RTC[17];
char second[5], minute[5], hour[5], day[5], date[5], month[5], year[5];
int second1, minute1, hour1, day1, date1, month1, year1;
int second2, minute2, hour2, day2, date2, month2, year2;


void SetTime(void)
{
		
	/*** Function to set the time of the RTC
	     in Binary-coded-Decimal(BCD) *****/
	second2 =  ((second1/10*16) + (second1%10));       //___second
	minute2 =  ((minute1/10*16) + (minute1%10));      //___minute
	hour2   =  ((hour1/10*16)   +   (hour1%10));     //___hour
	day2    =  ((day1/10*16)    +    (day1%10));    //___day
	date2   =  ((date1/10*16)   +   (date1%10));   //___date
	month2  =  ((month1/10*16)  +  (month1%10));  //___month
	year2   =  ((year1/10*16)   +   (year1%10)); //___year


	/*** Function addresses each of the time
	        to be set in the RTC      *****/
	rtcDs1307.writeByte(0x0000, second2);
	rtcDs1307.writeByte(0x0001, minute2);
	rtcDs1307.writeByte(0x0002, hour2);
	rtcDs1307.writeByte(0x0003, day2);
	rtcDs1307.writeByte(0x0004, date2);
	rtcDs1307.writeByte(0x0005, month2);
	rtcDs1307.writeByte(0x0006, year2);
}



int main(void)
{
	delay_ms(100);
	display.init();
	rtcDs1307.init();
	display.clear();
	
	display.writeText(0, 0, "INITIALIZING...");
	display.writeText(1, 0, "RTC Time set");
	delay_ms(2000);
	display.clear();
	
    /* Replace with your application code */
    while (1) 
    { 
		key = readKeypad4X4();

		if (i == 0 || i == 1)
		{
			display.writeText(0,0,"ENTER SECOND: ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 2) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 2 || i == 3)
		{
			display.writeText(0,0,"ENTER MINUTE: ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 4) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 4 || i == 5)
		{
			display.writeText(0,0,"ENTER HOUR:    ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 6) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 6 || i == 7)
		{
			display.writeText(0,0,"ENTER DAY:    ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 8) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 8 || i == 9)
		{
			display.writeText(0,0,"ENTER DATE:    ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 10) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 10 || i == 11)
		{
			display.writeText(0,0,"ENTER MONTH:  ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 12) display.clear();
				key = readKeypad4X4();
			}
		}
		if (i == 12 || i == 13)
		{
			display.writeText(0,0,"ENTER YEAR:   ");
			if (key != 255)
			{
				press = pad[key];
				RTC[i] = press;
				display.writeDec(1,i,RTC[i]);
				i++;
				_delay_ms(500);
				if(i == 14) display.clear();
				key = readKeypad4X4();
			}
		} 
		if (i == 14)
		{
			display.writeText(0,0,"TAP # TO LOAD");
			display.writeText(1,0,"TAP * TO CANCEL");
			if(key == 14)
			{
				 i = 20;
				 display.clear();
			}
			if(key == 12)
			{
				display.clear();
				_delay_ms(500);
				i = 0;
				key = readKeypad4X4();
			}
		}
		
		if(i == 20)
		{
			for (uint8_t j =0;j<101;j++)
			{
				display.writeText(0,0,"UPDATING TIME...");
				display.writeDec(1,6,j);
				display.writeText(1,8,"%");
				_delay_ms(100);
				if(j == 100) i = 21;
			}
		}
		if(i == 21)
		{
			display.writeText(0,0,"TIME UPDATED!   ");
			display.writeText(1,0,"    Thank You...");
			sprintf(second, "%d%d",  RTC[0],RTC[1]);
			sprintf(minute, "%d%d",  RTC[2],RTC[3]);
			sprintf(hour,   "%d%d",  RTC[4],RTC[5]);
			sprintf(day,    "%d%d",  RTC[6],RTC[7]);
			sprintf(date,   "%d%d",  RTC[8],RTC[9]);
			sprintf(month,  "%d%d",  RTC[10],RTC[11]);
			sprintf(year,   "%d%d",  RTC[12],RTC[13]);
			
			second1 = atoi(second);
			minute1 = atoi(minute);
			hour1   = atoi(hour);
			day1    = atoi(day);
			date1   = atoi(date);
			month1  = atoi(month);
			year1   = atoi(year);
			
			SetTime();
			_delay_ms(7000);
			display.clear();
			i = 22;
		}
		if (i == 22)
		{
			display.scroll(0,4);
			display.writeText(1,0,"Thank You...   ");
			_delay_ms(400);
		}
	}
}