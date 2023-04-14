/*
 * SWITCH.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Mohamed
 */

#ifndef SWITCH_H_
#define SWITCH_H_

#include "SWTCH_cfg.h"

/* 										SW error Status 											*/
typedef enum
{
	SW_enuOk = 0,
	SW_enuNotOk
}SW_Error_t;

/*										SW States 													*/
typedef enum
{
	SW_enuPressed = 0,
	SW_enuReleased
}SW_State_t;

/*										SW Modes 													*/
typedef enum
{
	SW_PullUp = 0,
	SW_PullDown
}SW_Mode_t;


SW_Error_t SW_init(void);
SW_Error_t SW_getStatus(SW_Num_t SW_Num , u8 *Cpy_u8LocalAdd);

#endif /* SWITCH_H_ */
