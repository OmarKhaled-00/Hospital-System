#include"STD_TYPES.h"
#include"Port_prv.h"
#include"Port_cfg.h"
#include"Port_interface.h"
#include"Port_reg.h"




void PORT_voidInit(void)
{
	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;
	
	PORTA = PORTA_INIT_VAL;
	PORTB = PORTB_INIT_VAL;
	PORTC = PORTC_INIT_VAL;
	PORTD = PORTD_INIT_VAL;
}
