//**************************************************************
// ****** FUNCTIONS FOR SPI COMMUNICATION *******
//**************************************************************
//Controller		: ATmega32 (Clock: 8 Mhz-internal)
//Compiler			: AVR-GCC (winAVR with AVRStudio-4)
//Project Version	: DL_1.0
//Author			: CC Dharmani, Chennai (India)
//			  		  www.dharmanitech.com
//Date				: 10 May 2011
//**************************************************************

#ifndef _SPI_ROUTINES_H_
#define _SPI_ROUTINES_H_

#include <avr/io.h>
#include "SPI_routines.h"


#define SPI_SD             SPCR = 0x52
#define SPI_HIGH_SPEED     SPCR = 0x50; SPSR |= (1<<SPI2X)


void spi_init(void);
unsigned char SPI_transmit(unsigned char);
unsigned char SPI_receive(void);

void spi_init(void)
{
SPCR = 0x52; //setup SPI: Master mode, MSB first, SCK phase low, SCK idle low
SPSR = 0x00;
}

unsigned char SPI_transmit(unsigned char data)
{
// Start transmission
SPDR = data;

// Wait for transmission complete
while(!(SPSR & (1<<SPIF)));
data = SPDR;

return(data);
}

unsigned char SPI_receive(void)
{
unsigned char data;
// Wait for reception complete

SPDR = 0xff;
while(!(SPSR & (1<<SPIF)));
data = SPDR;

// Return data register
return data;
}

//******** END ****** www.dharmanitech.com *****

#endif
