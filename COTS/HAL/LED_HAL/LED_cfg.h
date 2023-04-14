/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  LED Configuration header File                                  */
/*                                  Layer: HAL                                                            */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#ifndef LED_CFG_H_
#define LED_CFG_H_

/*
 * 									  LED SPEED
 */
#define LED_SPEED_LOW                   ((u32)(0x0))
#define LED_SPEED_MEDIUM                ((u32)(0x1))
#define LED_SPEED_HIGH                  ((u32)(0x2))
#define LED_SPEED_VHIGH                 ((u32)(0x3))

/*
 *                                     LED Pins
 */

#define LED_PIN0                     ((u16)(0x01))
#define LED_PIN1                     ((u16)(0x02))
#define LED_PIN2                     ((u16)(0x04))
#define LED_PIN3                     ((u16)(0x08))
#define LED_PIN4                     ((u16)(0x10))
#define LED_PIN5                     ((u16)(0x20))
#define LED_PIN6                     ((u16)(0x40))
#define LED_PIN7                     ((u16)(0x80))
#define LED_PIN8                     ((u16)(0x100))
#define LED_PIN9                     ((u16)(0x200))
#define LED_PIN10                    ((u16)(0x400))
#define LED_PIN11                    ((u16)(0x800))
#define LED_PIN12                    ((u16)(0x1000))
#define LED_PIN13                    ((u16)(0x2000))
#define LED_PIN14                    ((u16)(0x4000))
#define LED_PIN15                    ((u16)(0x8000))


/*										LED Port													*/
typedef enum
{
	LED_enuPortA = 0,
	LED_enuPortB,
	LED_enuPortC,
	LED_enuPortD,
	LED_enuPortE,
	LED_enuPortH
}LED_Port_t;

/*										LED NUMs													*/
typedef enum
{
	LED_enuAlarm = 0,
	LED_enuWarning,
	//....
	LED_enuNums
}LED_Num_t;

/*										LED structure 												*/
typedef struct
{
	u8 LED_port;
	u8 LED_pin;
	u8 LED_mode;
	u8 LED_speed;
	u8 LED_Name[8];
	u8 LED_color[8];
}LED_strInfo_t;

extern const LED_strInfo_t LED_arr[LED_enuNums];

#endif /* LED_CFG_H_ */
