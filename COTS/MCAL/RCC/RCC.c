/**********************************************************************************************************/
/**********************************************************************************************************/
/*                                  File:  RCC Source File                                                */
/*                                  Layer: MCAL STM32F401CC                                               */
/*                                  Author: Mohamed_Ibrahim                                               */
/**********************************************************************************************************/
/**********************************************************************************************************/


#include "STD_TYPES.h"
#include "RCC.h"

/****************************   RCC registers Clear and get masks           ********************************/

#define HSI_CLEAR_MASK            0XFFFFFFFE
#define HSE_CLEAR_MASK            0XFFFEFFFF
#define PLL_CLEAR_MASK            0XFEFFFFFF

#define HSI_READY_MASK            0X2
#define HSE_READY_MASK            0X20000
#define PLL_READY_MASK            0X2000000

#define SW_CLEAR_MASK             0XFFFFFFFC
#define SWS_GET_MASK              0X0C

#define HSI_SW_SET_MASK           0X0
#define HSE_SW_SET_MASK			  0X01
#define PLL_SW_SET_MASK           0X02

#define PLLM_CLEAR_MASK           0XFFFFFFC0
#define PLLN_CLEAR_MASK           0XFFFF803F
#define PLLP_CLEAR_MASK           0XFFFCFFFF
#define PLLQ_CLEAR_MASK			  0XF0FFFFFF
#define PLLSRC_CLEAR_MASK		  0XFFBFFFFF

#define AHB_PRE_CLAER_MASK        0XFFFFFF0F
#define ABP1_PRE_CLEAR_MASK       0XFFFFE3FF
#define ABP2_PRE_CLEAR_MASK       0XFFFF1FFF

#define PLL_M_SHIFT               0
#define PLL_N_SHIFT               6
#define PLL_P_SHIFT               16
#define PLL_Q_SHIFT               24
#define PLL_SRC_SHIFT             22

#define AHB_SHIFT                 4
#define ABP1_SHIFT                10
#define ABP2_SHIFT                13

/**************************************** RCC registers Structure *******************************************/
typedef struct {
	u32 RCC_CR_REG;
	u32 RCC_PLLCFGR_REG;
	u32 RCC_CFGR_REG;
	u32 RCC_CIR_REG;
	u32 RCC_AHB1RSTR_REG;
	u32 RCC_AHB2RSTR_REG;
	u32 RCC_RESREVED1_REG;
	u32 RCC_RESREVED2_REG;
	u32 RCC_APB1RSTR_REG;
	u32 RCC_APB2RSTR_REG;
	u32 RCC_RESREVED3_REG;
	u32 RCC_RESREVED4_REG;
	u32 RCC_AHB1ENR_REG;
	u32 RCC_AHB2ENR_REG;
	u32 RCC_RESREVED5_REG;
	u32 RCC_RESREVED6_REG;
	u32 RCC_APB1ENR_REG;
	u32 RCC_APB2ENR_REG;
	u32 RCC_RESREVED7_REG;
	u32 RCC_RESREVED8_REG;
	u32 RCC_AHB1LPENR_REG;
	u32 RCC_AHB2LPENR_REG;
	u32 RCC_RESREVED9_REG;
	u32 RCC_RESREVED10_REG;
	u32 RCC_APB1LPENR_REG;
	u32 RCC_APB2LPENR_REG;
	u32 RCC_RESREVED11_REG;
	u32 RCC_RESREVED12_REG;
	u32 RCC_BDCR_REG;
	u32 RCC_CSR_REG;
	u32 RCC_RESREVED13_REG;
	u32 RCC_RESREVED14_REG;
	u32 RCC_SSCGR_REG;
	u32 RCC_PLLI2SCFGR_REG;
	u32 RCC_RESREVED15_REG;
	u32 RCC_DCKCFGR_REG;
} RCC_REG_t;


/************************************** Pointer to RCC structure *********************************************************/
RCC_REG_t * const RCC = ((RCC_REG_t *)0x40023800);


/************************************* APIS Implementation ***************************************************************/

