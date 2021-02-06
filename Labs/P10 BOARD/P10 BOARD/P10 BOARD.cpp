/*
 * P10_BOARD.cpp
 *
 * Created: 20/03/2017 15:32:36
 *  Author: kelvin
 */ 


#define F_CPU 16000000
#define PRESCALLER 1024.0

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "char_code.h"

#define usingGeneralAVR
#define usingP10

#define maxDisplayRoll 2
#define maxDisplayCol  1

#define enablePinDir      DDRD_B2
#define addressAPinDir    DDRD_B3
#define addressBPinDir    DDRD_B4
#define shiftClockPinDir  DDRD_B5
#define latchClockPinDir  DDRD_B6
#define data1PinDir       DDRD_B7

#define enablePin         PORTD_B2
#define addressAPin       PORTD_B3
#define addressBPin       PORTD_B4
#define shiftClockPin     PORTD_B5
#define latchClockPin     PORTD_B6
#define data1Pin          PORTD_B7

#include "c://Emancipator/Emancipator.h"

p10 display;

char message[] = " WELCOME TO EMANCIPATOR EMBEDDED - HOME OF EMBEDDED SYSTEMS";
char speed = 25;

char message1[10][10] = {
	                    { "JESUS    " },
						{ "IS       " },
						{ "LORD     " },
						{ "JESUS    " },	
						{ "IS       " },
						{ "THE      " },
						{ "GREATEST " },	
					};

int main(void)
{
	 display.init(100, 40);     
	 display.clearDRAM(); 
	 //display.scrolDisplayLeft(message , speed);
	
	 display.writeText(&message1[0][0], LEFT );
	 delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[1][0], LEFT );
	 Delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[2][0], LEFT );
	 Delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[3][0], LEFT );
	 Delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[4][0], LEFT );
	 Delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[5][0], LEFT );
	 Delay_ms(2000);
	 
	 display.clearDRAM();
	 display.writeText(&message1[6][0], LEFT );
	 Delay_ms(2000);
	
	 display.clearDRAM();
	 
    while (1) 
	{
		 display.scrollText(message, speed);
		 delay_ms(500);
		 display.clearDRAM();
    }
}

