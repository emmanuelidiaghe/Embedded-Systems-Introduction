/*
 * PWM.cpp
 *
 * Created: 04-May-17 6:57:21 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define usingGeneralAVR
#define usingLcd

#define lcdD4Dir DDRA_B0
#define lcdD5Dir DDRA_B1
#define lcdD6Dir DDRA_B2
#define lcdD7Dir DDRA_B3
#define lcdRsDir DDRA_B7
#define lcdEnDir DDRA_B5

#define lcdD4 PORTA_B0
#define lcdD5 PORTA_B1
#define lcdD6 PORTA_B2
#define lcdD7 PORTA_B3
#define lcdRs PORTA_B7
#define lcdEn PORTA_B5

#include "c://Emancipator/Emancipator.h"

lcd display (16,2);             //LCD resolution 16x2


int main(void)
{
	DDRD =  0x30;  //OC1A + OC1B
	PORTD = 0x48;
	
	DDRB  = 0x08;  //OC0
	PORTB = 0x00;
	
	display.init();
	_delay_ms(100);
	display.clear();
	_delay_ms(400);
	
	sei();
	
	display.writeText(0,0,"RED:");
	display.writeText(1,4,"GREEN:");
	display.writeText(0,8,"BLUE:");
	
	GICR = (1<<INT1);
	
	//      |    Fast PWM mode      |256_scaler | Inverted
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<CS02) | (1<<COM01);
	
	//      |   Inverted modes         |  Fast PWM
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
	
	//      |      Fast PWM          | 256_prescaler
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS12);
	

	ICR1 = 625;  //100Hz

	//OC1A = RED
	//OC1B = BLUE
	//OC0  = GREEN
	
    while (1) 
    {
		
		// Random compare values generation
		for (int b=469;b>0;b--)
		{
			OCR1B = b;
			display.writeDec(0,13,b);
			_delay_ms(10);
		}
		for (int s=255;s>0;s--)
		{
			OCR0 = s;
			display.writeDec(1,10,s);
			_delay_ms(20);
		}
		for (int j=0;j<469;j++)
		{
			OCR1B = j;
			display.writeDec(0,13,j);
			_delay_ms(10);
		}		
		for (int i=469;i>0;i--)
		{
			OCR1A = i;
			display.writeDec(0,4,i);
			_delay_ms(10);
		}	
		for (int r=0;r<255;r++)
		{
			OCR0 = r;
			display.writeDec(1,10,r);
			_delay_ms(20);
		}
    }
}
ISR(INT1_vect)
{
	_delay_ms(5000);
}