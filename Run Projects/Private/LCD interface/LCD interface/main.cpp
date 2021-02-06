/*
 * LCD interface.cpp
 *
 * Created: 14-Apr-17 10:42:19 PM
 * Author : Emancipator
 */ 
#define F_CPU 8000000
#include <avr/io.h>

#define usingLCD
#define usingGeneralAVR

/**********************
LCD PIN CONFIGURATION
*********************/
#define lcdD4Dir DDRA_B0
#define lcdD5Dir DDRA_B1
#define lcdD6Dir DDRA_B2
#define lcdD7Dir DDRA_B3
#define lcdEnDir DDRA_B4
#define lcdRsDir DDRA_B5

#define lcdD4 PORTA_B0
#define lcdD5 PORTA_B1
#define lcdD6 PORTA_B2
#define lcdD7 PORTA_B3
#define lcdEn PORTA_B4
#define lcdRs PORTA_B5

#include "C://Emancipator/Emancipator.h"

lcd display (16,2);  //creating an instance of the lcd class


int main(void)
{ 
	display.init();  //initialize the display
	delay_ms(200);
    display.writeText(0,0,"LCD DISPLAY");
	delay_ms(3000);
	display.clear();
	
    /* Replace with your application code */
    while (1) 
    {
		display.writeText(0,1,"PROJECT DESIGN"); //0-Row, 1-Column
		display.writeText(1,4,"EMMANUEL");      //1-Row, 4-Column
		delay_ms(10);	
	}
}