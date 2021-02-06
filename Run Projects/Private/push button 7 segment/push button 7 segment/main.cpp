/*
 * push button.cpp
 *
 * Created: 05-Apr-17 11:16:53 AM
 * Author : Emancipator
 */ 
#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
      DDRC=0xFF;
	  PORTC=0xFC;
	  DDRD=0x00;
	  PORTD=0x40;
	  
	  int led_on[10]={0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7};
	  int a=0;
	  int button_pressed=0;
	  
		  while(1)
		{		  
			  if ((PIND & (1<<PD6))==0)
			  {
				  _delay_ms(50);
				  a=button_pressed + 1;
			  }
	      else {
			  button_pressed=a;
		       }	 
		   if(a==1)  
		  {
			  PORTC=led_on[0];
		  }
		  else if (a==2)
		  {
			  PORTC=led_on[1];
		  }
		  else if (a==3)
		  {
			  PORTC=led_on[2];
		  }
		  else if (a==4)
		  {
			  PORTC=led_on[3];
		  } 
		  else if (a==5)
		  {
			  PORTC=led_on[4];
		  }
		  else if (a==6)
		  {
			   PORTC=led_on[5];
		  }
		  else if (a==7)
		  {
			   PORTC=led_on[6];
		  }
		  else if (a==8)
		  {
			   PORTC=led_on[7];
		  }
		  else if (a==9)
		  {
			   PORTC=led_on[8];
		  }
		  else if (a==10)
		  {
			  PORTC=led_on[9];
		  }
		  else if (a==11)
		  {
			  button_pressed=0;
		  }
		  }
		}