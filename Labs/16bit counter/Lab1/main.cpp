/*
 * Lab1.cpp
 *
 * Created: 04-Apr-17 12:40:41 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA=0xFF;
	PORTA=0x00;
	DDRC=0xFF;
	PORTC=0x00;
	
	int count1;
	int count2;
    /* Replace with your application code */
	while(1)
	{
		for (count1=0;count1<255;count1++)
		{
			for (count2=0;count2<255;count2++)
			{
				PORTA=count2;
				_delay_ms(100);
			}
			PORTC=count1;
			_delay_ms(100);
			
		}
    }

}