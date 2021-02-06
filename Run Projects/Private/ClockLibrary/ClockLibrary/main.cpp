/*
 * Real clock.cpp
 *
 * Created: 08-Jun-17 11:17:36 AM
 * Author : Emancipator
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


#define usingSoftI2c
#define usingLcd
#define usingGeneralAVR
#define usingShiftRegister
#define usingDigitalClock
#define DefaultSet
#define NumOfReg 4

//SHIFT_REGISTER
/*#define HC595_DDR 	DDRB
#define HC595_PORT 	PORTB

#define HC595_DS1_POS       PB0
#define HC595_DS2_POS       PB1
#define HC595_SH1_CP_POS    PB2
#define HC595_SH2_CP_POS    PB3
#define HC595_ST_CP_POS     PB4*/

//BLINKTIMER
#define BlinkTimer_DDR  DDRC
#define BlinkTimer_PORT PORTC

#define BlinkTimer_AM PC1
#define BlinkTimer_PM PC2
#define BlinkTimer_BLINK PC0

//RTC
#define i2cSclDir DDRD_B5
#define i2cSdaDir DDRD_B4
#define i2cSdaPin PIND_B4
#define i2cScl   PORTD_B5
#define i2cSda   PORTD_B4

//LCD
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

#include "C://Emancipator/Emancipator.h"

i2c rtcDs1307(0x68, I2C_8Bit);  //Address, bit size (RTC)
Blink blink;
Time time;
HC595 shift;

uint8_t led_pattern[10] = {63,6,91,79,102,109,125,7,127,111};

int main(void)
{
	blink.init();       //Initialize LED
	rtcDs1307.init();  //Initialize RTC
	shift.init();     //Initialize 595
	_delay_ms(100);
	
	time.DispProtocol();
	
	blink.Timer();
	
	/* Replace with your application code */
	while (1)
	{
		rtcDs1307.readBytes(0x0000, rtcData, 8);
		
		time.Convert();
		
		shift.HC595WRITE(led_pattern[S0],led_pattern[S1],led_pattern[M0],led_pattern[M1]);
		
		time.LcdDisplay();
		
		_delay_ms(1);
	}
}

ISR(TIMER1_COMPA_vect)
{	
	time.Convert();
	blink.on();
	
	_delay_ms(500);
}