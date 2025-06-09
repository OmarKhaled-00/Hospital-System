/*
 * SPI_prog.c
 *
 *  Created on: Jun 2, 2024
 *      Author: user
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "Port_interface.h"
#include "SPI_reg.h"
#include "SPI_interface.h"

void SPI_MasterInit(void)
{
	/* Make MOSI, SCK, SS as Output pin */
	/* Make MISO pin as input pin */
	/* Make high on SS pin */
	PORT_voidInit();
	/* Enable SPI in master mode with Fosc/16 */
	SET_BIT(SPCR,SPCR_SPE);
	SET_BIT(SPCR,SPCR_MSTR);
	CLR_BIT(SPCR,SPCR_SPR0);
	CLR_BIT(SPCR,SPCR_SPR1);
    /* Disable speed doubler */
	 CLR_BIT(SPSR,SPSR_SPI2X);
}
void SPI_Transmit(uint8 Copy_u8Data)
{

	uint8 FlushBuffer;
  /* Write data to SPI data register */
	SPDR = Copy_u8Data;
		/* Wait till transmission complete */
	while(!(SPSR & (1<<SPSR_SPIF)));
		/* Flush received data */
	FlushBuffer=SPDR;

	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}


