/*
 * PWM.cpp
 *
 * Created: 04-May-17 6:57:21 PM
 * Author : Emancipator
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRD =  0x30;  //OC1A + OC1B
	PORTD = 0x00;
	
	DDRB  = 0x08;  //OCO
	PORTB = 0x00;
	
	//      |    Fast PWM mode      |256_scaler | Inverted
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<CS02) | (1<<COM01);
	
	//      |   Inverted modes         |  Fast PWM
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
	
	//      |      Fast PWM          | 256_prescaler
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS12);
	
	
	ICR1 = 469;  //100Hz
	
	
    while (1) 
    {
		// Random compare values generation
		
		for (int a=0;a<469;a++)
		{
			OCR1A = a;
			_delay_ms(10);
		}
		for (int b=469;b>0;b--)
		{
			OCR1B = b;
			_delay_ms(10);
		}
		for (int s=255;s>0;s--)
		{
			OCR0 = s;
			_delay_ms(20);
		}
		for (int j=0;j<469;j++)
		{
			OCR1B = j;
			_delay_ms(10);
		}		
		for (int i=469;i>0;i--)
		{
			OCR1A = i;
			_delay_ms(10);
		}	
		for (int r=0;r<255;r++)
		{
			OCR0 = r;
			_delay_ms(20);
		}
    }
}