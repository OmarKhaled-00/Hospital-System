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
#if(Timer1_Mode == T1Normal)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_Correct_8_bit)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_Correct_9_bit)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_Correct_10_bit)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == CTC_OCR1A)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == Fast_PWM_8_bit)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == Fast_PWM_9_bit)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == Fast_PWM_10_bit)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	CLR_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_and_Frequency_Correct_ICR1)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_and_Frequency_Correct_OCR1A)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_Correct_ICR1)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == PWM_Phase_Correct_OCR1A)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == CTC_ICR1)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == Fast_PWM_ICR1)
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#elif(Timer1_Mode == Fast_PWM_OCR1A)
	SET_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1A,TCCR1B_WGM12);
	SET_BIT(TCCR1A,TCCR1B_WGM13);
#endif
	/*Clear Prescaller*/
	TCCR1B &= Clear_Prescaler_Bits;
	/*Set prescaller*/
#if(T1Clock_Source_Val == T1No_clock_source)
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1Prescaler_1)
	SET_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1Prescaler_8)
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1Prescaler_64)
	SET_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1Prescaler_256)
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	SET_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1Prescaler_1024)
	SET_BIT(TCCR1B,TCCR1B_CS10);
	CLR_BIT(TCCR1B,TCCR1B_CS11);
	SET_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1External_clock_source_on_T0_pin_Clock_on_falling_edge)
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	SET_BIT(TCCR1B,TCCR1B_CS12);
#elif(T1Clock_Source_Val == T1External_clock_source_on_T0_pin_Clock_on_rising_edge)
	SET_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	SET_BIT(TCCR1B,TCCR1B_CS12);
#endif
#if(Compare_Output_Mode_non_PWM == Normal_port_operation_OC1A_OC1B_disconnected)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_non_PWM == Toggle_OC1A_OC1B_on_compar_match)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_non_PWM == Clear_OC1A_OC1B_on_compare_match_Set_output_to_low_level)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_non_PWM == Set_OC1A_OC1B_on_compare_match_Set_output_to_high_level)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#endif
#if(Compare_Output_Mode_on_FAST_PWM == FASTPWM_Normal_port_operation_OC1A_OC1B_disconnected)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_on_FAST_PWM == FAST_PWM_WGM13_0)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_on_FAST_PWM == FAST_PWM_Clear_OC1A_OC1B_on_compare_match_set_OC1A_OC1B_at_TOP)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_on_FAST_PWM == FAST_PWM_Set_OC1A_OC1B_on_compare_match_clear_OC1A_OC1B_at_TOP)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#endif
#if(Compare_Output_Mode_Phase_Correct_and_Phase_and_Frequency_CorrectPWM == Normal_port_operation)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_Phase_Correct_and_Phase_and_Frequency_CorrectPWM == WGM13_0_settings)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	CLR_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_Phase_Correct_and_Phase_and_Frequency_CorrectPWM == Clear_OC1A_OC1B_on_compare_match_when_up_counting_set_OC1A_OC1B_on_compare_match_when_downcounting)
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	CLR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#elif(Compare_Output_Mode_Phase_Correct_and_Phase_and_Frequency_CorrectPWM == Set_OC1A_OC1B_on_compare_match_when_up_counting_Clear_OC1A_OC1B_on_compare_match_when_downcounting)
	SET_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);
#endif

}

void TIMER1_voidSetTopVal(uint16 Copy_u16Val)
{
	ICR1 = Copy_u16Val;
}
void TIMER1_voidSetComVal(uint16 Copy_u16Val)
{
	OCR1A = Copy_u16Val;
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
