/*
 * GccApplication1.cpp
 *
 * Created: 05-Apr-17 12:41:04 PM
 * Author : Emancipator
 */ 
#define  F_CPU 16000000//External clock source
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC  = 0xE0; //set for output
	PORTC = 0x00; //initialized to off
	
    /* Replace with your application code */
    while (1) 
    {
		PORTC = 0x80;  //red color
		_delay_ms(300); // delays for 3/10-a-second
		PORTC = 0x40; //green color
		_delay_ms(300);  //delays for 3/10-a-second
		PORTC = 0x20; //green color
		_delay_ms(300);  //delays for 3/10-a-second
    }
}