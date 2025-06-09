/*
 * SPI_reg.h
 *
 *  Created on: Jun 2, 2024
 *      Author: user
 */

#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPDR     *((volatile uint8*)0x2F)  /*SPI Data Register*/
#define SPSR     *((volatile uint8*)0x2E)  /*SPI Status Register*/
#define SPSR_SPI2X    0u   /* Double SPI Speed Bit*/
#define SPSR_WCOL     6u   /*Write COLlision Flag*/
#define SPSR_SPIF     7u   /*SPI Interrupt Flag*/
#define SPCR      *((volatile uint8*)0x2D)  /*SPI Control Register*/
#define SPCR_SPR0                0u  /*SPI Clock Rate Select 0*/
#define SPCR_SPR1                1u  /*SPI Clock Rate Select 1*/
#define SPCR_CPHA                2u  /*Clock Phase*/
#define SPCR_CPOL                3u  /*Clock Polarity*/
#define SPCR_MSTR                4u  /*Master/Slave Select*/
#define SPCR_DORD                5u  /* Data Order*/
#define SPCR_SPE                 6u  /*SPI Enable*/
#define SPCR_SPIE                7u  /*SPI Interrupt Enable*/
#endif /* SPI_REG_H_ */
