/*
 * BoardTest.cpp
 *
 * Created: 06-Mar-18 10:41:40 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0x01;
	PORTB = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTB ^= 0x01;
		_delay_ms(1000);
    }
}

