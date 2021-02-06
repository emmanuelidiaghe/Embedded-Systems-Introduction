/*
 * SetRtcTime_button1.cpp
 *
 * Created: 20-Jul-17 10:33:19 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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


#include "C://afrouno/afrouno.h"

lcd display (16,2);
/***************************
****VARIABLE DECLARATION****
****************************/

char keyPadCode[17] = "123A456B789C*0#D";

int ArrayConvert(int arr[], int n)
{
	char str[6][3];
	int i;
	char number[13] = {'\n'};
		
		for(i=0;i<n;i++) sprintf(str[i], "%d", arr[i]);
		for(i=0;i<n;i++) strcat (number,str[i]);
		
		i = atoi(number);
		return i;
}

int main(void)
{
	int num[6] = {13,20,5,4,3,55};
	int realnum;
	realnum = ArrayConvert(num,6);	
		
	while(1)
	{
		display.write(1,0,realnum);
	}
}
	