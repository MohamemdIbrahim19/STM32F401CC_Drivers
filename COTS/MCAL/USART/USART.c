/*
 * USART.c
 *
 *  Created on: Mar 28, 2023
 *      Author: Mohamed_ibrahim
 */
#include "STD_TYPES.h"
#include "USART.h"
#include "USART_private.h"
#include "USART_cfg.h"
#include "RCC.h"

#define USART_NUM                3
#define SYSCLK                   16000000UL

/*					CLEAR MASKS TO AVOID RMW				*/
#define SAMPLING_CLEAR           0X7FFF
#define USART_EN_CLEAR			 0XDFFF
#define DATA_FRAME_CLEAR         0XEFFF
#define PARITY_C_CLEAR           0XFBFF
#define PARITY_S_CLEAR           0XFDFF
#define PE_CLEAR                 0XFEFF
#define TXE_CLEAR				 0XFF7F
#define TXC_CLEAR				 0XFFBF
#define RXNE_CLEAR				 0XFFDF
#define TE_CLEAR				 0XFFF7
#define RE_CLEAR				 0XFFFB
#define STOP_CLEAR               0X4F6F

/*					USART Peripherals available  			*/
#define USART1                   ((USART_REG_t *) (0x40011000))
#define USART2                   ((USART_REG_t *) (0x40004400))
#define USART6                   ((USART_REG_t *) (0x40011400))

#define jj                  	 *((USART_REG_t *) (0x40011000))

/*					USART Registers 						*/
typedef struct
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}USART_REG_t;

/*					Array of pointers to registers 			*/
volatile USART_REG_t *  USART_ARR[USART_NUM] = {USART1,USART2,USART6};

/*	USART Data Buffer (Transmit) */
u8 *Buffer_ptr_TR[USART_NUM];
u8 Buffer_size_TR[USART_NUM] = {0};
u8 Buffer_idx_TR[USART_NUM] = {0};
USART_status_t USART_status_TR[USART_NUM] = {USART_Idle};

/*	USART Data Buffer (Receive) */
u8 *Buffer_ptr_RE[USART_NUM];
u8 Buffer_size_RE[USART_NUM] = {0};
u8 Buffer_idx_RE[USART_NUM] = {0};
USART_status_t USART_status_RE[USART_NUM] = {USART_Idle};


/*	Pointer to Transmition Done Function */
void (*TR_CALL_Back)(void);

/*	Pointer to Receive Done Function */
void (*RE_CALL_Back)(void);


USART_Errors_t USART_enuInit(USART_Num_t USART_Num)
{
	u32 Local_u32temp = 0;
	USART_Errors_t USART_Errors = USART_enuOk;

	switch(USART_Num)
	{
		case USART_1:
			rcc_controlABP2Prephiral(ABP2_PREI_USART1en,PREI_StateON);
			break;
		case USART_2:
			rcc_controlABP1Prephiral(ABP1_PREI_USART2en,PREI_StateON);
			break;
		case USART_6:
			rcc_controlABP2Prephiral(ABP2_PREI_USART6en,PREI_StateON);
			break;

		default: USART_Errors = USART_enuNotOk;  break;

	}

	Local_u32temp = USART_ARR[USART_Num]->USART_CR1;

	/*	Enable USART	*/
	Local_u32temp &= USART_EN_CLEAR;
	Local_u32temp |= USART_STATE;

	/* select Parity on/off	*/
	Local_u32temp &= PARITY_C_CLEAR;
	Local_u32temp |= USART_PARITY_STATE;

	Local_u32temp &= PARITY_S_CLEAR;
	Local_u32temp |= USART_PARITY_CONFG;

	/*	Set Receiver/Transmitter state */
	Local_u32temp &= RE_CLEAR;
	Local_u32temp |= USART_RECIEVER_STATE;

	Local_u32temp &= TE_CLEAR;
	Local_u32temp |= USART_TRANSMITTER_STATE;

	/*	Sampling 8/16 */
	Local_u32temp &= SAMPLING_CLEAR;
	Local_u32temp |= USART_SAMPLING;

	/*	Data Frame M bit*/
	Local_u32temp &= DATA_FRAME_CLEAR;
	Local_u32temp |= USART_DATA_FRAME;

	USART_ARR[USART_Num]->USART_CR1 = Local_u32temp;

	/*	select Stop bits */
	Local_u32temp = USART_ARR[USART_Num]->USART_CR2;
	Local_u32temp &= STOP_CLEAR;
	Local_u32temp |= USART_STOP_BITS;

	/*	Select Baud Rate */
	Local_u32temp =  USART_ARR[USART_Num]->USART_BRR;
	if(USART_SAMPLING == OVSAMPLING_16)
	{
		Local_u32temp = (SYSCLK)/(16*USART_BAUD_RATE);
	}
	else if(USART_SAMPLING == OVSAMPLING_8)
	{
		Local_u32temp = (SYSCLK)/(16*USART_BAUD_RATE);
	}

//	USART_ARR[USART_Num]->USART_BRR = 0xD03;
	USART_ARR[USART_Num]->USART_BRR = (Local_u32temp<<DIV_Mantissa);

	/*	Interrupts Control	*/
	Local_u32temp = USART_ARR[USART_Num]->USART_CR1;
	Local_u32temp &= PE_CLEAR & TXE_CLEAR & TXC_CLEAR & RXNE_CLEAR;
	Local_u32temp |= USART_PARITY_INT | USART_TXE_INT | USART_TC_INT | USART_RXE_INT;
	USART_ARR[USART_Num]->USART_CR1 |= Local_u32temp;

	if(USART_DMA_MODE == USART_DMA_RECIEVE)
	{
		USART_ARR[USART_Num]->USART_CR3 |= (1<<6);
	}
	else if(USART_DMA_MODE == USART_DMA_SEND)
	{
		USART_ARR[USART_Num]->USART_CR3 |= (1<<7);
	}
	NVIC_EnableIRQ(37);

	return USART_Errors;
}

