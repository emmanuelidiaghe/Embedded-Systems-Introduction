/*
 * ATtiny2313.cpp
 *
 * Created: 28-Dec-17 3:55:46 PM
 * Author : Emancipator
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD = 0x64;
	PORTD = 0x00;
    
    while (1) 
    {
		PORTD ^= 0x64;
		_delay_ms(500);
    }
}