RCC_enuErrorS_t rcc_controlClockSourceState(RCC_enuClockSource_t RCC_enuClockSource, RCC_enuClockState_t RCC_enuClockState) {

	RCC_enuErrorS_t Error_Status = RCC_enuOk;
	u32 Local_u32temp = RCC->RCC_CR_REG;
	u32 timeOut = 0xFFF;

	if (RCC_enuClockSource < ClockSource_HSI || RCC_enuClockSource > ClockSource_PLL)
	{
		 Error_Status = RCC_enuNotOk;
	}
	else if (RCC_enuClockState<ClockState_ON || RCC_enuClockState>ClockState_OFF)
	{
		 Error_Status = RCC_enuNotOk;
	}
	else
	{
		switch(RCC_enuClockSource)
		{
		    /******************************************      Case HSI    *****************************************************/
			case ClockSource_HSI:
				if(RCC_enuClockState == ClockState_OFF)
				{
					Local_u32temp &= HSI_CLEAR_MASK;
					RCC->RCC_CR_REG = Local_u32temp;
				}
				else
				{
					Local_u32temp &= HSI_CLEAR_MASK;
					Local_u32temp |= ~(HSI_CLEAR_MASK);
					RCC->RCC_CR_REG = Local_u32temp;

					while( (!((RCC->RCC_CR_REG & HSI_READY_MASK) == HSI_READY_MASK)) && timeOut )
					{
						timeOut--;
					}

					if(timeOut == 0)
					{
						Error_Status = RCC_enuNotOk;
					}
				}

				break;

		        /******************************************      Case HSE    *****************************************************/
				case ClockSource_HSE:
					if(RCC_enuClockState == ClockState_OFF)
					{
						Local_u32temp &= HSE_CLEAR_MASK;
						RCC->RCC_CR_REG = Local_u32temp;
					}
					else
					{
						Local_u32temp &= HSE_CLEAR_MASK;
						Local_u32temp |= ~(HSE_CLEAR_MASK);
						RCC->RCC_CR_REG = Local_u32temp;

						while( (!((RCC->RCC_CR_REG & HSE_READY_MASK) == HSE_READY_MASK)) && timeOut )
						{
							timeOut--;
						}

						if(timeOut == 0)
						{
							Error_Status = RCC_enuNotOk;
						}
					}

					break;

		        /******************************************      Case PLL    *****************************************************/
				case ClockSource_PLL:
					if(RCC_enuClockState == ClockState_OFF)
					{
						Local_u32temp &= PLL_CLEAR_MASK;
						RCC->RCC_CR_REG = Local_u32temp;
					}
					else
					{
						Local_u32temp &= PLL_CLEAR_MASK;
						Local_u32temp |= ~(PLL_CLEAR_MASK);
						RCC->RCC_CR_REG = Local_u32temp;

						while( (!((RCC->RCC_CR_REG & PLL_READY_MASK) == PLL_READY_MASK)) && timeOut )
						{
							timeOut--;
						}

						if(timeOut == 0)
						{
							Error_Status = RCC_enuNotOk;
						}
					}

					break;

				default : Error_Status = RCC_enuNotOk;         break;
		}
	}



	return Error_Status;
}

