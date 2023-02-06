/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  RCC header File                                                */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/

#ifndef RCC_H_
#define RCC_H_

// Running clock in SWS
#define RUNNING_CLOCK_HSI               0X00
#define RUNNING_CLOCK_HSE	 		    0X01
#define RUNNING_CLOCK_ PLL              0X02

// AHB Prescaler division factors
#define AHB_0_PRESCALLER                0X00
#define AHB_2_PRESCALLER                0X08
#define AHB_4_PRESCALLER                0X09
#define AHB_8_PRESCALLER                0X0A
#define AHB_16_PRESCALLER               0X0B
#define AHB_64_PRESCALLER               0X0C
#define AHB_128_PRESCALLER              0X0D
#define AHB_256_PRESCALLER              0X0E
#define AHB_512_PRESCALLER              0X0F

// ABP1 Prescaler division factors
#define ABP1_0_PRESCALLER               0X00
#define ABP1_2_PRESCALLER               0X04
#define ABP1_4_PRESCALLER               0X05
#define ABP1_8_PRESCALLER               0X06
#define ABP1_16_PRESCALLER              0X07

// ABP2 Prescaler division factors
#define ABP2_0_PRESCALLER               0X00
#define ABP2_2_PRESCALLER               0X04
#define ABP2_4_PRESCALLER               0X05
#define ABP2_8_PRESCALLER               0X06
#define ABP2_16_PRESCALLER              0X07


// RCC APIS return types
typedef enum
{
	RCC_enuOk = 0, RCC_enuNotOk
} RCC_enuErrorS_t;

// RCC clock source definitions
typedef enum
{
	ClockSource_HSI = 0, ClockSource_HSE, ClockSource_PLL
} RCC_enuClockSource_t;

// RCC clock states
typedef enum
{
	ClockState_ON = 0, ClockState_OFF
} RCC_enuClockState_t;

// RCC clock check ready state
typedef enum
{
	Clock_READY = 0, Clock_NotREADY
} RCC_enuClockRady_t;

// RCC PLL clock source configuration
typedef enum
{
	PLL_HSIsrc = 0, PLL_HSEsrc
} PLL_src_t;

// PLL (P) parameter division factors
typedef enum
{
	PLLP_2 = 0, PLLP_4, PLLP_6, PLLP_8
} PLL_pConfig_t;

// AHB1 Peripherals
typedef enum
{
	AHB1_PREI_GPIOAen = 0, AHB1_PREI_GPIOBen, AHB1_PREI_GPIOCen, AHB1_PREI_GPIODen, AHB1_PREI_GPIOEen,
	AHB1_PREI_GPIOHen = 7,
	AHB1_PREI_CRCen = 12,
	AHB1_PREI_DMA1en = 21, AHB1_PREI_DMA2en
} AHB1_PREI_t;

// AHB2 Peripherals
typedef enum
{
	AHB2_PREI_OTGFSen = 7
} AHB2_PREI_t;

// ABP1 Peripherals
typedef enum
{
	ABP1_PREI_TIM2en = 0, ABP1_PREI_TIM3en, ABP1_PREI_TIM4en, ABP1_PREI_TIM5en,
	ABP1_PREI_WWDGen = 11,
	ABP1_PREI_SPI2en = 14, ABP1_PREI_SPI3en,
	ABP1_PREI_USART2en = 17,
	ABP1_PREI_I2C1en = 21, ABP1_PREI_I2C2en, ABP1_PREI_I2C3en,
	ABP1_PREI_PWRen = 28
} ABP1_PREI_t;

// ABP2 Peripherals
typedef enum
{
	ABP2_PREI_TIM1en = 0,
	ABP2_PREI_USART1en = 4, ABP2_PREI_USART6en ,
	ABP2_PREI_ADC1en = 8,
	ABP2_PREI_SDIOen = 11, ABP2_PREI_SPI1en , ABP2_PREI_SPI4en , ABP2_PREI_SYSCFGen ,
	ABP2_PREI_TIM9en = 16, ABP2_PREI_TIM10en , ABP2_PREI_TIM11en
} ABP2_PREI_t;

// Peripheral state on/off
typedef enum
{
	PREI_StateON = 0, PREI_StateOFF
} PREI_State_t;


/**************************************************** APIS Prototypes ***********************************************/

/*
 * ******************************************************************************************************************
 * @description : control HSI/E PLL
 * @input : Clock source , Clock state ON/OFF
 * @output: OK case correct parameters , clock is on and ready , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlClockSourceState(
		RCC_enuClockSource_t RCC_enuClockSource,
		RCC_enuClockState_t RCC_enuClockState);

/*
 * ******************************************************************************************************************
 * @description : Select a clock source HSI/E PLL
 * @input :  Clock source
 * @output:  OK case correct parameters , SW == SWS , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_selectClockSource(RCC_enuClockSource_t RCC_enuClockSource);

/*
 * ******************************************************************************************************************
 * @description : Get the system clock
 * @input : a variable address to be de-refrenced
 * @output: OK , running clock case valid input address , NotOk else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_getRunningClock(u32 *ADD_RunningClock);

/*
 * ******************************************************************************************************************
 * @description : Configure PLL clock
 * @input : PLL parameters (M,N,P,Q,SRC)
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_configPLL(u32 PLLM, u32 PLLN, PLL_pConfig_t PLLP, u32 PLLQ,
		PLL_src_t PLL_src);

/*
 * ******************************************************************************************************************
 * @description : set AHB Prescaler
 * @input : prescaler value
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlAHBprescaller(u32 AHBprescaler);

/*
 * ******************************************************************************************************************
 * @description : set ABP1 Prescaler
 * @input : prescaler value
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlABP1prescaller(u32 ABP1prescaler);

/*
 * ******************************************************************************************************************
 * @description : set ABP2 Prescaler
 * @input : prescaler value
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlABP2prescaller(u32 ABP2prescaler);

/*
 * ******************************************************************************************************************
 * @description : Control AHB1 Peripherals Enable/dis
 * @input : Peripheral , State
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlAHB1Prephiral(AHB1_PREI_t AHB1_PREI,
		PREI_State_t PREI_State);

/*
 * ******************************************************************************************************************
 * @description : Control AHB2 Peripherals Enable/dis
 * @input : Peripheral , State
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlAHB2Prephiral(AHB2_PREI_t AHB2_PREI,
		PREI_State_t PREI_State);

/*
 * ******************************************************************************************************************
 * @description : Control ABP1 Peripherals Enable/dis
 * @input : Peripheral , State
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlABP1Prephiral(ABP1_PREI_t ABP1_PREI,
		PREI_State_t PREI_State);

/*
 * ******************************************************************************************************************
 * @description : Control ABP2 Peripherals Enable/dis
 * @input : Peripheral , State
 * @output: OK , valid parameters , NotOK else
 * ******************************************************************************************************************
 */
RCC_enuErrorS_t rcc_controlABP2Prephiral(ABP2_PREI_t ABP2_PREI,
		PREI_State_t PREI_State);

#endif /* RCC_H_ */
