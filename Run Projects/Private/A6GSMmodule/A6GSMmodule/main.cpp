/*
 * A6GSMmodule.cpp
 *
 * Created: 24-Jul-18 11:47:32 AM
 * Author : Emancipator
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define usingUSART
#define usingGSM
//#define usingGeneralAVR
//#define usingSim900

#include "C://Emancipator/Emancipator.h"

//gsm Gsm;

int main(void)
{
	call("+2347061045015");
	//sendSMS("+2347061045015","EMANCIPATOR EMBEDDED, A6 GSM MODULE. ©2018");
	//gsm.init(9600);
	
	_delay_ms(1000);
	
    while (1) 
    {
    }
}