/*
 * SWITCH_cfg.c
 *
 *  Created on: Feb 24, 2023
 *      Author: Mohamed
 */
#include "STD_TYPES.h"
#include "SWITCH.h"
#include "SWTCH_cfg.h"

const SW_strInfo_t SW_arr[SW_enuNums] = {
		[SW_enuAlarm] =
		{
			.SW_port =  SW_enuPortA,
			.SW_pin =   SW_PIN0,
			.SW_mode =  SW_PullUp,
			.SW_speed = SW_SPEED_HIGH,
			.SW_Name =  "LED R"
		},

		[SW_enuWarning] =
		{
			.SW_port =  SW_enuPortA,
			.SW_pin =   SW_PIN1,
			.SW_mode =  SW_PullUp,
			.SW_speed = SW_SPEED_HIGH,
			.SW_Name =  "LED R"
		}
};


