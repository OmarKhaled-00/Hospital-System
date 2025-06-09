/*
 * LM35_prog.c
 *
 *  Created on: Mar 20, 2024
 *      Author: user
 */
#include"STD_TYPES.h"
#include"ADC_interface.h"
uint32 Get_u32Temp(void)
{

	uint16 Local_u32DigitalReading = ADC_u8GetChannelReading(0);
	    uint32 Local_u32AnalogReading = ((uint32)Local_u32DigitalReading * 5000UL / 1024UL); // Convert ADC reading to millivolts

	    uint32 Temp = Local_u32AnalogReading+10/10 ; // Convert millivolts to Celsius
	    Temp=Temp/(uint32)10;
	    return Temp;
}
