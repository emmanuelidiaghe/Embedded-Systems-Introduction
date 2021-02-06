/*
 * Blinking.cpp
 *
 * Created: 15-May-18 11:41:56 AM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 255;
	PORTB = 0;
	
    /* Replace with your application code */
    while (1) 
	{
		PORTB = 255;
		_delay_ms(1000);
		
		PORTB = 0;
		_delay_ms(1000);
	
	}
}

