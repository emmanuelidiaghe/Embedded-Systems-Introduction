/*
 * PIRtest1.cpp
 *
 * Created: 25-Jul-17 11:45:09 AM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
	DDRA  = 0xFF;
	DDRC  = 0xFF;
	PORTA = 0x00;
	PORTC = 0x00;
	
	MCUCR = (1<<ISC10);
	GICR  = (1<<INT1);
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		PORTA = 0xFF; 
    }
}
ISR(INT1_vect)
{
	PORTA = 0x00;
	PORTC = 0xFF;
	_delay_ms(2000);
	PORTC = 0x00;
}