Buffer_status_t USART_enuSendBuffer(USART_Num_t USART_Num,u8 *Local_buffer_in, u32 Local_u32size)
{
	Buffer_status_t Buffer_status = Buffer_enuNotOk;
	u32 Local_u32temp;
	if(Local_buffer_in == NULL)
	{
		 Buffer_status = Buffer_enuNotOk;
	}
	else if(USART_status_TR[USART_Num] == USART_Idle)
	{
		/*	Start buffering	*/
		USART_status_TR[USART_Num] = USART_Busy;
		Buffer_ptr_TR[USART_Num] = Local_buffer_in;
		Buffer_size_TR[USART_Num] = Local_u32size;
		Buffer_idx_TR[USART_Num] = 0;

		/*	Transmit first byte	*/
		trace_printf("%d",Buffer_ptr_TR[USART_Num][Buffer_idx_TR[USART_Num]]);
		USART_ARR[USART_Num]->USART_DR = Buffer_ptr_TR[USART_Num][Buffer_idx_TR[USART_Num]];
		Local_u32temp |= USART_PARITY_INT | USART_TXE_INT | USART_TC_INT | USART_RXE_INT;
		USART_ARR[USART_Num]->USART_CR1 |= Local_u32temp;

		Buffer_idx_TR[USART_Num]++;
		Buffer_status = Buffer_enuOk;
	}
	else
	{

	}
	return Buffer_status;
}
Buffer_status_t USART_enuRecieveBuffer(USART_Num_t USART_Num,u8 *Local_buffer_in, u32 Local_u32size)
{
	Buffer_status_t Buffer_status = Buffer_enuNotOk;
	u8 Local_u32temp = 0;
	if(Local_buffer_in == NULL)
	{
		 Buffer_status = Buffer_enuNotOk;
	}
	else if(USART_status_RE[USART_Num] == USART_Idle)
	{
		/*	Start buffering	*/
		USART_status_RE[USART_Num] = USART_Busy;
		Buffer_ptr_RE[USART_Num] = Local_buffer_in;
		Buffer_size_RE[USART_Num] = Local_u32size;
		Buffer_idx_RE[USART_Num] = 0;

		Local_u32temp |= USART_PARITY_INT | USART_TXE_INT | USART_TC_INT | USART_RXE_INT;
		USART_ARR[USART_Num]->USART_CR1 |= Local_u32temp;

		Buffer_status = Buffer_enuOk;
	}
	else
	{

	}

	return Buffer_status;
}


USART_Errors_t USART_enuRegisterCallBack_TXE(void (*Pfn)(void))
{
	USART_Errors_t USART_Errors = USART_enuOk;

	if(Pfn == NULL)
	{
		USART_Errors = USART_enuNotOk;
	}
	else
	{
		TR_CALL_Back = Pfn;
	}

	return USART_Errors;
}
USART_Errors_t USART_enuRegisterCallBack_RX(void (*Pfn)(void))
{
	USART_Errors_t USART_Errors = USART_enuOk;

	if(Pfn == NULL)
	{
		USART_Errors = USART_enuNotOk;
	}
	else
	{
		RE_CALL_Back = Pfn;
	}

	return USART_Errors;
}

USART1_IRQHandler(void)
{
	trace_printf("ISR\n");
	// Check Transmition register empty , without DMA , && (USART_status_TR[USART_1] == USART_Busy)
	if(((USART_ARR[USART_1]->USART_SR) & (1<<TXE)) )
	{
		trace_printf("1");

		if(Buffer_idx_TR[USART_1] < Buffer_size_TR[USART_1])
		{
			trace_printf("Byte %d Sent\n",Buffer_idx_TR[USART_1]-1);
			USART_ARR[USART_1]->USART_DR = Buffer_ptr_TR[USART_1][Buffer_idx_TR[USART_1]];
			Buffer_idx_TR[USART_1]++;
		}
		else
		{
			trace_printf("Byte %d Sent\n",Buffer_idx_TR[USART_1]-1);
			trace_printf("Transmit Complete , Calling Callback Function ...... \n");

			USART_status_TR[USART_1] = USART_Idle;

			USART_ARR[USART_1]->USART_CR1 &= TXE_CLEAR;
			TR_CALL_Back();
		}
	}

	 if(((USART_ARR[USART_1]->USART_SR) & (1<<RXNE)) &&
			(USART_status_RE[USART_1] = USART_Busy))
	{
		trace_printf("I recieved a byte  ");
		Buffer_ptr_RE[Buffer_idx_RE[USART_1]] = (u8*)USART_ARR[USART_1]->USART_DR;
		if(Buffer_ptr_RE[Buffer_idx_RE[USART_1]] == '1')
		{
			trace_printf("I recieved a byte = 1\n");
			//SetLedON();
		}
		else if(Buffer_ptr_RE[Buffer_idx_RE[USART_1]] == '0')
		{
			trace_printf("I recieved a byte = 0");
			//SetLedOFF();
		}
		Buffer_idx_RE[USART_1]++;

		if(Buffer_idx_RE[USART_1] == Buffer_size_RE[USART_1])
		{

			USART_status_RE[USART_1] = USART_Idle;
			RE_CALL_Back();
		}
	}
}








