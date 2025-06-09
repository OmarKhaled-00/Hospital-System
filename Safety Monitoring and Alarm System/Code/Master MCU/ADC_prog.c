/*
 * ADC_prog.c
 *
 *  Created on: Mar 17, 2024
 *      Author: user
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ErrType.h"

#include"ADC_reg.h"
#include"ADC_prv.h"
#include"ADC_cfg.h"
#include"ADC_interface.h"



void ADC_VoidInit(void)
{

#if(REFS1_0 ==  AREF_Internal_Vref_Turned_Off)
	CLR_BIT(ADMUX , ADMUX_REFS1);
	CLR_BIT(ADMUX , ADMUX_REFS0);
#endif

#if(REFS1_0 == AVCC_With_External_Capacitor_On_AREF)
	CLR_BIT(ADMUX , ADMUX_REFS1);
    SET_BIT(ADMUX , ADMUX_REFS0);
#endif

#if(REFS1_0 == Reserved)
    SET_BIT(ADMUX , ADMUX_REFS1);
    CLR_BIT(ADMUX , ADMUX_REFS0);
#endif

#if(REFS1_0 == Internal_Voltage)
    SET_BIT(ADMUX , ADMUX_REFS1);
    SET_BIT(ADMUX , ADMUX_REFS0);
#endif

#if(ADLAR_Pin == Resolution_8)
    SET_BIT(ADMUX , ADMUX_ADLAR);
#endif

#if(ADLAR_Pin == Resolution_10)
    CLR_BIT(ADMUX , ADMUX_ADLAR);
#endif

#if(Auto_Trigger == ENABLED)
    SET_BIT(ADCSRA,ADCSRA_ADATE);
#endif

#if(Auto_Trigger == DISABLED)
    CLR_BIT(ADCSRA,ADCSRA_ADATE);
#endif

#if(ADC_Interrupt == ENABLED)
    SET_BIT(ADCSRA, ADCSRA_ADIE);
#endif

#if(ADC_Interrupt == DISABLED)
    CLR_BIT(ADCSRA, ADCSRA_ADIE);
#endif

    /*The prescaler division factor*/
    ADCSRA &= ADC_PRESCALER_BIT_MASK;   /*Clear Bits*/
    ADCSRA |=ADC_u8Prescaler_Division_Factor << ADC_Prescaler_BIT_POS;
  /*Enable ADC*/
  SET_BIT(ADCSRA, ADCSRA_ADEN);
}

uint16 ADC_u8GetChannelReading(uint8 Copy_u8Channel)
{
	/*Initially clear the bits of ADMUX*/
	ADMUX &= CHANNEL_BIT_MASK;
	ADMUX |= Copy_u8Channel;

	/*Start Conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);
	/*Polling(with Blocking) on the conversion complete*/
	while((GET_BIT(ADCSRA,ADCSRA_ADIF))==0);
	/*Clear the flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	/*Get the conversion result*/
#if(ADLAR_Pin == Resolution_8)
	return ADCH;
#endif

#if(ADLAR_Pin == Resolution_10)
	return ADC;
#endif

}


