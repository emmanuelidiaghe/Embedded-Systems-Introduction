/*
 * SEVEN SEGMENT DISPLAY.cpp
 *
 * Created: 17-Mar-18 12:26:14 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* initialize ports and pins */
	int segment[10] = {0b01111111, 0b00000110,0b01011011,0b01001111,0b00100111,0b01101101};
	DDRA = 0b11111111;
	PORTA = 0b00000000;
	int i;
	
	
    while (1) 
    {
	for(i=0; i<6; i++)
	{
		PORTA = segment[i];
		_delay_ms(1000);
    } 
}
	}

