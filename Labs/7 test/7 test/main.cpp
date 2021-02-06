/*
 * Timer1.cpp
 *
 * Created: 11-Apr-17 1:33:48 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA  = 0b11111111;
	PORTA = 0b00000000;
	
    /* Replace with your application code */
    while (1)
    {
		PORTA = 0b11111111;
		_delay_ms(500);
		PORTA = 0b00000000;
		_delay_ms(500);
    }
}


