/*
 * LDR ADC.cpp
 *
 * Created: 15-Apr-17 12:05:02 PM
 * Author : Emmanuel
 */ 
#define F_CPU 1000000
#include <avr/io.h>

#define usingGeneralAVR
#define usingLCD // using LCD from afrouno library

#define lcdD4Dir DDRC_B2
#define lcdD5Dir DDRC_B3
#define lcdD6Dir DDRC_B4
#define lcdD7Dir DDRC_B5
#define lcdEnDir DDRC_B6
#define lcdRsDir DDRC_B7

#define lcdD4 PORTC_B2
#define lcdD5 PORTC_B3
#define lcdD6 PORTC_B4
#define lcdD7 PORTC_B5
#define lcdEn PORTC_B6
#define lcdRs PORTC_B7

#include "C://Emancipator/Emancipator.h"

lcd display (16,2); //LCD resolution 16x2

int main(void)
{
	display.init(); //initialize LCD
	delay_ms(1000);
	display.clear();
	delay_ms(10);
	
	display.writeText(0,7,"09:43");
	display.writeText(1,0,"PLEASE WAIT...");
	
while(1)
{
	display.writeText(0,7,"09:43");
	display.writeText(1,0,"PLEASE WAIT...");
}
}

