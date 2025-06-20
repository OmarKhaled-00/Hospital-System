#ifndef PORT_CFG_H
#define PORT_CFG_H

/*configure MC pins directions ,  Options : 1) INPUT
                                            2) OUTPUT
*/
#define PORTA_PIN7_DIR              OUTPUT
#define PORTA_PIN6_DIR              OUTPUT
#define PORTA_PIN5_DIR              OUTPUT
#define PORTA_PIN4_DIR              OUTPUT
#define PORTA_PIN3_DIR              OUTPUT
#define PORTA_PIN2_DIR              OUTPUT
#define PORTA_PIN1_DIR              OUTPUT
#define PORTA_PIN0_DIR              OUTPUT


#define PORTB_PIN0_DIR              OUTPUT
#define PORTB_PIN1_DIR              OUTPUT
#define PORTB_PIN2_DIR              INPUT
#define PORTB_PIN3_DIR              OUTPUT
#define PORTB_PIN4_DIR              INPUT
#define PORTB_PIN5_DIR              INPUT
#define PORTB_PIN6_DIR              OUTPUT
#define PORTB_PIN7_DIR              INPUT


#define PORTC_PIN0_DIR    			OUTPUT
#define PORTC_PIN1_DIR    			OUTPUT
#define PORTC_PIN2_DIR    			OUTPUT
#define PORTC_PIN3_DIR    			OUTPUT
#define PORTC_PIN4_DIR    			OUTPUT
#define PORTC_PIN5_DIR    			OUTPUT
#define PORTC_PIN6_DIR    			OUTPUT
#define PORTC_PIN7_DIR    			OUTPUT

#define PORTD_PIN0_DIR    			OUTPUT
#define PORTD_PIN1_DIR    			OUTPUT
#define PORTD_PIN2_DIR    			OUTPUT
#define PORTD_PIN3_DIR    			OUTPUT
#define PORTD_PIN4_DIR    			OUTPUT
#define PORTD_PIN5_DIR    			OUTPUT
#define PORTD_PIN6_DIR    			OUTPUT
#define PORTD_PIN7_DIR    			OUTPUT

/*Configure the MCU pins intitial value, in case of input direction, options:   1- FLOATING
																			    2- PULLED_UP

										, in case of output direction, options: 1- LOW
																				2- HIGH
*/

#define PORTA_PIN0_INIT_VAL    			LOW
#define PORTA_PIN1_INIT_VAL    			FLOATING
#define PORTA_PIN2_INIT_VAL    			FLOATING
#define PORTA_PIN3_INIT_VAL    			FLOATING
#define PORTA_PIN4_INIT_VAL    			FLOATING
#define PORTA_PIN5_INIT_VAL    			FLOATING
#define PORTA_PIN6_INIT_VAL    			FLOATING
#define PORTA_PIN7_INIT_VAL    			LOW


#define PORTB_PIN0_INIT_VAL    			LOW
#define PORTB_PIN1_INIT_VAL    			LOW
#define PORTB_PIN2_INIT_VAL    			PULLED_UP
#define PORTB_PIN3_INIT_VAL    			LOW
#define PORTB_PIN4_INIT_VAL    			FLOATING
#define PORTB_PIN5_INIT_VAL    			FLOATING
#define PORTB_PIN6_INIT_VAL    			LOW
#define PORTB_PIN7_INIT_VAL    			FLOATING

#define PORTC_PIN0_INIT_VAL    			LOW
#define PORTC_PIN1_INIT_VAL    			LOW
#define PORTC_PIN2_INIT_VAL    			LOW
#define PORTC_PIN3_INIT_VAL    			LOW
#define PORTC_PIN4_INIT_VAL    			LOW
#define PORTC_PIN5_INIT_VAL    			LOW
#define PORTC_PIN6_INIT_VAL    			LOW
#define PORTC_PIN7_INIT_VAL    			LOW
									
#define PORTD_PIN0_INIT_VAL    			LOW
#define PORTD_PIN1_INIT_VAL    			LOW
#define PORTD_PIN2_INIT_VAL    			LOW
#define PORTD_PIN3_INIT_VAL    			LOW
#define PORTD_PIN4_INIT_VAL    			LOW
#define PORTD_PIN5_INIT_VAL    			LOW
#define PORTD_PIN6_INIT_VAL    			LOW
#define PORTD_PIN7_INIT_VAL    			LOW


#endif
