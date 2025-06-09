#include "STD_TYPES.h"
#include "util/delay.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include "DIO_interface.h"
#include "Port_interface.h"
#include "SPI_interface.h"
#include "Timers_interface.h"
void Gas_Alarm_On(void);
void Gas_Alarm_Off(void);
void Fire_Alarm_OnCh1(void);
void Fire_Alarm_OffCh1(void);
void Fire_Alarm_OnCh2(void);
void Fire_Alarm_OffCh2(void);
void Case_Dark(void);
void Case_Mid(void);
void Case_Light(void);
static uint8 u8DCounter=0;
static uint8 u8MCounter=0;
static uint8 u8LCounter=0;
volatile static uint8 u8Received=0;

void main(void)
{
    PORT_voidInit();
	SPI_SlaveInit();
	Timer0_voidInit();
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
	_delay_ms(1000);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);


	while(1)
	{
		u8Received = SPI_SlaveReceive();
		_delay_ms(25);
		if(u8Received != 0);
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_HIGH);
		switch(u8Received)
		{
		case('f'):Fire_Alarm_OnCh1();break;
		case('n'):Fire_Alarm_OffCh1();break;
		case('K'):Fire_Alarm_OnCh2();break;
		case('k'):Fire_Alarm_OffCh2();break;
		case('H'):DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_HIGH);break;
		case('L'):DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);break;
		case('D'):Case_Dark();break;
		case('I'):Case_Mid();break;
		case('S'):Case_Light();break;
		case('G'):Gas_Alarm_On();DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);break;
		case('g'):Gas_Alarm_Off();DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);break;
		default:u8Received=0;break;
		}
		DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN7,DIO_u8PIN_LOW);

	}
}



void Gas_Alarm_On(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Buzzer on*/
	/*Generating Yellow Color indicates that there is a Gas*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);/*RED is ON*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);/*GREEN is ON*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH); /*Ventilation Fan 1 ON*/
	_delay_ms(100);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH); /*Ventilation Fan 2 ON*/

}
void Gas_Alarm_Off(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW); /*Buzzer OFF*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);/*RED is OFF*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);/*GREEN*/
	/*Generating Blue Color indicates that there is no  Gas*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW); /*Ventilation Fan 1 OFF*/
	_delay_ms(50);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW); /*Ventilation Fan 2 OFF*/
}

void Fire_Alarm_OnCh1(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Buzzer on*/
	/*Generating Red Color indicates that there is a Fire*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);/*RED is ON PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);/*GREEN PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Water Pump1*/

}
void Fire_Alarm_OnCh2(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Buzzer on*/
	/*Generating Red Color indicates that there is a Fire*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);/*RED is ON PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);/*GREEN PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH); /*Water Pump2*/

}
void Fire_Alarm_OffCh1(void)
{
	DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW); /*Buzzer OFF*/
	/*Generating Green Color indicates that there is no Fire*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);/*RED is ON PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);/*GREEN PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Water Pump1*/
	_delay_ms(500);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);/*RED is ON PORTC*/
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);/*GREEN PORTC*/


}
void Fire_Alarm_OffCh2(void)
{
	 DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW); /*Buzzer OFF*/
	 /*Generating Green Color indicates that there is no Fire*/
     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);/*RED is ON PORTC*/
	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);/*GREEN PORTC*/
	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW); /*Water Pump2*/
	_delay_ms(500);
	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);/*RED is ON PORTC*/
	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);/*GREEN PORTC*/

}
void Case_Dark(void)
{
	if(u8DCounter == 1)
	{

	}
	else
	{
		Timer0_voidSetCompareMatchValue(255);
		u8DCounter=1;
		u8MCounter=0;
		u8LCounter=0;
	}
}
void Case_Mid(void)
{
	if(u8MCounter == 1)
		{

		}
		else
		{
			Timer0_voidSetCompareMatchValue(100);
			u8MCounter=1;
			u8DCounter=0;
			u8LCounter=0;
		}
}
void Case_Light(void)
{
	if(u8LCounter == 1)
		{

		}
		else
		{
			Timer0_voidSetCompareMatchValue(10);
			u8LCounter=1;
			u8DCounter=0;
			u8MCounter=0;
		}
}
