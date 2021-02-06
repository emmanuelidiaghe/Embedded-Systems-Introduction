/*
 * using595LedMatrix.cpp
 *
 * Created: 20/02/2017 20:41:37
 * Author : YAKMOH
 */ 



#define  F_CPU 16000000UL

#include <avr/io.h>

#include "character_code.h"

//char message1[255] = "JESUS is LORD, I love JESUS..., but HE loves me more  !@#$%^&*()-+{}[]/\:;,.?<> ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789 ""\0" ;
//char message[255] = "www.nijatechbooks.com""\0";
//char efua[255] = "EFUA VALERIE FARIZA YAKUBU ""\0";

char msg[255] = "hello world.   Welcome to ErIt ...  finish.. no  ""\0";

 
#define usingPort
#define usingUart
#define usingHC595LedMatrix

#define n595  2               // numbers of 74HC595

#define enablePin    PORTB_B1
#define dataInPin    PORTB_B3
#define shiftClkPin  PORTB_B4
#define latchClkPin  PORTB_B5

#define enableDir    DDRB_B1
#define dataInDir    DDRB_B3
#define shiftClkDir  DDRB_B4
#define latchClkDir  DDRB_B5

#define addAPin  PORTC_B0
#define addBPin  PORTC_B1
#define addCPin  PORTC_B2

#define addADir  DDRC_B0
#define addBDir  DDRC_B1
#define addCDir  DDRC_B2

#include "C:/Emancipator/Emancipator.h"


HC595LedMatrix display;

char speed = 105;

int main(void)
{
    
	display.init(100, 10);    // frequency and brightness
	//display.clearDRAM();
	
	
	/* Replace with your application code */
    while (1) 
    {
		
		    //display.scrolText(efua, speed );
		    //display.scrolText(message1, speed );
		    display.scrolText(msg, 100);
    }
}


