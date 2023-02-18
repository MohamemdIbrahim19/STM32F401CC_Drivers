/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  GPIO source File                                               */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#include "STD_TYPES.h"
#include "GPIO.h"

#define CLAER_ONE_PINS_MASK                   	 	0XFFFE
#define CLAER_TWO_PINS_MASK                    		0XFFFFFFFC
#define CLAER_FOUR_PINS_MASK                        0XFFFFFFF0

#define CLEAR_CSHIFT_MASK_1(PIN)                 	(((CLAER_ONE_PINS_MASK)<< (PIN)) | ((CLAER_TWO_PINS_MASK)>>(16-(PIN))))
#define CLEAR_CSHIFT_MASK_2(PIN)                 	(((CLAER_TWO_PINS_MASK)<<((PIN)*2))|((CLAER_TWO_PINS_MASK)>>(32-((PIN)*2))))
#define CLEAR_CSHIFT_MASK_4(PIN)                 	(((CLAER_FOUR_PINS_MASK)<<((PIN)*4))|((CLAER_FOUR_PINS_MASK)>>(32-((PIN)*4))))

#define GET_FIRST_PIN_M                             ((u16)(0X01))

#define OTYPER_GET_M                                0X4
#define PUPDR_GET_M                                 0X3



/*
 * 										GPIO REGISTERS
 */
typedef struct
{
	u32 GPIO_MODER;
	u32 GPIO_OTYPER;
	u32 GPIO_OSPEEDR;
	u32 GPIO_PUPDR;
	u32 GPIO_IDR;
	u32 GPIO_ODR;
	u32 GPIO_BSRR;
	u32 GPIO_LCKR;
	u32 GPIO_AFRL;
	u32 GPIO_AFRH;
}GPIO_Reg_t;


