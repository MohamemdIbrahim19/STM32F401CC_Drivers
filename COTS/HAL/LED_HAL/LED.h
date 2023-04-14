/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  LED header File                                                */
/*                                  Layer: HAL                                                            */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/
#ifndef LED_H_
#define LED_H_

#include "LED_cfg.h"

/*										LED Mode													*/
typedef enum
{
	LED_enuActiveHigh = 0,
	LED_enuActiveLow
}LED_Mode_t;

/*										LED Values													*/
typedef enum
{
	LED_enuOFF = 0,
	LED_enuON
}LED_State_t;

/* 										LED error Status 											*/
typedef enum
{
	LED_enuOk = 0,
	LED_enuNotOk
}LED_Error_t;

/* 								         Function APIs					                            */
LED_Error_t LED_init(void);
LED_Error_t LED_setState(LED_Num_t LED_Num,LED_State_t LED_State);

#endif /* LED_H_ */
