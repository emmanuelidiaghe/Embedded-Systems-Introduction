/*
 * button test segment.cpp
 *
 * Created: 10-Apr-17 10:50:08 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	DDRD=0x00;
	PORTD=0x40;
	
	int count1=0;
	int segment[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7};

    /* Replace with your application code */
    while (1) 
    {
		if ((PIND && (1<<PD6))==0)
		{
			PORTC=segment[count1];
			_delay_ms(500);
			count1++;
		}
		if (count1==10)
		{
			count1=0;
		}
		if ((PIND && (1<<PD5))==0)
		{
			count1--;
			PORTC=segment[count1];
			_delay_ms(500);
		}
    }
}

