/*
 * SWTCH_cfg.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Mohamed
 */

#ifndef SWTCH_CFG_H_
#define SWTCH_CFG_H_

/*
 * 									  Switch SPEED
 */
#define SW_SPEED_LOW                   ((u32)(0x0))
#define SW_SPEED_MEDIUM                ((u32)(0x1))
#define SW_SPEED_HIGH                  ((u32)(0x2))
#define SW_SPEED_VHIGH                 ((u32)(0x3))

/*
 *                                     Switch Pins
 */

#define SW_PIN0                     ((u16)(0x01))
#define SW_PIN1                     ((u16)(0x02))
#define SW_PIN2                     ((u16)(0x04))
#define SW_PIN3                     ((u16)(0x08))
#define SW_PIN4                     ((u16)(0x10))
#define SW_PIN5                     ((u16)(0x20))
#define SW_PIN6                     ((u16)(0x40))
#define SW_PIN7                     ((u16)(0x80))
#define SW_PIN8                     ((u16)(0x100))
#define SW_PIN9                     ((u16)(0x200))
#define SW_PIN10                    ((u16)(0x400))
#define SW_PIN11                    ((u16)(0x800))
#define SW_PIN12                    ((u16)(0x1000))
#define SW_PIN13                    ((u16)(0x2000))
#define SW_PIN14                    ((u16)(0x4000))
#define SW_PIN15                    ((u16)(0x8000))


/*										Switch Port													*/
typedef enum
{
	SW_enuPortA = 0,
	SW_enuPortB,
	SW_enuPortC,
	SW_enuPortD,
	SW_enuPortE,
	SW_enuPortH
}LED_Port_t;

/*										LED NUMs													*/
typedef enum
{
	SW_enuAlarm = 0,
	SW_enuWarning,
	//....
	SW_enuNums
}SW_Num_t;


typedef struct
{
	u8 SW_port;
	u8 SW_pin;
	u8 SW_mode;
	u8 SW_speed;
	u8 SW_Name[8];
}SW_strInfo_t;

#endif /* SWTCH_CFG_H_ */
