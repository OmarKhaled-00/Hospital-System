/*

 * LDR_prog.c
 *
 *  Created on: Mar 20, 2024
 *      Author: user
 */

#include"STD_TYPES.h"
#include"ADC_interface.h"
#include"LDR_interface.h"

uint16 LDR_GetValue(void)
{

	uint16 Local_u16DigitalReading = ADC_u8GetChannelReading(7);
	return Local_u16DigitalReading;
}
