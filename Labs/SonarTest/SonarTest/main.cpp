/*
 * SonarTest.cpp
 *
 * Created: 08-Aug-17 12:08:50 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>

#define usingGeneralAVR
#define usingLCD
#define usingUSonic

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

#define US_DDR		DDRC
#define US_PORT		PORTC
#define US_PIN		PINC
#define US_TRIGER	PINC1
#define US_ECHO		PINC0

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