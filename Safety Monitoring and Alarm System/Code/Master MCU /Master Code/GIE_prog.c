#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"GIE_reg.h"
#include"GIE_interface.h"



void GIE_VoidEnableGlobal(void)
{
	__asm volatile("SEI");  /*Inline assembly: Set_bit I*/
	/*SET_BIT(SREG,SREG_I);*/
}

void GIE_VoidDisableGlobal(void)
{
	__asm volatile("CLI");  /*Inline assembly: Set_bit I*/
	/*CLR_BIT(SREG,SREG_I);*/
}
/*But it will take some time for operation (3 Clock cycle)*/
/*So we will use an assembly instructions delivered by kit (1 Clock cycle) By SEI for setbit and CLI for clrbit*/
/*Every tool differs from each other in assembly instructions so , we use gcc
GCC: --asm volatile("Assembly instructions") (--) is optional and (volatile) is optional , it means that you don' want compiler to 
optimize your code*/ 


