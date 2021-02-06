/*
 * push button.cpp
 *
 * Created: 05-Apr-17 11:16:53 AM
 * Author : Emancipator
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
      DDRC=0xFF;
	  PORTC=0x00;
	  
	  int led_on[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7};
	  
		  while(1)
		{	
			for (int i =0;i<10;i++)
			{
				PORTC = led_on[i];
				_delay_ms(1000);
			}
		}
}