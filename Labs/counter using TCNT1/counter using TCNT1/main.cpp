/*
 * counter using TCNT1.cpp
 *
 * Created: 11-Apr-17 10:00:07 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFF;  // set for output
	PORTA= 0x00;
	DDRC = 0xFF;  // set for output
	PORTC= 0x00; 
	DDRD = 0x00;  // set for input
	PORTD= 0x64;
	
        int led1[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //Array of LED shifts
		int led2[9] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
		int count1  = 0;
		int count2  = 0;
		int a=0;
		int button_pressed=0;

	TCCR1B|=(1<<CS12); // using 256 pre-scaler
	
    /* Replace with your application code */
    while (1) 
    {
		if ((PIND && (1<<PD6))==0)
		{
		   _delay_ms(50);
			a=button_pressed+1;
		}
		else
		{
			button_pressed=a;
		}
		if (TCNT1>=5859)  //set counter to 1/8th second
	{
		TCNT1=0;
		if(a==1)
		{
			PORTA = led1[count1];  //LEDs shift in 1/8th second
			count1++;                
			if (count1>7)
			{
				count1=0;
				PORTC = led1[count2];  //LEDs shift in 1 second
				count2++;
				if (count2>7)
				{
					count2=0;
				}
			}
		}
	
		else if (a==2)
		{
					PORTC = led2[count1];  //LEDs shift in 1/8th second
					count1++;
					if (count1>7)
					{
						count1=0;
						PORTA = led2[count2];  //LEDs shift in 1 second
						count2++;
						if (count2>7)
						{
							count2=0;
						}
					}
		}
		
		else if (a>2)
		{
			button_pressed=0;
		}
    }
	}
		}