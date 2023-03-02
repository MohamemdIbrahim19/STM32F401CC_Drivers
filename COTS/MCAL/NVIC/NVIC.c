/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  NVIC Source File                                               */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#include "STD_TYPES.h"
#include "NVIC.h"

#define NVIC_REG_PINS                 32
#define NVIC_MAX_INTS                 239

#define NVIC_PRIORITY_REG_B           4

#define NVIC_ISERx(n)                 *((volatile u32*)(0x100 +(0x4*n)))
#define NVIC_ICERx(n)				  *((volatile u32*)(0x180 +(0x4*n)))
#define NVIC_ISPRx(n)				  *((volatile u32*)(0x200 +(0x4*n)))
#define NVIC_ICPRx(n)				  *((volatile u32*)(0x280 +(0x4*n)))
#define NVIC_IABRx(n)				  *((volatile u32*)(0x300 +(0x4*n)))
#define NVIC_IPRx(n)				  *((volatile u32*)(0x400 +(0x4*n)))

NVIC_ERRORS_t NVIC_EnableIRQ(u8 IRQn){

	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		NVIC_ISERx(Local_RegNo) |= 1<<Local_pinNo;
	}

	return local_Error_S;
}
NVIC_ERRORS_t NVIC_DisableIRQ(u8 IRQn){

	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		NVIC_ICERx(Local_RegNo) |= 1<<Local_pinNo;
	}

	return local_Error_S;
}

NVIC_ERRORS_t NVIC_SetPendingIRQ(u8 IRQn)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		NVIC_ISPRx(Local_RegNo) |= 1<<Local_pinNo;
	}
	return local_Error_S;
}

NVIC_ERRORS_t NVIC_ClearPendingIRQ(u8 IRQn)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		NVIC_ICPRx(Local_RegNo) |= 1<<Local_pinNo;
	}
	return local_Error_S;
}

NVIC_ERRORS_t NVIC_GetPendingIRQ(u8 IRQn , u32 * Cpy_Addresult)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else if(Cpy_Addresult == ((void*)0))
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		*Cpy_Addresult = (NVIC_ISPRx(Local_RegNo)>>Local_pinNo);
	}
	return local_Error_S;
}

NVIC_ERRORS_t NVIC_GetActiveIRQ(u8 IRQn , u32 * Cpy_Addresult)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_pinNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else if(Cpy_Addresult == ((void*)0))
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_pinNo = IRQn % NVIC_REG_PINS;
		Local_RegNo = IRQn / NVIC_REG_PINS;

		*Cpy_Addresult = NVIC_IABRx((Local_RegNo)>>Local_pinNo);
	}
	return local_Error_S;
}

NVIC_ERRORS_t NVIC_SetPriority(u8 IRQn, u8 priority)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_ByteNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else if(priority>255)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_ByteNo = IRQn % NVIC_PRIORITY_REG_B;
		Local_RegNo = IRQn / NVIC_PRIORITY_REG_B;

		NVIC_IPRx(Local_RegNo) |= (priority <<( 4 * Local_ByteNo));
	}
	return local_Error_S;
}
NVIC_ERRORS_t NVIC_GetPriority(u8 IRQn , u32 * Cpy_Addresult)
{
	NVIC_ERRORS_t local_Error_S = NVIC_enuOk;
	u8 Local_ByteNo = 0;
	u8 Local_RegNo = 0;

	if(IRQn > NVIC_MAX_INTS)
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else if(Cpy_Addresult == ((void*)0))
	{
		local_Error_S = NVIC_enuNotOk;
	}
	else
	{
		Local_ByteNo = IRQn % NVIC_PRIORITY_REG_B;
		Local_RegNo = IRQn / NVIC_PRIORITY_REG_B;

		*Cpy_Addresult = (NVIC_IPRx(Local_RegNo)>>(4*Local_ByteNo));
	}
	return local_Error_S;
}

