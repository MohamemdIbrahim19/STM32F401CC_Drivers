/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  GPIO header File                                               */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/*
 * 	                                PREPHIRALS Base addresses
 */

#define GPIOA_BASEADD                    0x40020000
#define GPIOB_BASEADD                    0x40020400
#define GPIOC_BASEADD                    0x40020800
#define GPIOD_BASEADD                    0x40020C00
#define GPIOE_BASEADD                    0x40021000
#define GPIOH_BASEADD                    0x40021C00

/*
 * 									GPIO MODES
 * 									0B ( Moder_(2bits) )| ( type_(1bit) ) | ( PULL up/down_(2bits) )
 */

//                                  Output configuration
#define GPIO_OUTPUT_PP                   0B01000
#define GPIO_OUTPUT_PP_PU                0B01001
#define GPIO_OUTPUT_PP_PD				 0B01010

#define GPIO_OUTPUT_OD                   0B01100
#define GPIO_OUTPUT_OD_PU				 0B01101
#define GPIO_OUTPUT_OD_PD                0B01110

//                                  Alternative function configuration
#define GPIO_AF_PP                       0B10000
#define GPIO_AF_PP_PU                    0B10001
#define GPIO_AF_PP_PD				     0B10010

#define GPIO_AF_OD                       0B10100
#define GPIO_AF_OD_PU				     0B10101
#define GPIO_AF_OD_PD                    0B10110

//                                  Input configuration
#define GPIO_INPUT_FLOATING              0B00000
#define GPIO_INPUT_PU                    0B00001
#define GPIO_INPUT_PD				     0B00010

//									Analog configuration
#define GPIO_ANALOG                      0B11000


/*
 * 									GPIO SPEED
 */
#define GPIO_SPEED_LOW                   ((u32)(0x0))
#define GPIO_SPEED_MEDIUM                ((u32)(0x1))
#define GPIO_SPEED_HIGH                  ((u32)(0x2))
#define GPIO_SPEED_VHIGH                 ((u32)(0x3))

/*
 *                                  GPIO Pins
 */

#define GPIO_PIN0_M                      ((u16)(0x01))
#define GPIO_PIN1_M                      ((u16)(0x02))
#define GPIO_PIN2_M                      ((u16)(0x04))
#define GPIO_PIN3_M                      ((u16)(0x08))
#define GPIO_PIN4_M                      ((u16)(0x10))
#define GPIO_PIN5_M                      ((u16)(0x20))
#define GPIO_PIN6_M                      ((u16)(0x40))
#define GPIO_PIN7_M                      ((u16)(0x80))
#define GPIO_PIN8_M                      ((u16)(0x100))
#define GPIO_PIN9_M                      ((u16)(0x200))
#define GPIO_PIN10_M                     ((u16)(0x400))
#define GPIO_PIN11_M                     ((u16)(0x800))
#define GPIO_PIN12_M                     ((u16)(0x1000))
#define GPIO_PIN13_M                     ((u16)(0x2000))
#define GPIO_PIN14_M                     ((u16)(0x4000))
#define GPIO_PIN15_M                     ((u16)(0x8000))

#define GPIO_PINSNUM                     16


/*
 * 									GPIO ERROR STATUS
 */
typedef enum
{
	GPIO_enuOK=0,
	GPIO_enuNotOK
}GPIO_enuError_t;

/*
 * 									Pin state
 */

typedef enum
{
	GPIO_enuLow = 0,
	GPIO_enuHigh
}GPIO_PIN_state_t;


/*
 * 									GPIO PORTS
 */

typedef enum
{
	 GPIO_enuPORTA = 0,
	 GPIO_enuPORTB,
	 GPIO_enuPORTC,
	 GPIO_enuPORTD,
	 GPIO_enuPORTE,
	 GPIO_enuPORTH,
	 GPIO_enuPortsNum
}GPIO_PORTS_t;

/*
 * 									GPIO AF configuration
 */

typedef enum
{
	GPIO_enuAF0 = 0,
	GPIO_enuAF1,
	GPIO_enuAF2,
	GPIO_enuAF3,
	GPIO_enuAF4,
	GPIO_enuAF5,
	GPIO_enuAF6,
	GPIO_enuAF7,
	GPIO_enuAF8,
	GPIO_enuAF9,
	GPIO_enuAF10,
	GPIO_enuAF11,
	GPIO_enuAF12,
	GPIO_enuAF13,
	GPIO_enuAF14,
	GPIO_enuAF15
}GPIO_AF_t;

/*
 * 									GPIO pins for AF
 */

typedef enum
{
	AF_PIN_0 = 0,
	AF_PIN_1,
	AF_PIN_2,
	AF_PIN_3,
	AF_PIN_4,
	AF_PIN_5,
	AF_PIN_6,
	AF_PIN_7,
	AF_PIN_8,
	AF_PIN_9,
	AF_PIN_10,
	AF_PIN_11,
	AF_PIN_12,
	AF_PIN_13,
	AF_PIN_14,
	AF_PIN_15
}GPIO_PIN_AF_t;

/*
 *									GPIO PIN STRUCTURE
 */

typedef struct
{
	u32 port;
	u32 pin;
	u32 speed;
	u32 mode;
}GPIO_strPin_t;

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_init() initialize GPIO pin                           */
/*                                 @input : pin struct GPIO_strPin includes                               */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											Pin from GPIO Pins macros                                     */
/*											Speed from GPIO SPEED macros                                  */
/*											Mode from GPIO MODES macros                                   */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_init(GPIO_strPin_t *GPIO_strPin);

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_setPin() set pin value High/Low                      */
/*                                 @input : Pin from GPIO Pins macros                                     */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											Pin state type GPIO_PIN_state_t enum                          */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_setPin(GPIO_PORTS_t Cpy_GpioPort ,u32 Cpy_u32GpioPin ,GPIO_PIN_state_t  Cpy_GPIO_PinState);

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_getPinValue() to get a Gpio pin value                */
/*                                 @input : Pin from GPIO Pins macros                                     */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											a local/global variable address to store the pin state        */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_getPinValue(GPIO_PORTS_t Cpy_GpioPort , u32 Cpy_u32GpioPin , u8 * ADD_u8ValPtr);

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_setAF() set alternative function for pins            */
/*                                 @input : Pin from GPIO_PIN_AF_t enum                                   */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											alternative function from GPIO_AF_t enum                      */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_setAF(GPIO_PORTS_t Cpy_GpioPort , GPIO_PIN_AF_t GPIO_PIN_AF , GPIO_AF_t GPIO_AF);



#endif /* GPIO_H_ */
