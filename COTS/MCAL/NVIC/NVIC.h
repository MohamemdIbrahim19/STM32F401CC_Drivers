/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  NVIC header File                                               */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/
#ifndef NVIC_H_
#define NVIC_H_

typedef enum
{
	NVIC_enuOk = 0,
	NVIC_enuNotOk
}NVIC_ERRORS_t;
/*										Data sheet recommended APIs                                       */
NVIC_ERRORS_t NVIC_EnableIRQ(u8 IRQn);
NVIC_ERRORS_t NVIC_DisableIRQ(u8 IRQn);

NVIC_ERRORS_t NVIC_SetPendingIRQ(u8 IRQn);
NVIC_ERRORS_t NVIC_ClearPendingIRQ(u8 IRQn);
NVIC_ERRORS_t NVIC_GetPendingIRQ(u8 IRQn , u32 * Cpy_Addresult);

NVIC_ERRORS_t NVIC_GetActiveIRQ(u8 IRQn , u32 * Cpy_Addresult);

NVIC_ERRORS_t NVIC_SetPriority(u8 IRQn, u8 priority);
NVIC_ERRORS_t NVIC_GetPriority(u8 IRQn , u32 * Cpy_Addresult);

#endif /* NVIC_H_ */














