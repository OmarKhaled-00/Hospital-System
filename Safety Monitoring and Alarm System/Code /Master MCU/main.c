#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "DIO_reg.h"
#include "Port_interface.h"
#include "LM35_interface.h"
#include "LDR_interface.h"
#include "ADC_interface.h"
#include "SPI_interface.h"
#include "EXTI_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"
static uint8 u8FlameCha1Reading=1;
static uint8 u8FlameCha2Reading=1;
static uint8 u8GasReading=1;
static uint8 u8TempReadingCounter=0;
static uint8 u8LightReadingCounter=4;
static uint32 u32TempReading=0u;
static uint16 u16LightReading=0u;
void INT0_Func(void);
void INT1_Func(void);
void Gas_Reading(void);
void Temp_Reading(void);
void LDR_Reading(void);
void Flame_Reading(void);
void Flame_Reading2(void);

void main(void)
{
  PORT_voidInit();
  SPI_MasterInit();
  EXTI_VoidInit();
  ADC_VoidInit();
  USART_Init();
  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
  	_delay_ms(1000);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
  	_delay_ms(100);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
  	_delay_ms(100);
  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);

 EXTI_u8SetCallBack(INT0,&INT0_Func);
  EXTI_u8SetCallBack(INT1,&INT1_Func);
  GIE_VoidEnableGlobal();

  while(1)
  {

      Flame_Reading();
      _delay_ms(50);
      Flame_Reading2();
	  _delay_ms(50);
	  Gas_Reading();
	  _delay_ms(50);
	  Temp_Reading();
	  _delay_ms(50);
	  LDR_Reading();
	 _delay_ms(50);



  }
}


