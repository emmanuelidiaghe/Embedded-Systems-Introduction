/*
 * Digital thermometer.cpp
 *
 * Created: 15-Apr-17 12:05:02 PM
 * Author : Emmanuel
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>

#define usingLcd
#define usingPort

#define lcdD4Dir DDRC_B0
#define lcdD5Dir DDRC_B1
#define lcdD6Dir DDRC_B2
#define lcdD7Dir DDRC_B3
#define lcdRsDir DDRC_B4
#define lcdEnDir DDRC_B5

#define lcdD4 PORTC_B0
#define lcdD5 PORTC_B1
#define lcdD6 PORTC_B2
#define lcdD7 PORTC_B3
#define lcdRs PORTC_B4
#define lcdEn PORTC_B5
/*
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
*/
#include "C://afrouno1/afrouno.h"
lcd display (16,2);

int speed=0;
uint8_t tempF;
uint8_t temp=ADCL;

int main(void)
{
	DDRD=0x88;
	PORTD=0x00;
	
	display.init();
	
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (ADPS1) | (1<<ADIE);
	ADMUX  |= (1<<REFS0) | (1<<ADLAR) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	sei();
	ADCSRA |= (1<<ADSC);
	
while(1)
{
}
}
ISR(ADC_vect)
{
	uint8_t tempC = (ADCH<<2) | (temp>>6);
	tempF=(tempC/2);
	display.writeText(0,0,"Temp");
	display.writeText(0,6,"Speed");
	display.writeDec(1,3,tempF);
	display.writeText(1,0,"'C:");
	// "if" ensures whole no. display
	if (tempF<100)
	{
		display.writeDec(1,3,tempF);
		display.writeText(1,5," ");
	}
	else if (tempF<10)
	{
		display.writeDec(1,3,tempF);
		display.writeText(1,4,"  ");
	}
	if (tempF<25)
	{
		display.writeDec(1,8,speed);
	}
	else if (tempF>25 && tempF<30)
	{
		speed=1;
		PORTD=0x08;
		display.writeDec(1,8,speed);
	} 
	else if (tempF>30 && tempF<40)
	{
		speed=2;
		PORTD=0x08;
		display.writeDec(1,8,speed);
	}
	else if (tempF>40 && tempF<50)
	{
		speed=3;
		PORTD=0x08;
		display.writeDec(1,8,speed);
	}
	else if (tempF>50 && tempF<55)
	{
		speed=4;
		PORTD=0x08;
		display.writeDec(1,8,speed);
	}
	else if (tempF>55 && tempF<78)
	{
		speed=5;
		PORTD=0x08;
		display.writeDec(1,8,speed);
	}
	else if (tempF>100)
	{
		PORTD=0x80;
		display.clear();
		delay_ms(1);
		display.writeText(0,0,"Temp");
		display.writeText(0,5,"HEAT ALERT!");
		display.writeDec(1,1,tempF);
		
	}

	ADCSRA |= (1<<ADSC);
}
