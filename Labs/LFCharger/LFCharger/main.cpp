/*
 * SineWave Generator.cpp
 *
 * Created: 11-Dec-18 9:39:41 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#define usingGeneralAVR
#define usingADC
int Vout = 0;
int Duty = 0;

#include "C://Emancipator/Emancipator.h"

	int main(void) 
	{
		DDRD = (1<<DDD4)|(1<<DDD5); //PWM Pins
		PORTD |=  (1<<PD4);
		PORTD &= ~(1<<PD5);
		
		analogRefInit(VREFF_AVCC);
		
		cli();//Disable Interrupts
		
		TCCR1A = 0b10100001;
		TCCR1B = 0b00000011;
		TCCR0  = 0b00001010;
		OCR0   = 123;


		TIMSK |=(1 << OCIE0);

		sei();//Enable Interrupts
		
		while(1)
		{
			Vout = analogeReadPin(0);
			
			while (Vout < 510) {
				if (Duty == 30) {
					Vout = analogeReadPin(0);
				}
				else {
					Duty = Duty + 1;
					Vout = analogeReadPin(0);
					_delay_ms(1);
				}
			}
			while (Vout>510 && Vout<530) Vout = analogeReadPin(0);
			while (Vout > 530) {
				if (Duty == 1) {
					Vout = analogeReadPin(0);
				}
				else {
					Duty = Duty - 1;
					Vout = analogeReadPin(0);
					_delay_ms(1);
				}
			}
		}
	}

	ISR(TIMER0_COMP_vect)
	{
		int ok = 230;
			OCR1A = ok;
			OCR1B = ok;
	}
	 