void INT0_Func(void)
{
		if(GET_BIT(PIND,2)==0)      /*Channel1_Fire_Detected.*/
		{
			if(u8FlameCha1Reading == 0)
			{

			}
			else
			{
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
				 SPI_Transmit('f');/*Transmit 'f' to the Slave */
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
				 _delay_ms(100);
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
				 _delay_ms(50);
				 u8FlameCha1Reading=0; /*Update the variable.*/
			}

		}
		else           /*No Fire Detected*/
		{
			if(u8FlameCha1Reading == 1)
			{

			}
			else
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
				SPI_Transmit('n');/*Transmit 'n' to the Slave */
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit statue*/
				_delay_ms(100);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
				_delay_ms(50);
				u8FlameCha1Reading=1; /*Update the variable*/
			}

		}
}
void INT1_Func(void)
{
	    if(GET_BIT(PIND,3)==0)/*Channel2_Fire_Detected.*/
			{
				if(u8FlameCha2Reading==0)
				{

				}
				else
				{
					 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
					 SPI_Transmit('F');/*Transmit 'F' to the Slave */
					 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
					 _delay_ms(100);
					 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
					 _delay_ms(50);

					 u8FlameCha2Reading=0;/*Update the variable*/
				}

			}
			else /*No Fire Detected*/
			{
				if(u8FlameCha2Reading == 1)
				{

				}
				else
				{
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
					SPI_Transmit('N');/*Transmit 'n' to the Slave */
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit statue*/
					_delay_ms(100);
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
					_delay_ms(50);

					u8FlameCha2Reading=1;  /*Update the variable*/
				}

			}

}
void Gas_Reading(void)
{
	 /*Check gas Reading*/
		  if(GET_BIT(PINB,2)==0) /*There is a Gas Detected*/
		  {
			  if(u8GasReading == 0)   /*If it's detected before.*/
			  	{
			         /*Do nothing , operations are already operated.*/
			  	}
			  	else /*If it's the first time to detect the Fire , Do the Operations.*/
			  	{
			  	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
			  	 SPI_Transmit('G');/*Transmit 'G' to the Slave */
			  	 _delay_ms(5);
			  	 USART_VoidSend('G'); /*Transmit G to ESP*/
			  	 _delay_ms(5);
			  	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
			  	 _delay_ms(100);
			  	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
			  	 _delay_ms(1000);
			  	 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
			  	 _delay_ms(50);
			  	 u8GasReading=0; /*Update the variable.*/
			  	}
		  }
		  else /*No Gas Detected*/
		  {
			  if(u8GasReading == 1) /*If it's detected before*/
			  	{
			        /*Do nothing, The Operations are already done.*/
			  	}
			  	else  /*If it's the first time , Do the operations.*/
			  	{
			  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
			  	SPI_Transmit('g');/*Transmit 'g' to the Slave */
			  	_delay_ms(5);
			  	USART_VoidSend('g');/*Transmit g to ESP*/
			  	_delay_ms(5);
			  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit statue*/
			  	_delay_ms(100);
			  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
			  	_delay_ms(1000);
			  	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
			  	_delay_ms(50);
			  	u8GasReading=1; /*Update the variable*/
			  	}
		  }

}
void Temp_Reading(void)
{
	u32TempReading = Get_u32Temp();
	_delay_us(25);

	if(u32TempReading >25)
	{
		 if(u8TempReadingCounter == 1)
		 {

		 }
		 else
		 {
			 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
			 SPI_Transmit('H');/*Transmit 'H' to the Slave */
			 _delay_ms(5);
			 USART_VoidSend('H'); /*Transmit H to ESP*/
			 _delay_ms(5);
			 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
			 _delay_ms(100);
			 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
			 _delay_ms(1000);
			 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
			 _delay_ms(50);

			 u8TempReadingCounter=1;
		 }
	}
	else
	{
		if(u8TempReadingCounter == 0)
		{

		}
		else
		{
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
			SPI_Transmit('L');/*Transmit 'L' to the Slave */
			 _delay_ms(5);
			USART_VoidSend('L'); /*Transmit L to ESP*/
			_delay_ms(5);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
			_delay_ms(100);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
			_delay_ms(1000);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
			_delay_ms(50);

			u8TempReadingCounter=0;
		}
	}
}
void LDR_Reading(void)
{
   u16LightReading = LDR_GetValue();
   _delay_us(25);
   if((u16LightReading >= 1)&&(u16LightReading < 49)) /*Dark*/
        {
	       if(u8LightReadingCounter == 0)
	       {

	       }
	       else
	       {
	    	   DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
	    	   SPI_Transmit('D');/*Transmit 'D' to the Slave */
	    	   _delay_ms(5);
	    	   USART_VoidSend('D'); /*Transmit H to ESP*/
	    	  	_delay_ms(5);
	    	   DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
	    	   _delay_ms(100);
	    	   DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
	    	   _delay_ms(1000);
	    	   DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
	    	   _delay_ms(50);
	    	   u8LightReadingCounter =0;
	       }
        }
        else if((u16LightReading >= 49)&&(u16LightReading <500 )) /*Mid Night*/
        {
        	if(u8LightReadingCounter ==1)
        	{

        	}
        	else
        	{
        		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
        		 SPI_Transmit('I');/*Transmit 'I' to the Slave */
        		 _delay_ms(5);
        		USART_VoidSend('I'); /*Transmit I to ESP*/
        		_delay_ms(5);
        		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
        		  _delay_ms(100);
        		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
        		 _delay_ms(1000);
        		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
        		 _delay_ms(50);
        		 u8LightReadingCounter=1;
        	}
        }
        else if(u16LightReading == 683) /*Light*/
        {
         if(u8LightReadingCounter == 2)
         {

         }
         else
         {
        		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
        	     SPI_Transmit('S');/*Transmit 'S' to the Slave */
        	     _delay_ms(5);
        	     USART_VoidSend('S'); /*Transmit S to ESP*/
        	     _delay_ms(5);
        	     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
        	     _delay_ms(100);
        	     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit Statue*/
        	     _delay_ms(1000);
        	     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
        	     _delay_ms(50);
        	     u8LightReadingCounter =2;
         }
        }
}
void Flame_Reading(void)
{
	if(GET_BIT(PIND,2)==0)      /*Channel1_Fire_Detected.*/
		{
			if(u8FlameCha1Reading == 0)
			{

			}
			else
			{
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
				 SPI_Transmit('f');/*Transmit 'f' to the Slave */
				 _delay_ms(5);
				USART_VoidSend('f'); /*Transmit f to ESP*/
				_delay_ms(5);
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
				 _delay_ms(100);
				 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
				 _delay_ms(50);
				 u8FlameCha1Reading=0; /*Update the variable.*/
			}

		}
		else           /*No Fire Detected*/
		{
			if(u8FlameCha1Reading == 1)
			{

			}
			else
			{
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
				SPI_Transmit('n');/*Transmit 'n' to the Slave */
				_delay_ms(5);
				USART_VoidSend('n'); /*Transmit n to ESP*/
				_delay_ms(5);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit statue*/
				_delay_ms(100);
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
				_delay_ms(50);
				u8FlameCha1Reading=1; /*Update the variable*/
			}

		}
}
void Flame_Reading2(void)
{
	 if(GET_BIT(PIND,3)==0)/*Channel2_Fire_Detected.*/
				{
					if(u8FlameCha2Reading==0)
					{

					}
					else
					{
						 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
						 SPI_Transmit('K');/*Transmit 'F' to the Slave */
						 _delay_ms(5);
						 USART_VoidSend('K'); /*Transmit K to ESP*/
						_delay_ms(5);
						 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH); /*Transmit Statue*/
						 _delay_ms(100);
						 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
						 _delay_ms(50);

						 u8FlameCha2Reading=0;/*Update the variable*/
					}

				}
				else /*No Fire Detected*/
				{
					if(u8FlameCha2Reading == 1)
					{

					}
					else
					{
						DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW); /*Slave is working now*/
						SPI_Transmit('k');/*Transmit 'n' to the Slave */
						 _delay_ms(5);
						USART_VoidSend('k'); /*Transmit k to ESP*/
						_delay_ms(5);
						DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW); /*Transmit statue*/
						_delay_ms(100);
						DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH); /*Slave isnot working now*/
						_delay_ms(50);

						u8FlameCha2Reading=1;  /*Update the variable*/
					}

				}

}



