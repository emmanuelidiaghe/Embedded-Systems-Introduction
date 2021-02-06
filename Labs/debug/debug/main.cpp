/*
 * debug.cpp
 *
 * Created: 24-May-18 12:38:42 PM
 * Author : Emancipator
 */ 
#define F_CPU 000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB  = 0xFF;
	PORTB = 0xFF;
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB = 0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
	}
}

