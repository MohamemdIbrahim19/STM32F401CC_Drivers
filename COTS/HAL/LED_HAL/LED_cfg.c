/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  LED Configuration source File                                  */
/*                                  Layer: HAL                                                            */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/
#include "STD_TYPES.h"
#include "LED.h"
#include "LED_cfg.h"

const LED_strInfo_t LED_arr[LED_enuNums] = {
		[LED_enuAlarm] =
		{
			.LED_port =  LED_enuPortA,
			.LED_pin =   LED_PIN0,
			.LED_mode =  LED_enuActiveHigh,
			.LED_speed = LED_SPEED_HIGH,
			.LED_Name =  "LED R",
			.LED_color = "RED"
		},

		[LED_enuWarning] =
		{
			.LED_port =  LED_enuPortA,
			.LED_pin =   LED_PIN1,
			.LED_mode =  LED_enuActiveHigh,
			.LED_speed = LED_SPEED_HIGH,
			.LED_Name =  "LED L",
			.LED_color = "BLUE"
		}
};
