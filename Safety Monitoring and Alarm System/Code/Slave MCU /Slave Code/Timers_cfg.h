/*
 * Timers_cfg.h
 *
 *  Created on: Apr 20, 2024
 *      Author: user
 */

#ifndef TIMERS_CFG_H_
#define TIMERS_CFG_H_
/*Timer0*/
/*Initialize modes*/
#define Normal_Mode                                                         0u
#define PWM_Phase_Correct                                                   1u
#define CTC                                                                 2u
#define Fast_PWM                                                            3u
/*------------------------------------------------------------------*/
/*Set the mode*/
#define MODE           Fast_PWM
/*Compare Output Mode, Fast PWM Mode*/
#define  Normal_port_operation_OC0_disconnected                              0u
#define  Reserved                                                            1u   /*Not used*/
#define  Clear_OC0_on_compare_match_set_OC0_at_TOP                           2u
#define  Set_OC0_on_compare_match_clear_OC0_at_TOP                           3u
/*------------------------------------------------------------------*/
/*Set the mode*/
#define Fast_PWM_Mode                Clear_OC0_on_compare_match_set_OC0_at_TOP
/* ------------------------------------------------------------------*/
/*Compare Output Mode, Phase Correct PWM Mode*/
#define Normal_port_operation_OC0_disconnected_Phase_Correct                                      0u
#define Reserved_Phase_Correct                                                                    1u  /*Not used*/
#define Clear_OC0_on_compare_match_when_upcounting_Set_OC0_on_compare_match_when_downcounting     2u
#define Set_OC0_on_compare_match_when_upcounting_Clear_OC0_on_compar_ match_when_downcounting     3u
/*------------------------------------------------------------------*/
/*Set the mode*/
#define Phase_Correct_PWM_Mode           Reserved_Phase_Correct
/*-------------------------------------------------------------------*/
/*Prescaller initialization*/
#define No_clock_source                                                       0u
#define Prescaler_0                                                           1u
#define Prescaler_64                                                          3u
#define Prescaler_256                                                         4u
#define Prescaler_1024                                                        5u
#define External_clock_source_on_T0_pin_Clock_on_falling_edge                 6u
#define External_clock_source_on_T0_pin_Clock_on_rising_edge                  7u
/*------------------------------------------------------------------------*/
/*Set the prescaller*/
#define Clock_Source_Val              Prescaler_256
/*------------------------------------------------------------------------*/
/*Set initial value for TCNT0 and OCR0*/
#define TCNTO_Init_val             0u
#define OCR0_Init_val              0u
/*------------------------------------------------------------------------*/

/*Timer1*/
/*Initialize modes*/
 #define T1Normal                                           0u
 #define PWM_Phase_Correct_8_bit                            1u
 #define PWM_Phase_Correct_9_bit                            2u
 #define PWM_Phase_Correct_10_bit                           3u
 #define CTC_OCR1A                                          4u
 #define Fast_PWM_8_bit                                     5u
 #define Fast_PWM_9_bit                                     6u
 #define Fast_PWM_10_bi                                     7u
 #define PWM_Phase_and_Frequency_Correct_ICR1               8u
 #define PWM_Phase_and_Frequency_Correct_OCR1A              9u
 #define PWM_Phase_Correct_ICR1                             10u
 #define PWM_Phase_Correct_OCR1A                            11u
 #define CTC_ICR1                                           12u
 #define Fast_PWM_ICR1                                      14u
 #define Fast_PWM_OCR1A                                     15u

 #define Timer1_Mode                         Fast_PWM_ICR1
/*----------------------------------------------------------------------------*/
  /*Prescaller initialization*/
#define T1No_clock_source                                                       0u
#define T1Prescaler_1                                                           1u
#define T1Prescaler_8                                                           2u
#define T1Prescaler_64                                                          3u
#define T1Prescaler_256                                                         4u
#define T1Prescaler_1024                                                        5u
#define T1External_clock_source_on_T0_pin_Clock_on_falling_edge                 6u
#define T1External_clock_source_on_T0_pin_Clock_on_rising_edge                  7u
/*Set the prescaller*/
#define T1Clock_Source_Val              T1Prescaler_1
/*------------------------------------------------------------------------*/

/*Compare Output Mode, non-PWM*/
#define Normal_port_operation_OC1A_OC1B_disconnected                           0u
#define Toggle_OC1A_OC1B_on_compar_match                                       1u
#define Clear_OC1A_OC1B_on_compare_match_Set_output_to_low_level               2u
#define Set_OC1A_OC1B_on_compare_match_Set_output_to_high_level                3u

#define Compare_Output_Mode_non_PWM               Normal_port_operation_OC1A_OC1B_disconnected
/*-------------------------------------------------------------------------*/

/*Compare Output Mode, Fast PWM*/

#define FASTPWM_Normal_port_operation_OC1A_OC1B_disconnected                            0u
#define FAST_PWM_WGM13_0                                                                1u
#define FAST_PWM_Clear_OC1A_OC1B_on_compare_match_set_OC1A_OC1B_at_TOP                  2u
#define FAST_PWM_Set_OC1A_OC1B_on_compare_match_clear_OC1A_OC1B_at_TOP                  3u

#define Compare_Output_Mode_on_FAST_PWM               FAST_PWM_Clear_OC1A_OC1B_on_compare_match_set_OC1A_OC1B_at_TOP
/*----------------------------------------------------------------------------*/

/*Compare Output Mode, Phase Correct and Phase and Frequency CorrectPWM*/
#define  Normal_port_operation                                                                                         0u
#define  WGM13_0_settings                                                                                              1u
#define  Clear_OC1A_OC1B_on_compare_match_when_up_counting_set_OC1A_OC1B_on_compare_match_when_downcounting           2u
#define  Set_OC1A_OC1B_on_compare_match_when_up_counting_Clear_OC1A_OC1B_on_compare_match_when_downcounting            3u

#define  Compare_Output_Mode_Phase_Correct_and_Phase_and_Frequency_CorrectPWM                    Normal_port_operation
/*-----------------------------------------------------------------------------*/
#endif /* TIMERS_CFG_H_ */
