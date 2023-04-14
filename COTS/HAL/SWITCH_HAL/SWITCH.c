/*
 * SWITCH.c
 *
 *  Created on: Feb 24, 2023
 *      Author: Mohamed
 */
#include "STD_TYPES.h"
#include "SWITCH.h"
#include "SWTCH_cfg.h"
#include "GPIO.h"

SW_Error_t SW_init(void)
{
	SW_Error_t SW_Error = SW_enuOk;

	u8 Local_u8Counter = 0;

	for(Local_u8Counter=0 ; Local_u8Counter<SW_enuNums ; Local_u8Counter++)
	{
		GPIO_strPin_t GPIO_strPin;
		GPIO_strPin[Local_u8Counter].port = SW_arr[Local_u8Counter].SW_port;
		GPIO_strPin[Local_u8Counter].pin =  SW_arr[Local_u8Counter].SW_pin
		GPIO_strPin[Local_u8Counter].speed = SW_arr[Local_u8Counter].SW_speed;
		if(SW_arr[Local_u8Counter].SW_mode == SW_PullUp)
		{
			GPIO_strPin[Local_u8Counter].mode = GPIO_INPUT_PU;
		}
		else
		{
			GPIO_strPin[Local_u8Counter].mode = GPIO_INPUT_PD;
		}

		GPIO_init(&GPIO_strPin);
	}


	return SW_Error;
}
SW_Error_t SW_getStatus(SW_Num_t SW_Num , u8 *Cpy_u8LocalAdd)
{

}



