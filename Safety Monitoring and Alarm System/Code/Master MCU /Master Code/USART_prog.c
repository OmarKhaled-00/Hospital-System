/*
 * USART_prog.c
 *
 *  Created on: May 15, 2024
 *      Author: user
 */

#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_reg.h"
#include "USART_interface.h"




void USART_Init(void)
{
	/*Set Baud Rate : 9600 bps*/
	UBRRH = 0;
	UBRRL = 103;

	/*Set Frame Format : 8 bits , 1 stop bit , no polarity*/

	UCSRC = (1<<UCSRC_URSEL) | (1<<UCSRC_UCSZ0) | (1<<UCSRC_UCSZ1);

	/*Enable Transmitter and reciever*/

	UCSRB = (1<<UCSRB_TXEN) | (1<<UCSRB_RXEN);
}


void USART_VoidSend(uint8 Copy_u8Data)
{
	/*To transmit the signal , UDRE Flag must set to one First in the UCSRA Register*/
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR = Copy_u8Data;
}


uint8 USART_u8Recieve(void)
{
  while(GET_BIT(UCSRA,UCSRA_RXC)==0);
  return UDR;
}
