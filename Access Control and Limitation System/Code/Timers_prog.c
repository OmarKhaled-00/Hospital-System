/*
 * Timers_prog.c
 *
 *  Created on: Apr 20, 2024
 *      Author: user
 */
#include"STD_TYPES.h"
#include"ErrType.h"
#include"BIT_MATH.h"
#include"Timers_interface.h"
#include"Timers_cfg.h"
#include"Timers_prv.h"
#include"Timers_reg.h"


//static void (*Timer0_CallBackFunc)(void)=NULL;
static void (*Timer_CallBackFunc[9])(void)={NULL};
void Timer0_voidInit(void)
{
#if(MODE == Normal_Mode)/*Set to the normal mode*/
	CLR_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	/*Set preload value*/
	TCNT0 = TCNTO_Init_val;
	/*Enable interrupt overflow*/
	SET_BIT(TIMSK,TIMSK_TOIEO);
#elif(MODE == CTC)     /*Set the CTC mode*/
    CLR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	/*Set Compare match value*/
	OCR0=OCR0_Init_val;
	/*Enable cmopare match interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

#elif(MODE == PWM_Phase_Correct)/*Set PWM, phase correct*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	CLR_BIT(TCCR0,TCCR0_WGM01);
	if(Phase_Correct_PWM_Mode == Normal_port_operation_OC0_disconnected_Phase_Correct)
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
	    CLR_BIT(TCCR0,TCCR0_COM01);
	}
	else if(Phase_Correct_PWM_Mode ==Clear_OC0_on_compare_match_when_upcounting_Set_OC0_on_compare_match_when_downcounting)
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
	}
	else if(Phase_Correct_PWM_Mode ==Set_OC0_on_compare_match_when_upcounting_Clear_OC0_on_compar_ match_when_downcounting)
	{
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
	}
	else
	{
		/*Do nothing , continue*/
	}


#elif(MODE == Fast_PWM)/*Set Fast PWM*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);
	if(Fast_PWM_Mode == Clear_OC0_on_compare_match_set_OC0_at_TOP)
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
	}
	else if(Fast_PWM_Mode == Normal_port_operation_OC0_disconnected)
	{
		CLR_BIT(TCCR0,TCCR0_COM00);
	    CLR_BIT(TCCR0,TCCR0_COM01);
	}
	else if(Fast_PWM_Mode == Set_OC0_on_compare_match_clear_OC0_at_TOP)
	{
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
	}
	else
	{
		/*Do nothing , continue*/
	}


#endif


	/*Clear prescaler bits*/
	TCCR0 &= Clear_Prescaler_Bits;
	/*Set prescaler to divided by 256  8_bit*/
#if(Clock_Source_Val == No_clock_source)
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == Prescaler_0)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == Prescaler_8)
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == Prescaler_64)
    SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == Prescaler_256)
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == Prescaler_1024)
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == External_clock_source_on_T0_pin_Clock_on_falling_edge)
	CLR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#elif(Clock_Source_Val == External_clock_source_on_T0_pin_Clock_on_rising_edge)
	SET_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);
#endif
	//TCCR0 |= 0b100;

}

void Timer1_voidInit(void)
{
	TCCR1B &= Clear_Prescaler_Bits;

	    // Set Fast PWM mode 15: WGM13 = 1, WGM12 = 1, WGM11 = 1, WGM10 = 1
	    // Configure non-inverting mode for OC1A and OC1B
	    TCCR1A = (1 << TCCR1A_WGM11) | (1 << TCCR1A_WGM10) | (1 << TCCR1A_COM1A1) | (1 << TCCR1A_COM1B1);
	    TCCR1B = (1 << TCCR1B_WGM13) | (1 << TCCR1B_WGM12) | (1 << TCCR1B_CS12); // Prescaler = 256

	    // Set the top value for Timer1 (OCR1A as TOP)
	     OCR1A = 65535; // Using maximum 16-bit value for highest resolution

	    // Set the duty cycle for Motor 2 to 25% of OCR1A
	    //OCR1B = OCR1A / 4; // 25% duty cycle

}

void TIMER1_voidSetTopVal(uint16 Copy_u16Val)
{
	ICR1 = Copy_u16Val;
}
void TIMER1_voidSetComVal(uint16 Copy_u16Val)
{
	OCR1A = Copy_u16Val;
}

void TIMER1_voidSetComValB(uint16 Copy_u16Val)
{
	OCR1B=Copy_u16Val;
}

uint8 Timer_u8SetCallBack(uint8 Copy_u8InitState,void(*Copy_pvCallBack)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBack != NULL)
	{
		/*Set Localy Function globally*/
		Timer_CallBackFunc[Copy_u8InitState] = Copy_pvCallBack;
	}
	else
	{
		Local_u8ErrorState= NULL_PTR_ERR;
	}
	return Local_u8ErrorState;

}

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadValue)
{
  TCNT0 = Copy_u8PreloadValue;
}

void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareValue)
{
  OCR0 = Copy_u8CompareValue;
}


/*Timer0 overflow ISR*/
void __vector_11(void)__attribute__((signal));
void __vector_11(void)
{
	if(Timer_CallBackFunc[Timer0_OVF_INT]!= NULL)
	{
		Timer_CallBackFunc[Timer0_OVF_INT]();
	}
	else
	{

	}
}
/*Timer0 Compare match interrupt*/
void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	if(Timer_CallBackFunc[Timer0_OC_INT]!= NULL)
	{
		Timer_CallBackFunc[Timer0_OC_INT]();
	}
	else
	{

	}
}