RCC_enuErrorS_t rcc_selectClockSource(RCC_enuClockSource_t RCC_enuClockSource)
{
		RCC_enuErrorS_t Error_Status = RCC_enuOk;
		u32 Local_u32temp = RCC->RCC_CFGR_REG;
		u32 timeOut = 0xFFF;

		if (RCC_enuClockSource < ClockSource_HSI || RCC_enuClockSource > ClockSource_PLL)
		{
			 Error_Status = RCC_enuNotOk;
		}
		else
		{
			switch(RCC_enuClockSource)
			{
			    /******************************************      Case HSI    *****************************************************/
			case ClockSource_HSI:
				if(!(RCC->RCC_CR_REG & HSI_READY_MASK))
				{
					// Clock isn't ready
					Error_Status = RCC_enuNotOk;
				}
				else
				{
					Local_u32temp &= SW_CLEAR_MASK;
					Local_u32temp |= HSI_SW_SET_MASK;
					RCC->RCC_CFGR_REG = Local_u32temp;

					while( (!((((RCC->RCC_CFGR_REG) & SWS_GET_MASK)>>2) == HSI_SW_SET_MASK))  && timeOut )
					{
						timeOut--;
					}

					if(timeOut == 0)
					{
						Error_Status = RCC_enuNotOk;
					}
				}
				break;

			/******************************************      Case HSE    *****************************************************/
			case ClockSource_HSE:
				if(!(RCC->RCC_CR_REG & HSE_READY_MASK))
				{
					// Clock isn't ready
					Error_Status = RCC_enuNotOk;
				}
				else
				{
					Local_u32temp &= SW_CLEAR_MASK;
					Local_u32temp |= HSE_SW_SET_MASK;
					RCC->RCC_CFGR_REG = Local_u32temp;

					while( (!((((RCC->RCC_CFGR_REG) & SWS_GET_MASK)>>2) == HSE_SW_SET_MASK))  && timeOut )
					{
						timeOut--;
					}

					if(timeOut == 0)
					{
						Error_Status = RCC_enuNotOk;
					}
				}
				break;

			/******************************************      Case PLL    *****************************************************/
			case ClockSource_PLL:
				if(!(RCC->RCC_CR_REG & PLL_READY_MASK))
				{
					// Clock isn't ready
					Error_Status = RCC_enuNotOk;
				}
				else
				{
					Local_u32temp &= SW_CLEAR_MASK;
					Local_u32temp |= PLL_SW_SET_MASK;
					RCC->RCC_CFGR_REG = Local_u32temp;

					while( (!((((RCC->RCC_CFGR_REG) & SWS_GET_MASK)>>2) == PLL_SW_SET_MASK))  && timeOut )
					{
						timeOut--;
					}

					if(timeOut == 0)
					{
						Error_Status = RCC_enuNotOk;
					}
				}
				break;

			default : Error_Status = RCC_enuNotOk;    break;

		}
	}

		return Error_Status;
}

 RCC_enuErrorS_t rcc_getRunningClock(u32 *ADD_RunningClock) {

	 	RCC_enuErrorS_t Error_Status = RCC_enuOk;
		u32 Local_u32temp = RCC->RCC_CFGR_REG;

		if(ADD_RunningClock == ((void *)0x0))
		{
			Error_Status = RCC_enuNotOk;
		}
		else
		{
			 *ADD_RunningClock = ((Local_u32temp & SWS_GET_MASK)>>2);
		}

		return Error_Status;
 }

 RCC_enuErrorS_t rcc_configPLL(u32 PLLM, u32 PLLN, PLL_pConfig_t PLLP, u32 PLLQ,PLL_src_t PLL_src)
 {
		RCC_enuErrorS_t ConfigError_Status = RCC_enuOk;
		RCC_enuErrorS_t ClockError_Status = RCC_enuOk;
		u32 Local_u32temp = RCC->RCC_PLLCFGR_REG;

		u32 Running_Clock = 0;

		ClockError_Status = rcc_getRunningClock(&Running_Clock);
		if(ClockError_Status != RCC_enuOk)
		{
			ConfigError_Status = RCC_enuNotOk;
		}
		else
		{
			if(Running_Clock == PLL_SW_SET_MASK)
			{
				// PLL is the running Clock
				ConfigError_Status = RCC_enuNotOk;
			}
			else
			{
				if(PLLM<2 || PLLM>63)
				{
					ConfigError_Status = RCC_enuNotOk;
				}
				else if(PLLN<192 || PLLN>432)
				{
					ConfigError_Status = RCC_enuNotOk;
				}
				else if((PLLP != PLLP_2) && (PLLP != PLLP_4) && (PLLP != PLLP_6) && (PLLP != PLLP_8))
				{
					ConfigError_Status = RCC_enuNotOk;
				}
				else if(PLLQ<2 || PLLQ>15)
				{
					ConfigError_Status = RCC_enuNotOk;
				}
				else if(PLL_src<PLL_HSIsrc || PLL_src>PLL_HSEsrc)
				{
					ConfigError_Status = RCC_enuNotOk;
				}
				else
				{
					/***************************** Configure PLLM ************************************/
				     Local_u32temp = RCC->RCC_PLLCFGR_REG;
				     Local_u32temp &= PLLM_CLEAR_MASK;
				     Local_u32temp |= (PLLM << PLL_M_SHIFT);
				     RCC->RCC_PLLCFGR_REG = Local_u32temp;


				    /***************************** Configure PLLN ************************************/
					 Local_u32temp = RCC->RCC_PLLCFGR_REG;
					 Local_u32temp &= PLLN_CLEAR_MASK;
					 Local_u32temp |= (PLLN << PLL_N_SHIFT);
					 RCC->RCC_PLLCFGR_REG = Local_u32temp;

					/***************************** Configure PLLP ************************************/
					 Local_u32temp = RCC->RCC_PLLCFGR_REG;
					 Local_u32temp &= PLLP_CLEAR_MASK;
					 Local_u32temp |= (PLLP << PLL_P_SHIFT);
					 RCC->RCC_PLLCFGR_REG = Local_u32temp;

					/***************************** Configure PLLQ ************************************/
					 Local_u32temp = RCC->RCC_PLLCFGR_REG;
					 Local_u32temp &= PLLQ_CLEAR_MASK;
					 Local_u32temp |= (PLLQ << PLL_Q_SHIFT);
					 RCC->RCC_PLLCFGR_REG = Local_u32temp;

					/***************************** Configure PLLSRC ************************************/
					 Local_u32temp = RCC->RCC_PLLCFGR_REG;
					 Local_u32temp &= PLLSRC_CLEAR_MASK;
					 Local_u32temp |= (PLL_src << PLL_SRC_SHIFT);
					 RCC->RCC_PLLCFGR_REG = Local_u32temp;
				}
			}
		}


		return ConfigError_Status;
 }

 RCC_enuErrorS_t rcc_controlAHBprescaller(u32  AHBprescaler)
 {
		RCC_enuErrorS_t Error_Status = RCC_enuOk;
		u32 Local_u32temp = RCC->RCC_CFGR_REG;

		if ((AHBprescaler != AHB_0_PRESCALLER) && (AHBprescaler != AHB_2_PRESCALLER)
			&& (AHBprescaler != AHB_4_PRESCALLER)
			&& (AHBprescaler != AHB_8_PRESCALLER)
			&& (AHBprescaler != AHB_16_PRESCALLER)
			&& (AHBprescaler != AHB_64_PRESCALLER)
			&& (AHBprescaler != AHB_128_PRESCALLER)
			&& (AHBprescaler != AHB_256_PRESCALLER)
			&& (AHBprescaler != AHB_512_PRESCALLER))
		{
			 Error_Status = RCC_enuNotOk;
		}
		else
		{
			Local_u32temp = RCC->RCC_CFGR_REG;
			Local_u32temp &= AHB_PRE_CLAER_MASK;
			Local_u32temp |= (AHBprescaler << AHB_SHIFT);
			RCC->RCC_CFGR_REG = Local_u32temp;
		}

		return Error_Status;
 }

 RCC_enuErrorS_t rcc_controlABP1prescaller(u32 ABP1prescaler)
 {
	RCC_enuErrorS_t Error_Status = RCC_enuOk;
	u32 Local_u32temp = RCC->RCC_CFGR_REG;

	if ((ABP1prescaler != ABP1_0_PRESCALLER)
			&& (ABP1prescaler != ABP1_2_PRESCALLER)
			&& (ABP1prescaler != ABP1_4_PRESCALLER)
			&& (ABP1prescaler != ABP1_8_PRESCALLER)
			&& (ABP1prescaler != ABP1_16_PRESCALLER))
	{
		 Error_Status = RCC_enuNotOk;
	}
	else
	{
		Local_u32temp = RCC->RCC_CFGR_REG;
		Local_u32temp &= ABP1_PRE_CLEAR_MASK;
		Local_u32temp |= (ABP1prescaler << ABP1_SHIFT);
		RCC->RCC_CFGR_REG = Local_u32temp;
	}

	return Error_Status;
 }

 RCC_enuErrorS_t rcc_controlABP2prescaller(u32 ABP2prescaler)
 {
	RCC_enuErrorS_t Error_Status = RCC_enuOk;
	u32 Local_u32temp = RCC->RCC_CFGR_REG;

	if ((ABP2prescaler != ABP2_0_PRESCALLER)
			&& (ABP2prescaler != ABP2_2_PRESCALLER)
			&& (ABP2prescaler != ABP2_4_PRESCALLER)
			&& (ABP2prescaler != ABP2_8_PRESCALLER)
			&& (ABP2prescaler != ABP2_16_PRESCALLER))
	{
		 Error_Status = RCC_enuNotOk;
	}
	else
	{
		Local_u32temp = RCC->RCC_CFGR_REG;
		Local_u32temp &= ABP2_PRE_CLEAR_MASK;
		Local_u32temp |= (ABP2prescaler << ABP2_SHIFT);
		RCC->RCC_CFGR_REG = Local_u32temp;
	}

	return Error_Status;
 }

 RCC_enuErrorS_t rcc_controlAHB1Prephiral(AHB1_PREI_t AHB1_PREI,
 		PREI_State_t PREI_State)
 {

	 RCC_enuErrorS_t Error_Status = RCC_enuOk;
	 u32 Local_u32temp = RCC->RCC_AHB1ENR_REG;

	 if(PREI_State<PREI_StateON || PREI_State>PREI_StateOFF)
	 {
		 Error_Status = RCC_enuNotOk;
	 }

	 switch(AHB1_PREI)
	 {
		 case AHB1_PREI_GPIOAen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIOAen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIOAen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_GPIOBen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIOBen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIOBen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_GPIOCen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIOCen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIOCen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_GPIODen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIODen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIODen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_GPIOEen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIOEen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIOEen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_GPIOHen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_GPIOHen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_GPIOHen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_CRCen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_CRCen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_CRCen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_DMA1en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_DMA1en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_DMA1en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case AHB1_PREI_DMA2en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB1_PREI_DMA2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB1_PREI_DMA2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 default : Error_Status = RCC_enuNotOk;      break;

	 }

	 return Error_Status;
 }

 RCC_enuErrorS_t rcc_controlAHB2Prephiral(AHB2_PREI_t AHB2_PREI,
 		PREI_State_t PREI_State)
 {
	 RCC_enuErrorS_t Error_Status = RCC_enuOk;
	 u32 Local_u32temp = RCC->RCC_AHB2ENR_REG;

	 if(PREI_State<PREI_StateON || PREI_State>PREI_StateOFF)
	 {
		 Error_Status = RCC_enuNotOk;
	 }

	 switch(AHB2_PREI)
	 {
	 	 case AHB2_PREI_OTGFSen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<AHB2_PREI_OTGFSen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<AHB2_PREI_OTGFSen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;


		 default : Error_Status = RCC_enuNotOk;      break;
	 }

	 return Error_Status;
 }

 RCC_enuErrorS_t rcc_controlABP1Prephiral(ABP1_PREI_t ABP1_PREI,
 		PREI_State_t PREI_State)
 {

	 RCC_enuErrorS_t Error_Status = RCC_enuOk;
	 u32 Local_u32temp = RCC->RCC_APB1ENR_REG;

	 if(PREI_State<PREI_StateON || PREI_State>PREI_StateOFF)
	 {
		 Error_Status = RCC_enuNotOk;
	 }

	 switch(ABP1_PREI)
	 {
		 case ABP1_PREI_TIM2en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_TIM2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_TIM2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_TIM3en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_TIM3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_TIM3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_TIM4en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_TIM4en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_TIM4en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_TIM5en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_TIM5en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_TIM5en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_WWDGen:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_WWDGen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_WWDGen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_SPI2en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_SPI2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_SPI2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_SPI3en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_SPI3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_SPI3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_USART2en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_USART2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_USART2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_I2C1en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_I2C1en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_I2C1en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_I2C2en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_I2C2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_I2C2en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_I2C3en:
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_I2C3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_I2C3en);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 case ABP1_PREI_PWRen :
			 if(PREI_State == PREI_StateON)
			 {
				 Local_u32temp |= (1<<ABP1_PREI_PWRen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 else
			 {
				 Local_u32temp &= ~(1<<ABP1_PREI_PWRen);
				 RCC->RCC_AHB1ENR_REG = Local_u32temp;
			 }
			 break;

		 default : Error_Status = RCC_enuNotOk;      break;

	 }

	 return Error_Status;

 }

 RCC_enuErrorS_t rcc_controlABP2Prephiral(ABP2_PREI_t ABP2_PREI,
 		PREI_State_t PREI_State)
 {
	 RCC_enuErrorS_t Error_Status = RCC_enuOk;
	 u32 Local_u32temp = RCC->RCC_APB2ENR_REG;

	 if(PREI_State<PREI_StateON || PREI_State>PREI_StateOFF)
	 {
		 Error_Status = RCC_enuNotOk;
	 }

	 switch(ABP2_PREI)
	 {
	 case  ABP2_PREI_TIM1en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_TIM1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_TIM1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_USART1en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_USART1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_USART1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_USART6en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_USART6en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_USART6en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_ADC1en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_ADC1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_ADC1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_SDIOen:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_SDIOen);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_SDIOen);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_SPI1en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_SPI1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_SPI1en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_SPI4en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_SPI4en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_SPI4en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_SYSCFGen:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_SYSCFGen);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_SYSCFGen);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_TIM9en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_TIM9en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_TIM9en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_TIM10en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_TIM10en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_TIM10en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 case  ABP2_PREI_TIM11en:
		 if(PREI_State == PREI_StateON)
		 {
			 Local_u32temp |= (1<<ABP2_PREI_TIM11en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 else
		 {
			 Local_u32temp &= ~(1<<ABP2_PREI_TIM11en);
			 RCC->RCC_AHB1ENR_REG = Local_u32temp;
		 }
		 break;

	 default:
		 Error_Status = RCC_enuNotOk;          break;
	 }

	 return Error_Status;
 }





