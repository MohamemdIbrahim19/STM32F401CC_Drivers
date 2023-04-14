/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  SysTick header File                                            */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/
#include "STD_TYPES.h"
#include "SysTick.h"

/*									Status and Control Register											*/
#define SYSTIC_CLEAR_START_M                     0XFFFFFFFE
#define SYSTIC_CLEAR_INT_M                       0XFFFFFFFD
#define SYSTIC_CLEAR_CLKS_M						 0XFFFFFFFB

void (* CallBack)(void);

typedef struct
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	u32 STK_CALIB;
}SysTick_Reg_t;


volatile SysTick_Reg_t * SysTick_RegPtr = ((volatile SysTick_Reg_t *)(0xE000E010));


SysTick_Errors_t SysTick_Start()
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;
	u32 Local_u32Temp = SysTick_RegPtr->STK_CTRL;

						/* Clear Current Value */
	SysTick_RegPtr->STK_VAL = 0;

						/* Select HSI as sysTick Clock */
	Local_u32Temp &= SYSTIC_CLEAR_CLKS_M;
	Local_u32Temp |= ~(SYSTIC_CLEAR_CLKS_M);

						/* Timer Start */
	Local_u32Temp &= SYSTIC_CLEAR_START_M;
	Local_u32Temp |= ~(SYSTIC_CLEAR_START_M);

	SysTick_RegPtr->STK_CTRL = Local_u32Temp;

	return SysTick_Errors;
}

SysTick_Errors_t SysTick_Stop()
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;
	u32 Local_u32Temp = SysTick_RegPtr->STK_CTRL;

	Local_u32Temp &= SYSTIC_CLEAR_START_M;

	SysTick_RegPtr->STK_CTRL = Local_u32Temp;
	return SysTick_Errors;
}

SysTick_Errors_t SysTick_EnableInterrupt()
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;
	u32 Local_u32Temp = SysTick_RegPtr->STK_CTRL;

	Local_u32Temp &= SYSTIC_CLEAR_INT_M;
	Local_u32Temp |= ~(SYSTIC_CLEAR_INT_M);

	SysTick_RegPtr->STK_CTRL = Local_u32Temp;

	return SysTick_Errors;
}

SysTick_Errors_t SysTick_SetPreloadValue(u32 Cpy_u32PreloadVal)
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;

	SysTick_RegPtr->STK_LOAD = Cpy_u32PreloadVal;

	return SysTick_Errors;
}

SysTick_Errors_t SysTick_SetPeriod_ms(u32 Cpy_u32Period_ms)
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;

	/* 16000 to make a 1ms*/


	return SysTick_Errors;
}
SysTick_Errors_t SysTick_SetCallBackFun(void (*Cpy_FunAdd)(void))
{
	SysTick_Errors_t SysTick_Errors = SysTick_enuOk;

	CallBack = Cpy_FunAdd;

	return SysTick_Errors;
}

