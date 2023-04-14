/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  SysTick header File                                            */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/
#ifndef SYSTICK_H_
#define SYSTICK_H_

// A dumy driver just to use SysTick Timer implementation in OS
// designed on system clock HSI 16 MHZ to avoid low power mode

typedef enum
{
	SysTick_enuOk = 0,
	SysTick_enuNotOk
}SysTick_Errors_t;

SysTick_Errors_t SysTick_Start();
SysTick_Errors_t SysTick_Stop();
SysTick_Errors_t SysTick_EnableInterrupt();
SysTick_Errors_t SysTick_SetPreloadValue(u32 Cpy_u32PreloadVal);
SysTick_Errors_t SysTick_SetPeriod_ms(u32 Cpy_u32Period_ms);
SysTick_Errors_t SysTick_SetCallBackFun();

#endif /* SYSTICK_H_ */
