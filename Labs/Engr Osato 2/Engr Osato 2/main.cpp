/*
*
*
*/
#define	F_CPU	16000000
#define usingGeneralAVR
#define usingLcd
#define usingAdc

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

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

lcd display(16,2);

uint8_t data;
uint8_t counter = 0;

char num_in[20];
char num_out[20];

uint8_t ch0;
uint8_t ch1;
uint8_t inFlag = 0;
uint8_t outFlag = 0;


int main(void)
{
	DDRC  = 0xFF;
	DDRA  = 0x00;
	PORTC = 0x00;
	
	display.init();
	analogRefInit(1);
	_delay_ms(100);
	
	display.writeText(0,0,"VISITOR COUNTER");
	display.writeText(1,0,"INITIALIZING...");
	_delay_ms(5000);
	
	display.clear();
	_delay_ms(1000);


	while (1)
	{
		display.writeText(0,0,"VISITOR COUNTER");
		display.writeText(1,0,"Occupants:");
		display.writeDec(1,10,counter);
		
		ch0 = analogeReadPin(0);
		ch1 = analogeReadPin(1);
		
		
		if (ch0 > ch1)
		{
			counter++;
			display.writeDec(1,10,counter);
		}
	}
	
}


