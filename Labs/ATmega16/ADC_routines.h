//******************************************************
//**** ADC ROUTINES - HEADER FILE **************
//******************************************************
//Controller		: ATmega32 (Clock: 8 Mhz-internal)
//Compiler			: AVR-GCC (winAVR with AVRStudio-4)
//Project Version	: DL_1.0
//Author			: CC Dharmani, Chennai (India)
//			  		  www.dharmanitech.com
//Date				: 10 May 2011
//******************************************************

#ifndef _ADC_ROUTINES_H_
#define _ADC_ROUTINES_H_

#include <avr/io.h>
#include "ADC_routines.h"

#define ADC_ENABLE 					ADCSRA |= (1<<ADEN)
#define ADC_DISABLE 				ADCSRA &= 0x7F
#define ADC_START_CONVERSION		ADCSRA |= (1<<ADSC)

unsigned char temperature[7];
unsigned char voltage[7];	

void ADC_init(void);
unsigned int ADC_read(void);
void readTemperature(unsigned char);
void readVoltage(unsigned char);

void ADC_init(void)
{
  ADCSRA = 0x00; //disable adc
  ADMUX  = 0x40;  //select adc input 0, ref:AVCC
  ADCSRA = 0x82; //prescaler:4, single conversion mode
  ADC_ENABLE;
}


//********************************************************************
//Purpose : Do an Analog to Digital Conversion
//Paramtr :	none
//return  : intger temperature value
//********************************************************************
unsigned int ADC_read(void)
{
    char i;
    unsigned int ADC_temp, ADCH_temp;
    unsigned int ADC_var = 0;
    
            
    for(i=0;i<8;i++)             // do the ADC conversion 8 times for better accuracy 
    {
	 	ADC_START_CONVERSION;
        while(!(ADCSRA & 0x10)); // wait for conversion done, ADIF flag active
        ADCSRA|=(1<<ADIF);
		
        ADC_temp = ADCL;         // read out ADCL register
        ADCH_temp = ADCH;        // read out ADCH register        
		ADC_temp +=(ADCH_temp << 8);
        ADC_var += ADC_temp;      // accumulate result (8 samples) for later averaging
    }

    ADC_var = ADC_var >> 3;       // average the 8 samples

	if(ADC_var > 1023) ADC_var = 1023;
	
    return ADC_var;
}


//********************************************************************
//Purpose : Read temperature from LM35 connected to the ADC
//Paramtr : unsigned char ADC channel number
//returns : None (modifies the global string 'temperature')
//********************************************************************
void readTemperature(unsigned char channel)
{
   unsigned int value;
   float volt;

   ADMUX = 0x40 | channel;
   value = ADC_read();

   volt = (float)(value * 5.0)/ 1024.0;
   value = (unsigned int)(volt * 1000);

   temperature[6] = 'C';  //centigrade
   temperature[5] = 0xb0; //ascii value for degree symbol
   temperature[4] = (value % 10) | 0x30;
   temperature[3] = '.';  
   value = value / 10;
   temperature[2] = (value % 10) | 0x30;
   value = value / 10;
   temperature[1] = (value % 10) | 0x30;
   value = value / 10;
   temperature[0] = value | 0x30;   
}  


//********************************************************************
//Purpose : Read voltage from ADC channels
//Paramtr : unsigned char ADC channel number
//returns : None (modifies the global string 'voltage')
//********************************************************************
void readVoltage(unsigned char channel)
{
   unsigned int value;
   float volt;

   ADMUX = 0x40 | channel;
   value = ADC_read();

   volt = (float)(value * 5.0)/ 1024.0;
   value = (unsigned int)(volt * 1000);

   voltage[6] = 'V';  //V for voltage
   voltage[5] = ' '; 
   voltage[4] = (value % 10) | 0x30;
   value = value / 10;
   voltage[3] = (value % 10) | 0x30;
   value = value / 10;
   voltage[2] = (value % 10) | 0x30;
   voltage[1] = '.';  
   value = value / 10;
   voltage[0] = value | 0x30;   
}  

#endif
