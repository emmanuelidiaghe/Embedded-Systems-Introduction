/*
 * Siren.cpp
 *
 * Created: 28-Dec-17 10:27:45 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int main(void)
{
	DDRD =  0x30;  //OC1A + OC1B
	PORTD = 0x00;
	
	//      |   Inverted modes         |  Fast PWM
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
	
	//      |      Fast PWM          | 256_prescaler
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS12);
	
	
	//ICR1 = 469;  //100Hz
	OCR1A = 400;

	
    while (1) 
    {
		for (int i = 625; i<1000; i++)
		{
			ICR1 = i;
			_delay_ms(50);
		}
    }
}

