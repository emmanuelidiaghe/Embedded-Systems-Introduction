/*
 * Timer1.cpp
 *
 * Created: 11-Apr-17 1:33:48 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Global Variable Declaration
int segment1[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7}; //with dot
int segment2[10]={0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6}; //without dot
int count1=0;
int count2=0;

int main(void)
{  
	DDRC=0xFF;
	PORTC=0x00;
        DDRB=0x03;
	PORTB=0x00;
	
	// CTC mode, prescaler=256
	TCCR1B=TCCR1B|(1<<3)|(1<<2);
	
	//Half a second
	OCR1AH=0x5B;    
	OCR1AL=0xE8; 
	
	sei(); //enable global interrupt
	
	TIMSK=TIMSK|(1<<4); //enable output compA match interrupt
	
	
    /* Replace with your application code */
    while (1)
    {           //50% duty_cycle

		//Black segment(PB1)
		PORTB=0x01;
		PORTC=segment1[count1];
		_delay_ms(10);
		
		//Blue segment(PB0)
		PORTB=0x02;
		PORTC=segment2[count2];
		_delay_ms(10);
    }
}

//Interrupt Service Routine
ISR(TIMER1_COMPA_vect)
{
	//occurs every 0.5sec
	if (count1<9)
	{
		count1++;
	}
	else
	{
		count1=0;
		if (count2<9)
		{
			count2++;
		}
		else
		{
			count2=0;
		}
	}
}
