/*
 * PWM.cpp
 *
 * Created: 04-May-17 6:57:21 PM
 * Author : Emancipator
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

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


void readOut(void)
{
	display.writeText(0,0,"RED:");
	display.writeText(1,4,"GREEN:");
	display.writeText(0,8,"BLUE:");
	
	display.writeDec(0,4,OCR1A);
	display.writeDec(1,10,OCR1B);
	display.writeDec(0,13,OCR0);
	
}

uint32_t convert(uint32_t value)
{
	uint32_t output;
	output = ((625 * value)/255);
	return output;
}

void Red(void)
{
	OCR1A = convert(255);
	OCR1B = convert(0);
	OCR0  = 0;
	readOut();
}

void Green(void)
{
	OCR1A = convert(0);
	OCR1B = convert(255);
	OCR0  = 0;
	readOut();
}

void Blue(void)
{
	OCR1A = convert(0);
	OCR1B = convert(0);
	OCR0  = 255;
	readOut();
}

void colour1(void)
{
	OCR1A = convert(107);
	OCR1B = convert(255);
	OCR0  = 255;
	readOut();
}

void colour2(void)
{
	OCR1A = convert(255);
	OCR1B = convert(0);
	OCR0  = 255;
	readOut();
}

void colour3(void)
{
	OCR1A = convert(50);
	OCR1B = convert(209);
	OCR0  = 80;
	readOut();
}

void colour4(void)
{
	OCR1A = convert(255);
	OCR1B = convert(100);
	OCR0  = 109;
	readOut();
}
void colour5(void)
{
	OCR1A = convert(170);
	OCR1B = convert(135);
	OCR0  = 200;
	readOut();
}

void colour6(void)
{
	OCR1A = convert(255);
	OCR1B = convert(255);
	OCR0  = 255;
	readOut();
}

void colour7(void)
{
	OCR1A = convert(70);
	OCR1B = convert(163);
	OCR0  = 140;
	readOut();
}

void colour8(void)
{
	OCR1A = convert(200);
	OCR1B = convert(100);
	OCR0  = 0;
	readOut();
}

void colour9(void)
{
	OCR1A = convert(192);
	OCR1B = convert(255);
	OCR0  = 0;
	readOut();
}

void colour10(void)
{
	OCR1A = convert(255);
	OCR1B = convert(50);
	OCR0  = 255;
	readOut();
}

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
	
	
	//      |    Fast PWM mode      |256_scaler | Inverted
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<CS02) | (1<<COM01);
	
	//      |   Inverted modes         |  Fast PWM
	TCCR1A = (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
	
	//      |      Fast PWM          | 256_prescaler
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS12);
	

	ICR1 = 625;  //100Hz

	//OC1A = RED
	//OC1B = GREEN
	//OC0  = BLUE
	
    while (1) 
    {
		colour1();
		_delay_ms(500);
		display.clear();
		
		colour2();
		_delay_ms(500);
		display.clear();
		
		colour3();
		_delay_ms(500);
		display.clear();
		
		Green();
		_delay_ms(500);
		display.clear();
		
		colour4();
		_delay_ms(500);
		display.clear();
		
		colour5();
		_delay_ms(500);
		display.clear();
		
		Red();
		_delay_ms(500);
		display.clear();
		
		colour6();
		_delay_ms(500);
		display.clear();
		
		colour7();
		_delay_ms(500);
		void
		colour8();
		_delay_ms(500);
		display.clear();
		
		colour9();
		_delay_ms(500);
		display.clear();
		
		Blue();
		_delay_ms(500);
		display.clear();
		
		colour10();
		_delay_ms(500);
		display.clear();
    }
}

