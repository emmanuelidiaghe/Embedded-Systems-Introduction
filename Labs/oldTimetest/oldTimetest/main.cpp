/*
 * oldTimetest.cpp
 *
 * Created: 30-Apr-18 11:11:27 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	
	PORTA = 0x00;
	PORTC = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		PORTA = 0xFF;
		_delay_ms(1000);
		PORTA = 0x00;
		
		PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
    }
}