/*
 * SonarTest.cpp
 *
 * Created: 08-Aug-17 12:08:50 PM
 * Author : Emancipator
 */ 
#define F_CPU 6000000
#include <avr/io.h>

#define usingGeneralAVR
#define usingLCD
#define usingUSonic

#define lcdD4Dir DDRB_B2
#define lcdD5Dir DDRB_B3
#define lcdD6Dir DDRB_B4
#define lcdD7Dir DDRB_B5
#define lcdEnDir DDRB_B1
#define lcdRsDir DDRB_B0

#define lcdD4 PORTB_B2
#define lcdD5 PORTB_B3
#define lcdD6 PORTB_B4
#define lcdD7 PORTB_B5
#define lcdEn PORTB_B1
#define lcdRs PORTB_B0

#define US_DDR		DDRA
#define US_PORT		PORTA
#define US_PIN		PINA
#define US_TRIGER	PINA0
#define US_ECHO		PINA1

#include "C://Emancipator/Emancipator.h"
lcd display(16,2);

int main(void)
{	
	//DDRC = (1<<DDC0)|(1<<DDC1)|(1<<DDC2);
	//PORTC = (1<<PC0)|(1<<PC1)|(1<<PC2);
	DDRD = (1<<DDD7);
	PORTD = (1<<PD7);
	
	
	
	_delay_ms(100);
	display.init();
	usound_init();
	
	display.writeText(0,2,"INITIALIZING");
	display.writeText(1,2,"WATER LEVEL...");
	_delay_ms(4000);
	display.clear();

    while (1) 
    {
		uint32_t i = readDistance();
		
		display.writeText(0,0,"MEASURING...");
		display.writeText(1,0,"Level:");
		display.writeDec(1,10,i);
		display.writeText(1,13,"cm");
		if (i<10)
		{
			display.writeText(1,10,"00");
			display.writeDec(1,12,i);
			display.writeText(1,13,"cm");
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
		if(i<50)
		{
			//PORTC &= ~(1<<PC0)|(1<<PC1)|(1<<PC2);
			PORTD &= ~(1<<PD7);
		}
		if (i>50)
		{
			//PORTC = (1<<PC0)|(1<<PC1)|(1<<PC2);
			PORTD = (1<<PD7);
		}
    }
}