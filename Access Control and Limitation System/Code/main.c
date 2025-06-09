/*
 * main.c

 *
 *  Created on: Apr 26, 2024
 *      Author: Omar Khaled
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ErrType.h"
#include"util/delay.h"
#include"DIO_reg.h"
#include"DIO_interface.h"
#include"Port_interface.h"
#include"EXTI_interface.h"
#include"GIE_interface.h"
#include"Timers_interface.h"
#include"Timers_reg.h"

static uint8 Local_u8DoorState = 1;
static uint8 Local_u8Reading = 2;

static uint8 Local_u8LiftState=0;

void INT0_Func(void);
void INT1_Func(void);


void main(void)
{
	PORT_voidInit();
	Timer0_voidInit();
	Timer1_voidInit();
	EXTI_VoidInit();
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
  	_delay_ms(1000);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
  	_delay_ms(100);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
  	_delay_ms(100);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
	_delay_ms(1500);

	while(1)
	{
		EXTI_u8SetCallBack(INT0, &INT0_Func);
		EXTI_u8SetCallBack(INT1, &INT1_Func);
		GIE_VoidEnableGlobal();

	   	if(((GET_BIT(PINA,0)==1)&&(GET_BIT(PINA,7)==1))) /*No person*/
	   	{
	   		_delay_ms(25);
	   		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
	   		Local_u8Reading = 0;
	   	}
	   	else if(((GET_BIT(PINA,0)==0)||(GET_BIT(PINA,7)==0))) /*Detect person*/
	   	{
	   		_delay_ms(25);
	   		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
	   		Local_u8Reading=1;
	   	}

	   if(Local_u8Reading == 1)/*Closed*/
	   {
	   	 if(Local_u8DoorState == 1) /*It's already Closed*/
	   	   {
	   	     /*Stop the motor*/
	   	     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
	   	     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);

	   	   }
	   	   else
	   	   {
	   	        /*Set Direction to Close the door for 3 seconds*/
	   		   Timer0_voidSetCompareMatchValue(128u);
	   	       DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
	   	       DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
	   	       _delay_ms(1500);
	   	       /*State of the door*/
	   	       Local_u8DoorState=1;
	   	   }
	   }
	   else if(Local_u8Reading == 0)/*Opened*/
	   {
	   	 if(Local_u8DoorState == 0) /*It's already Opened*/
	   	 	  {
	   	 		  /*Stop the motor*/
	   	 		  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
	   	 		  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
	   	 	  }
	   	 	  else
	   	 	  {

	   	 		  /*Set Direction to open the door for 3 seconds*/
	   	 		  Timer0_voidSetCompareMatchValue(128u);
	   	 		    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
	   	 		    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
	   	 		    _delay_ms(1500);
	   	 		    /*State of the door*/
	   	 		    Local_u8DoorState=0;

	   	 	  }
	   }
	}

}

void INT0_Func(void)
{
	if(Local_u8LiftState == 0)
	{
		 TIMER1_voidSetComVal(0);
		  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8LiftState=0;
		TIMER1_voidSetComValB(65535);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
		 _delay_ms(6000);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
		 _delay_ms(3700);
		 TIMER1_voidSetComVal(0);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
	}


}
void INT1_Func(void)
{
	if(Local_u8LiftState == 1)
	{
		TIMER1_voidSetComVal(0);




		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
	}
	else
	{
		Local_u8LiftState = 1;
		TIMER1_voidSetComValB(65535);
	    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
		_delay_ms(6000);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
		_delay_ms(3700);
		TIMER1_voidSetComVal(0);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
	}


}

