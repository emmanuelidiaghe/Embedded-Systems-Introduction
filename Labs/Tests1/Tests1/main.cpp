/*
*
*
*/
#define F_CPU 16000000
#include <avr/io.h>
#include <string.h>

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

#define usingGeneralAVR
#define usingLcd
#define usingUart

#include "c://Emancipator/Emancipator.h"

lcd display (16,2);
uart serial;

char msg[16];
uint8_t dispMsg; 
 
int main(void)
{
	_delay_ms(200);
	
	serial.init(9600);
	display.init();
	
	display.clear();
	_delay_ms(500);
	
	serial.writeLine("WELCOME TO EMANCIPATOR EMBEDDED...");
	serial.writeLine(" ");
	delay_ms(1000);
	serial.writeLine("This is a UART test!");
	serial.writeLine(" ");
	_delay_ms(1000);
	
	while(1)
	{
		if (serial.isDataReady())
		{
		    //serial.readText("Emancipator");
			dispMsg = serial.read();
			//serial.writeText(n);
			//display.writeText(1,0,(char*)dispMsg);
			//serial.writeLine((char*)dispMsg);
		}
		//strcpy((char*)dispMsg,msg);
		display.writeText(1,0,(char*)dispMsg);
		delay_ms(100);		
	}
}