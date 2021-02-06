/*
 * usingSofti2c.cpp
 *
 * Created: 04/05/2017 15:07:38
 * Author : YAKMOH
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>

// declare DDR and PORTS of uC as slave
#define i2cScl PORTC_B5
#define i2cSda PORTC_B4

#define i2cSclDir DDRC_B5
#define i2cSdaDir DDRC_B4

#define i2cSdaPin PINC_B4

#define usingSoftI2c
#define usingUart


#include "c:/Afrouno/afrouno.h"

uart serial;
i2c At24C32(0x50, I2C_16Bit); // Address, bit size (EEPROM)
i2c rtcDs1307(0x68, I2C_8Bit);  //Address, bit size (RTC)
uint8_t writeData[28] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
uint8_t readData[32];

uint8_t rtcData[7];
uint8_t rtcTime[9] = "00:00:00";

int main(void)
{
    
	//uint16_t eepromAdd = 0;
	
	
	serial.init(9600);
	Delay_ms(100);
	
	
	rtcDs1307.init();
	
	serial.writeLine("System startup....");
	/*
	serial.writeLine("writing data to EEPROM");
	for(uint8_t i=0; i<27; i++){
		
		At24C32.writeByte( eepromAdd+i, writeData[i]);
		serial.writeText(".");
		Delay_ms(250);
	}
	serial.writeLine(".");
	*/
	
	//serial.writeLine("reading data from EEPROM");
	/*for(uint8_t i=0; i<30; i++){
		
		At24C32.readByte( eepromAdd+i, &readData[i]);
		serial.writeText(".");
		Delay_ms(250);
	}
	
	
	At24C32.readBytes(eepromAdd, readData, 9 );
	serial.writeLine("Read Data:");
	serial.writeText( (char *)readData);
	*/
	
	
	rtcDs1307.readBytes(0x0000, rtcData, 7);  //position, data to be read, width of data
	
	rtcData[0] = rtcData[0] & 0b01111111;  //anding with 7bit wide data
	
	rtcDs1307.writeByte(0x0000, rtcData[0]); 
	  
	/* Replace with your application code */
    while (1) 
    {
		     rtcDs1307.readBytes(0x0000, rtcData, 7);
			 
			 /* Conversion steps
			 -BCD to Binary
			 -Binary to ASCII
			 */
			 rtcTime[7] =   ( rtcData[0] & 0b00001111) + 48;
			 rtcTime[6] =  (( rtcData[0] >> 4) & 0b00000111) + 48;
			 
			 rtcTime[4] = ( rtcData[1] & 0b00001111) + 48;
			 rtcTime[3] =  (( rtcData[1] >> 4) & 0b00000111) +48;
			 
			 rtcTime[1] = ( rtcData[2] & 0b00001111) + 48;
			 rtcTime[0] =  (( rtcData[2] >> 4) & 0b00000011) +48;
			 
			 serial.writeText((char*)"Time:");
			 serial.writeLine((char*)rtcTime);
			 Delay_ms(500);
		
    }
}

