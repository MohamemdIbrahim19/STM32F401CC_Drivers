/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  LED source File                                                */
/*                                  Layer: HAL                                                            */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#include "STD_TYPES.h"
#include "LED.h"
#include "LED_cfg.h"
#include "GPIO.h"

LED_Error_t LED_init(void)
{
	LED_Error_t LED_Error = LED_enuOk;
	u8 Local_u8LEDCounter = 0;

	for(Local_u8LEDCounter=0 ; Local_u8LEDCounter<LED_enuNums ; Local_u8LEDCounter++)
	{
		GPIO_strPin_t GPIO_strPin;
		GPIO_strPin.port = LED_arr[Local_u8LEDCounter].LED_port;
		GPIO_strPin.pin =  LED_arr[Local_u8LEDCounter].LED_pin;
		GPIO_strPin.mode = GPIO_OUTPUT_PP;
		GPIO_strPin.speed = LED_arr[Local_u8LEDCounter].LED_speed;
		GPIO_init(&GPIO_strPin);
	}

	return LED_Error;
}


LED_Error_t LED_setState(LED_Num_t LED_Num,LED_State_t LED_State)
{
	LED_Error_t LED_Error = LED_enuOk;

	if(LED_Num<0 || LED_Num>LED_enuNums)
	{
		LED_Error = LED_enuNotOk;
	}
	else if(LED_State<LED_enuOFF || LED_State>LED_enuON)
	{
		LED_Error = LED_enuNotOk;
	}
	else
	{
		GPIO_setPin(LED_arr[LED_Num].LED_port,LED_arr[LED_Num].LED_pin , LED_arr[LED_Num].LED_mode ^LED_State);
	}

	return LED_Error;
}
