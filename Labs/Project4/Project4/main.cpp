/*
 * SetRtcTime_button1.cpp
 *
 * Created: 20-Jul-17 10:33:19 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <string.h>


/***************************
******LCD_CONGIGURATION*****
***************************/
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

#define usingLcd
#define usingKeypad4X4

/***************************
****KEYPAD_CONGIGURATION****
***************************/
#define keypadPort           PORTB
#define keypadPortDirection  DDRB

#define keypadRow0 PINB_B0
#define keypadRow1 PINB_B1
#define keypadRow2 PINB_B2
#define keypadRow3 PINB_B3
#define keypadCol0 PINB_B4
#define keypadCol1 PINB_B5
#define keypadCol2 PINB_B6
#define keypadCol3 PINB_B7

#include "C://Emancipator/Emancipator.h"

lcd display (16,2);
/***************************
****VARIABLE DECLARATION****
****************************/
int key;
char press;
uint8_t i = 0, j =0, k = 0;
int segment[10]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};
char keyPadCode[17] = "123A456B789C*0#D";
char user[16] = "2017";
char test[16] = "";

int main(void)
{
	DDRC  = 0xFF;
	PORTC = 0x00;
	
	DDRD  = 0xFF;
	PORTD = 0x00;
	
	delay_ms(50);
	display.init();
	display.clear();
	
	display.writeText(0, 0, "INITIALIZING...");
	display.writeText(1, 0, "Password Test");
	delay_ms(2000);
	display.clear();
	
    /* Replace with your application code */
    while (1) 
    { 
		display.writeText(0,0,"ENTER PASSWORD:");
		key = readKeypad4X4(); 
		 
		if(key != 255)    //If a key on the keypad is pressed
		{
			if (j == 1)
			{
				display.clearLine(1,0);
			}
			display.writeText(1,i+6,"*");
			press = keyPadCode[key];
		    test[i] = press;
		    i++;
			k++;
			j = 0;
			_delay_ms(500);
		}
		
		if((k==4 || k==8) && (strcmp(test, user)!=0))
		{
			display.writeText(0,0," ACCESS DENIED!");
			display.writeText(1,0,"re-enter pWord");
			i = 0;
			j = 1;
			_delay_ms(100);
		}
		
		while ((k == 0 && k < 4) && (key == 255))
		{
			key = readKeypad4X4();
			PORTC = segment[0];
			PORTD = 128;
			_delay_ms(1);
			PORTC = segment[3];
			PORTD = 64;
			_delay_ms(1);
		}
		while ((k == 4 && k < 8) && (key == 255))
		{
			key = readKeypad4X4();
			PORTC = segment[0];
			PORTD = 128;
			_delay_ms(1);
			PORTC = segment[2];
			PORTD = 64;
			_delay_ms(1);
		}
		while ((k == 8 && k < 12) && (key == 255))
		{
			key = readKeypad4X4();
			PORTC = segment[0];
			PORTD = 128;
			_delay_ms(1);
			PORTC = segment[1];
			PORTD = 64;
			_delay_ms(1);
		}
		
		while(strcmp(test, user)==0)   //If the user inputs the correct password
		{
			display.writeText(0,0,"VERIFYING...    ");
			display.writeText(1,6,"       ");
			for(uint8_t a=0;a<12;a++)
			{
				display.writeText(1,a,".");
				_delay_ms(200);
			}
			display.clear();
			_delay_ms(1000);
			while(1)
			{
				display.writeText(0,4,"VERIFIED");
				display.writeText(1,1,"ACCESS GRANTED!");
				_delay_ms(50);
			}
		  } 
			
		while(strcmp(test, user)!=0 && k == 12)   //If the user inputs an incorrect password the 3rd time
		{
			display.clear();
			display.writeText(0,0,"VERIFYING...    ");
			display.writeText(1,6,"       ");
			for(uint8_t a=0;a<12;a++)
			{
				display.writeText(1,a,".");
				_delay_ms(200);
			}
			display.clear();
			_delay_ms(1000);
			while(1)
			{
				display.writeText(0,0,"SECURITY ALERT!!");
				display.writeText(1,4,"Dial 911");
				_delay_ms(500);
				display.clear();
				_delay_ms(500);
			}
		}
	}
}