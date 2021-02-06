/*
*
*
*/
#define	F_CPU	16000000
#define usingLcd
#define usingAdc

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "C://Emancipator/Emancipator.h"

lcd display(16,2);

uint8_t data;
uint8_t counter = 0;
uint16_t ch2_ref;
uint16_t ch3_ref;
uint16_t ch2_read;
uint16_t ch3_read;
uint16_t ADC_ch2_value;
uint16_t ADC_ch3_value;
char num_in[20];
char num_out[20];
uint8_t inFlag = 0;
uint8_t outFlag = 0;


void ADC_ch2(void);
void ADC_ch3(void);

int main(void)
{
	DDRD = 0b00110000;
	PORTD = 0x00;
	DDRA = 0x00;
	
	_delay_ms(100);
	display.init();
	analogRefInit(1);
	
	ch2_read = analogeReadPin(0);
	ch2_ref = ch2_read;

	ch3_read = analogeReadPin(1);
	ch3_ref = ch3_read;

	/* Start of infinite loop */
	while (1)
	{
		ADC_ch2();
		ADC_ch3();
		
		if (ADC_ch2_value < (ch2_ref - 100))
		{
			outFlag = 1;
			
			if (inFlag == 1)
			{
				counter++;
				PORTD |= (1<<PD5);	/* Turn ON LED on PD5 */
				inFlag = 0;
				outFlag = 0;
				_delay_ms(200);
				lcd_gotoxy(0,0);
				lcd_puts("Direction: -->");
				
			}
			else
			{
				counter = counter;
				lcd_gotoxy(0,0);
				lcd_puts("Direction:    ");
			}
			sprintf(num_in, "Visitors: %d ", counter);
			lcd_gotoxy(0,1);
			lcd_puts(num_in);
		}
		
		else if (ADC_ch3_value < (ch3_ref - 100))
		{
			inFlag = 1;
			
			if (outFlag == 1)
			{
				if (counter > 0)
				{
					counter--;
				}
				else if (counter == 0)
				{
					counter = 0;
				}
				
				inFlag = 0;
				outFlag = 0;
				PORTD |= (1<<PD4);	/* Turn ON LED on PD4 */
				_delay_ms(200);
				lcd_gotoxy(0,0);
				lcd_puts("Direction: <--");

			}
			else
			{
				counter = counter;
				lcd_gotoxy(0,0);
				lcd_puts("Direction:    ");
				
			}
			sprintf(num_in, "Visitors: %d ", counter);
			lcd_gotoxy(0,1);
			lcd_puts(num_in);
		}
		else
		{
			PORTD = 0x00;
			counter = counter;
		}
	}
	return 0;
}

void ADC_ch2()
{
	ADC_ch2_value = analogeReadPin(0);
}

void ADC_ch3()
{
	ADC_ch3_value = analogeReadPin(1);
}
