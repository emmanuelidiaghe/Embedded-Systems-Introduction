/*
 * RGB using counter.cpp
 *
 * Created: 12-Apr-17 10:30:21 AM
 * Author : Emancipator
 */ 
#define  F_CPU 12000000 // External clock source
#include <avr/io.h>


int main(void)
{
	DDRC=0xE0;  // set for output
	PORTC=0x00; // initialized to off
	int repeatCount=0;
	
	TCCR1B |= (1<<CS10);  // no pre_scaler
	
    /* Replace with your application code */
    while (1) 
    {
		if (TCNT1>60000)// any value within 16_bit
		{
			/* Micro-controller counter counts from 0 t0 60,000.
			Variable repeatCount increases for every 60,000 reached by counter */
			
			repeatCount++;
			TCNT1=0;
			if (repeatCount>=60)
			{
				PORTC=0x80;   //red led turns on and delays for 3/10-a-second
			}
		    if (repeatCount>=120)
		    {
				PORTC=0x40;   //green led turns on and delays for 3/10-a-second
		    }
			if (repeatCount>=180)
			{
				PORTC=0x20;    //blue led turns on and delays for 3/10-a-second
				repeatCount=0;
			}
		}
    }
}
// program compiled and run successfully