volatile GPIO_Reg_t * GPIOA_ptr = ((volatile GPIO_Reg_t *)(GPIOA_BASEADD));
volatile GPIO_Reg_t * GPIOB_ptr = ((volatile GPIO_Reg_t *)(GPIOB_BASEADD));
volatile GPIO_Reg_t * GPIOC_ptr = ((volatile GPIO_Reg_t *)(GPIOC_BASEADD));
volatile GPIO_Reg_t * GPIOD_ptr = ((volatile GPIO_Reg_t *)(GPIOD_BASEADD));
volatile GPIO_Reg_t * GPIOE_ptr = ((volatile GPIO_Reg_t *)(GPIOE_BASEADD));
volatile GPIO_Reg_t * GPIOH_ptr = ((volatile GPIO_Reg_t *)(GPIOH_BASEADD));


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
GPIO_enuError_t GPIO_init(GPIO_strPin_t *GPIO_strPin)
{

	u8 Local_u8PinCounter = 0;
	u32 Local_u32Temp = 0;
	u32 Local_u32Mode = 0;
	u32 Local_u32Typer = 0;
	u32 Local_u32Speed = 0;
	u32 Local_u32PUPDR = 0;


	GPIO_enuError_t Local_ErrorStatus = GPIO_enuOK;

    if(GPIO_strPin->port < GPIO_enuPORTA || GPIO_strPin->port > GPIO_enuPORTH)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else if(GPIO_strPin->speed < GPIO_SPEED_LOW || GPIO_strPin->speed > GPIO_SPEED_VHIGH)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else
	{
		//Loop through pins (that way make it easy to or pins)
		for(Local_u8PinCounter=0;Local_u8PinCounter<GPIO_PINSNUM;Local_u8PinCounter++)
		{
			if(((GPIO_strPin->pin)>>Local_u8PinCounter) & GET_FIRST_PIN_M)
			{
				switch(GPIO_strPin->port)
				{
					case GPIO_enuPORTA:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOA_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOA_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOA_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOA_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOA_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOA_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOA_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOA_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					case GPIO_enuPORTB:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOB_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOB_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOB_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOB_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOB_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOB_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOB_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOB_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					case GPIO_enuPORTC:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOC_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOC_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOC_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOC_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOC_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOC_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOC_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOC_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					case GPIO_enuPORTD:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOD_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOD_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOD_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOD_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOD_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOD_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOD_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOD_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					case GPIO_enuPORTE:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOE_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOE_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOE_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOE_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOE_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOE_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOE_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOE_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					case GPIO_enuPORTH:
						Local_u32Mode = (((u32)((GPIO_strPin->mode)>>3)));
						Local_u32Temp = GPIOH_ptr->GPIO_MODER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32Mode) << (Local_u8PinCounter*2));
						GPIOH_ptr->GPIO_MODER = Local_u32Temp;

						Local_u32Typer = ((u32)(((GPIO_strPin->mode)&OTYPER_GET_M)>>2));
						Local_u32Temp =  GPIOH_ptr->GPIO_OTYPER;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_1(Local_u8PinCounter);
						Local_u32Typer |= (Local_u32Typer << (Local_u8PinCounter));
						GPIOH_ptr->GPIO_OTYPER = Local_u32Temp;

						Local_u32PUPDR = (u32)((GPIO_strPin->mode)&PUPDR_GET_M);
						Local_u32Temp = GPIOH_ptr->GPIO_PUPDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= ((Local_u32PUPDR) << (Local_u8PinCounter*2));
						GPIOH_ptr->GPIO_PUPDR = Local_u32Temp;

						Local_u32Speed = (u32)(GPIO_strPin->speed);
						Local_u32Temp =  GPIOH_ptr->GPIO_OSPEEDR;
						Local_u32Temp &= CLEAR_CSHIFT_MASK_2(Local_u8PinCounter);
						Local_u32Temp |= (Local_u32Speed << (Local_u8PinCounter * 2));
						GPIOH_ptr->GPIO_OSPEEDR = Local_u32Temp;
						break;

					default :  Local_ErrorStatus = GPIO_enuNotOK; break;

				}
			}
		}
	}

	return Local_ErrorStatus;
}

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_setPin() set pin value High/Low                      */
/*                                 @input : Pin from GPIO Pins macros                                     */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											Pin state type GPIO_PIN_state_t enum                          */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_setPin(GPIO_PORTS_t Cpy_GpioPort ,u32 Cpy_u32GpioPin ,GPIO_PIN_state_t  Cpy_GPIO_PinState)
{
	u8 Local_u8PinCounter = 0;

	GPIO_enuError_t Local_ErrorStatus = GPIO_enuOK;

	    if(Cpy_GpioPort < GPIO_enuPORTA || Cpy_GpioPort > GPIO_enuPORTH)
		{
			Local_ErrorStatus = GPIO_enuNotOK;
		}
	    else if(Cpy_GPIO_PinState< GPIO_enuLow || Cpy_GPIO_PinState>GPIO_enuHigh)
	    {
			Local_ErrorStatus = GPIO_enuNotOK;
	    }

	    else
	    {
			for(Local_u8PinCounter=0;Local_u8PinCounter<GPIO_PINSNUM;Local_u8PinCounter++)
			{
				if((Cpy_u32GpioPin>>Local_u8PinCounter) & GET_FIRST_PIN_M)
				{

					switch(Cpy_GpioPort)
					{
						case GPIO_enuPORTA :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOA_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOA_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;
						case GPIO_enuPORTB :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOB_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOB_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;
						case GPIO_enuPORTC :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOC_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOC_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;
						case GPIO_enuPORTD :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOD_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOD_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;
						case GPIO_enuPORTE :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOE_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOE_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;
						case GPIO_enuPORTH :
							if(Cpy_GPIO_PinState == GPIO_enuHigh)
							{
								GPIOH_ptr->GPIO_BSRR |= (1<<Local_u8PinCounter);
							}
							else
							{
								GPIOH_ptr->GPIO_BSRR |= (1<<(Local_u8PinCounter+GPIO_PINSNUM));
							}
							break;

						default :  Local_ErrorStatus = GPIO_enuNotOK; break;
					}

				}
			}
	    }

	return Local_ErrorStatus;
}

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_getPinValue() to get a Gpio pin value                */
/*                                 @input : Pin from GPIO Pins macros                                     */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											a local/global variable address to store the pin state        */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_getPinValue(GPIO_PORTS_t Cpy_GpioPort , u32 Cpy_u32GpioPin , u8 * ADD_u8ValPtr)
{
	GPIO_enuError_t Local_ErrorStatus = GPIO_enuOK;

	u32 Local_u32Temp = GPIO_enuLow;
	*ADD_u8ValPtr = GPIO_enuLow;

	if(Cpy_GpioPort < GPIO_enuPORTA || Cpy_GpioPort>GPIO_enuPORTH)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else if(ADD_u8ValPtr == ((void *)(0)))
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else
	{
		switch(Cpy_GpioPort)
		{
			case GPIO_enuPORTA:
				Local_u32Temp = ((GPIOA_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			case GPIO_enuPORTB:
				Local_u32Temp = ((GPIOB_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			case GPIO_enuPORTC:
				Local_u32Temp = ((GPIOC_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			case GPIO_enuPORTD:
				Local_u32Temp = ((GPIOD_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			case GPIO_enuPORTE:
				Local_u32Temp = ((GPIOE_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			case GPIO_enuPORTH:
				Local_u32Temp = ((GPIOH_ptr->GPIO_ODR) & Cpy_u32GpioPin);
				if(Local_u32Temp)
				{
					*ADD_u8ValPtr = GPIO_enuHigh;
				}
				break;

			default : Local_ErrorStatus = GPIO_enuNotOK;    break;
		}
	}

	return Local_ErrorStatus;
}

/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                 @description GPIO_setAF() set alternative function for pins            */
/*                                 @input : Pin from GPIO_PIN_AF_t enum                                   */
/*                                          Port type GPIO_PORTS_t enum                                   */
/*											alternative function from GPIO_AF_t enum                      */
/* 								   @output: return Gpio error status                                      */
/**********************************************************************************************************/
/**********************************************************************************************************/
GPIO_enuError_t GPIO_setAF(GPIO_PORTS_t Cpy_GpioPort , GPIO_PIN_AF_t GPIO_PIN_AF , GPIO_AF_t GPIO_AF)
{

	u32 Local_u32Temp = 0;

	GPIO_enuError_t Local_ErrorStatus = GPIO_enuOK;
	if(Cpy_GpioPort < GPIO_enuPORTA || Cpy_GpioPort>GPIO_enuPORTH)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else if(GPIO_AF<GPIO_enuAF0 || GPIO_AF>GPIO_enuAF15)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else if(GPIO_PIN_AF<AF_PIN_0 || GPIO_PIN_AF>AF_PIN_15)
	{
		Local_ErrorStatus = GPIO_enuNotOK;
	}
	else
	{
		switch(Cpy_GpioPort)
		{
			case GPIO_enuPORTA:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOA_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOA_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOA_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOA_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			case GPIO_enuPORTB:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOB_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOB_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOB_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOB_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			case GPIO_enuPORTC:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOC_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOC_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOC_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOC_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			case GPIO_enuPORTD:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOD_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOD_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOD_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOD_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			case GPIO_enuPORTE:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOE_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOE_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOE_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOE_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			case GPIO_enuPORTH:
				if(GPIO_PIN_AF < AF_PIN_8)
				{
					Local_u32Temp = GPIOH_ptr->GPIO_AFRL;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF);
					Local_u32Temp |= ((GPIO_AF)<< (GPIO_PIN_AF * 4));
					GPIOH_ptr->GPIO_AFRL = Local_u32Temp;
				}
				else
				{
					Local_u32Temp = GPIOH_ptr->GPIO_AFRH;
					Local_u32Temp &= CLEAR_CSHIFT_MASK_4(GPIO_PIN_AF%8);
					Local_u32Temp |= ((GPIO_AF)<< ((GPIO_PIN_AF%8) * 4));
					GPIOH_ptr->GPIO_AFRH = Local_u32Temp;
				}
				break;

			default : Local_ErrorStatus = GPIO_enuNotOK;    break;
		}
	}

	return Local_ErrorStatus;
}



