/*
 * LCD interface.cpp
 *
 * Created: 14-Apr-17 10:42:19 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>

#define usingLcd

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


#include "c://afrouno/afrouno.h"
lcd display (16,2);


int main(void)
{ 
	display.init();
	delay_ms(50);
	
	display.clear();
	delay_ms(100);
	
	display.writeText(0,0,"INITIALIZING");
	display.writeText(1,0,"PLEASE WAIT...");
	delay_ms(3000);
	display.clear();
	
    /* Replace with your application code */
    while (1) 
    {
		display.writeText(0,2,"PROJECT DESIGN");
		display.writeText(1,6,"EMMANUEL");
		display.scroll(0,1);
		delay_ms(400);
		
	}
}

