/*
 * BoardTesting.cpp
 *
 * Created: 14-Mar-18 10:31:17 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//initialize Ports and pins
	DDRA  = 0b11111111;
	PORTA = 0b00000000;
	int i;
	
	uint8_t count[8] = {PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7};
    while (1) 
    {
		for (i = 0; i<9; i++)
		{
			PORTA = (1<<count[i]);
			_delay_ms(100);
		}
		for (i = 7; i>0; i--)
		{
			PORTA = (1<<count[i]);
			_delay_ms(100);
		}
    }
}