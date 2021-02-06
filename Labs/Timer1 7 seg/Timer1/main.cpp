/*
 * Timer1.cpp
 *
 * Created: 11-Apr-17 1:33:48 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "c://afrouno/afrouno.h"
int count;
int segment[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7};


int main(void)
{
	DDRC=0xFF;
	PORTC=0x00;
	
	// CTC mode,prescaler=256
	TCCR1B=TCCR1B|(1<<2); 
	OCR1AH=0xB7;        //whole no. of compValue
	OCR1AL=0xD1;        //remainder of compValue
	TIMSK=TIMSK|(1<<4); //enable output compA match interrupt
	sei(); //enable global interrupt
	
    /* Replace with your application code */
    while (1)
    {
    }
}
ISR(TIMER1_COMPA_vect)
{
	//occurs every 1sec(interrupt)
	for (count=0;count<10;count++)
	{
		PORTC=segment[count];
		_delay_ms(1000);
	}
}

