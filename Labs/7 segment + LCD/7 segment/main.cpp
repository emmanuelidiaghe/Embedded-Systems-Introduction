/*
 * 7 segment.cpp
 *
 * Created: 21-Apr-17 11:45:08 AM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>

#define usingLcd // using LCD from afrouno library
#define usingPort

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

#include "C://afrouno1/afrouno.h"
lcd display (16,2); //LCD resolution 16x2

int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	
	display.init();
	display.clear();
	delay_ms(100);
	display.clear();
	
	
	display.writeText(0,0,"INITIALIZING");
	display.writeText(1,0,"PLEASE WAIT...");
	_delay_ms(2000);
	display.clear();
	
	
	
	int segment[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7};
	int count;
    /* Replace with your application code */
    while (1) 
    {
		for (count=0;count<10;count++)
		{
			display.writeText(0,0,"SEGMENT COUNT");
			display.writeDec(1,7,count);
			PORTC=segment[count];
			delay_ms(1000);
		}
    }
}

