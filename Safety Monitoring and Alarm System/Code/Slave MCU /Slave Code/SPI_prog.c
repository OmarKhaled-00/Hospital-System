/*
 * SPI_prog.c
 *
 *  Created on: Jun 2, 2024
 *      Author: user
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Port_interface.h"
#include "SPI_reg.h"
#include "SPI_interface.h"



void SPI_SlaveInit(void)
{
	/* Make MOSI, SCK, SS as input pins */
	/* Make MISO pin as output pin */
	  PORT_voidInit();

	/* Enable SPI in slave mode */
		SET_BIT(SPCR,SPCR_SPE);
		/*Set slave mode*/
		CLR_BIT(SPCR,SPCR_MSTR);
		//SET_BIT(SPCR,SPCR_SPR0);
		//SET_BIT(SPCR,SPCR_SPR1);
		    /* Disable speed doubler */
			// CLR_BIT(SPSR,SPSR_SPI2X);
}
uint8 SPI_SlaveReceive(void)
{
	 while(!(SPSR & (1<<SPSR_SPIF)));	/* Wait till reception complete */
		return(SPDR);			/* Return received data */
}
