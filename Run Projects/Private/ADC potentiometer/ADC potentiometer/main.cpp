/*
 * Digital potentiometer.cpp
 *
 * Created: 15-Apr-17 12:05:02 PM
 * Author : Emmanuel
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

#define usingGeneralAVR
#define usingLcd // using LCD from Emancipator library

/**********************
 LCD PIN CONFIGURATION
 *********************/
#define lcdD4Dir DDRA_B0
#define lcdD5Dir DDRA_B1
#define lcdD6Dir DDRA_B2
#define lcdD7Dir DDRA_B3
#define lcdEnDir DDRA_B5
#define lcdRsDir DDRA_B7

#define lcdD4 PORTA_B0
#define lcdD5 PORTA_B1
#define lcdD6 PORTA_B2
#define lcdD7 PORTA_B3
#define lcdEn PORTA_B5
#define lcdRs PORTA_B7

#include "C://Emancipator/Emancipator.h"
lcd display (16,2); //an instance of the LCD class

int main(void)
{
	delay_ms(200);
	display.init(); //initialize LCD
	delay_ms(1000);
	display.clear();//clear display
	delay_ms(10);
	
	/**********************
	INITIALIZATION PROTOCOL
	***********************/
	display.writeText(0,0,"INITIALIZING");
	display.writeText(1,0,"PLEASE WAIT...");
	delay_ms(2000);
	display.clear();
	delay_ms(1000);
	
	/***************
	ADC REGISTER SET
	****************/
	/*       | Enable ADC | Use 64 pre-scaler   | Enable ADC interrupt */
	ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE); //| (ADPS1) | (1<<ADIE); 
	
	/*     |Left Adjustment|AVcc as Ref voltage |Enable ADC4   */
	ADMUX  |= (1<<ADLAR) | (1<<REFS0) |(1<<MUX2);
	
	/*   Start first Conversion */
	ADCSRA |= (1<<ADSC);
	
	/* Enable Global Interrupt */
	sei();
	
	while(1)
	{
		//;;Empty while loops, as interrupt function handles the conversion
	}
}
ISR(ADC_vect) //ADC Interrupt Service Routine
{
	/* 10bit resolution */
	uint8_t potL = ADCL;                     
	uint16_t potH = (ADCH<<2) | (potL>>6);
	
	display.writeText(0,0,"TEST IN PROGRESS");
	display.writeText(1,0,"POT Value...");
	display.writeDec(1,12,potH);
	
	// "if" ensures whole no. display 
	if (potH<1000)
	{
		display.writeDec(1,12,potH);
		display.writeText(1,15," ");
	}
	if (potH<100)
	{
		display.writeDec(1,12,potH);
		display.writeText(1,14,"  ");
	}
	if (potH<10)
	{
		display.writeDec(1,12,potH);
		display.writeText(1,13,"   ");
	}
	
	ADCSRA |= (1<<ADSC); //Start second conversion
}
