/*
 * USART_interface.h
 *
 *  Created on: May 15, 2024
 *      Author: user
 */

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_Init(void);


void USART_VoidSend(uint8 Copy_u8Data);


uint8 USART_u8Recieve(void);
#endif /* USART_INTERFACE_H_ */
