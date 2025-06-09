/*
 * Timers_interface.h
 *
 *  Created on: Apr 20, 2024
 *      Author: user
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_

#define Timer0_OVF_INT             0u
#define Timer0_OC_INT              1u

void Timer0_voidInit(void);

uint8 Timer_u8SetCallBack(uint8 Copy_u8InitState,void(*Copy_pvCallBack)(void));

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue);

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareValue);

void Timer1_voidInit(void);

void TIMER1_voidSetTopVal(uint16 Copy_u16Val);

void TIMER1_voidSetComVal(uint16 Copy_u16Val);

void TIMER1_voidSetComValB(uint16 Copy_u16Val);

#endif /* TIMERS_INTERFACE_H_ */
