/*
 * SonarTest.cpp
 *
 * Created: 08-Aug-17 12:08:50 PM
 * Author : Emancipator
 */ 

#define F_CPU 8000000
#include <avr/io.h>

#define usingGeneralAVR
#define usingLCD
#define usingUSonic

#define lcdD4Dir DDB0
#define lcdD5Dir DDB1
#define lcdD6Dir DDB2
#define lcdD7Dir DDB3
#define lcdEnDir DDB5
#define lcdRsDir DDB7

#define lcdD4 PB0
#define lcdD5 PB1
#define lcdD6 PB2
#define lcdD7 PB3
#define lcdEn PB5
#define lcdRs PB7

#define US_DDR		DDRD
#define US_PORT		PORTD
#define US_PIN		PORTD
#define US_TRIGER	PD1
#define US_ECHO		PD0

#include "C://Emancipator/Emancipator.h"

lcd display(16,2);

int main(void)
{
	DDRD  = 0x40;
	PORTD = 0x00;
	
	_delay_ms(100);
	display.init();
	usound_init();
	
	display.clear();
	_delay_ms(500);
	
	display.writeText(0,2,"INITIALIZING");
	display.writeText(1,0,"SONAR SYSTEM...");
	_delay_ms(2000);
	display.clear();
	_delay_ms(1000);
    /* Replace with your application code */
    while (1) 
    {
		uint32_t i = readDistance();
		
		display.writeText(0,0,"IN PROGRESS...");
		display.writeText(1,0,"Distance:");
		display.writeDec(1,10,i);
		display.writeText(1,13,"cm");
		if (i<10)
		{
			display.writeText(1,10,"00");
			display.writeDec(1,12,i);
			display.writeText(1,13,"cm");
			PORTD ^= 0x40;
			_delay_ms(500);
		}
		else if (i<100)
		{
			display.writeText(1,10,"0");
			display.writeDec(1,11,i);
			display.writeText(1,13,"cm");
			_delay_ms(500);
		}
		_delay_ms(500);
    }
}