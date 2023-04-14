/*
 * DMA.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Mohamed_ibrahim
 */

#include "STD_TYPES.h"
#include "DMA.h"
#include "DMA_private.h"

#define DMA_STREAMS_NUM	 8

#define ENABLE_CLEAR     0XFFFFFFFE
#define DMEIE_CLEAR		 0XFFFFFFFD
#define TEIE_CLEAR		 0XFFFFFFFB
#define HTIE_CLEAR		 0XFFFFFFF7
#define TCIE_CLEAR		 0XFFFFFFEF
#define PFCTRL_CLEAR     0XFFFFFFDF
#define DIR_CLEAR		 0XFFFFFF3F
#define CIRC_CLEAR		 0XFFFFFEFF
#define PINC_CLEAR		 0XFFFFFDFF
#define MINC_CLEAR		 0XFFFFFBFF
#define PSIZE_CLEAR		 0XFFFFE7FF
#define MSIZE_CLEAR		 0XFFFF9FFF
#define PINCOS_CLEAR     0XFFFF7FFF
#define PRIORITY_CLEAR   0XFFFCFFFF
#define	DBM_CLEAR		 0XFFFBFFFF
#define PBURST_CLEAR	 0XFF9FFFFF
#define MBURST_CLEAR	 0XFE7FFFFF
#define CHSEL_CLEAR		 0XF1FFFFFF

#define FEIE_CLEAR		 0XFFFFFF7F
#define DMDIS_CLEAR		 0XFFFFFFFB
#define THRESHOLD_CLEAR  0XFFFFFFFC

/*	Memory-Structure */
typedef struct
{
	u32 LISR;
	u32 HISR;
	u32 LIFCR;
	u32 HIFCR;

	struct
	{
		u32 SxCR;
		u32 SxNDTR;
		u32 SxPAR;
		u32 SxM0AR;
		u32 SxM1AR;
		u32 SxFCR;
	}REGx[DMA_STREAMS_NUM];

}DMA_Memory_t;

typedef enum
{
	DMA_Configured = 0,
	DMA_NotConfigured
}DMA_CONF_GRD_t;

typedef enum
{
	DMA_DataConfigured = 0,
	DMA_DataNotConfigured
}DMA_DATA_GRD_t;

DMA_CONF_GRD_t DMA_CONF_GRD[2] = {DMA_NotConfigured};
DMA_DATA_GRD_t DMA_DATA_GRD[2] = {DMA_DataNotConfigured};

#define DMA1    ((volatile DMA_Memory_t*)(0X40026000))
#define DMA2    ((volatile DMA_Memory_t*)(0X40026400))


volatile DMA_Memory_t * DMA_MemoryArr[2] = {DMA1,DMA2};

void (*PTF[2])(void);

DMA_ErrorS_t DMA_enuInitCFG(DMA_NUMS_t DMA_No,DMA_CFG_t* DMA_CFG)
{
	DMA_ErrorS_t DMA_ErrorS = DMA_enuOk;
	u32 Local_temp = 0;
	u32 Local_temp2 = 0;

	if(DMA_CFG == NULL)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else if(DMA_No<DMA_1 || DMA_No>DMA_2)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else
	{
		// Select Channel
		Local_temp &= CHSEL_CLEAR;
		Local_temp |= DMA_CFG->DMA_ChannelNo;

		// Select Priority
		Local_temp &= PRIORITY_CLEAR;
		Local_temp |= DMA_CFG->DMA_Priority;

		// Select Data Direction
		Local_temp &= DIR_CLEAR;
		Local_temp |= DMA_CFG->DMA_DataDirection;

		// Select PSIZE
		Local_temp &= PSIZE_CLEAR;
		Local_temp |= DMA_CFG->DMA_Psize;

		// Select MSIZE
		Local_temp &= MSIZE_CLEAR;
		Local_temp |= DMA_CFG->DMA_Msize;

		// Select Flow-Control
		Local_temp &= PFCTRL_CLEAR;
		Local_temp |= DMA_CFG->DMA_FlowController;

		// Select Peripheral increment mode
		Local_temp &= PINC_CLEAR;
		Local_temp |= DMA_CFG->DMA_PeripheralIncrement;

		// Select Peripheral increment offset size
		Local_temp &= PINCOS_CLEAR;
		Local_temp |= DMA_CFG->DMA_Pincos;

		// Select memory increment mode
		Local_temp &= MINC_CLEAR;
		Local_temp |= DMA_CFG->DMA_MemoryIncremet;

		// Select Peripheral BURST
		Local_temp &= PBURST_CLEAR;
		Local_temp |= DMA_CFG->DMA_PBURST;

		// Select Memory MURST
		Local_temp &= MBURST_CLEAR;
		Local_temp |= DMA_CFG->DMA_MBURST;

		// Select Direct mode
		Local_temp2 &= DMDIS_CLEAR;
		Local_temp2 |= DMA_CFG->DMA_DirectMode;

		// Select double buffer mode
		Local_temp &= DBM_CLEAR;
		Local_temp |= DMA_CFG->DMA_DoubleBufferMode;

		// Select Circular mode
		Local_temp &= CIRC_CLEAR;
		Local_temp |= DMA_CFG->DMA_CircularMode;

		// Select FIFI threshold Value
		Local_temp2 &= THRESHOLD_CLEAR;
		Local_temp2 |= DMA_CFG->DMA_FIFO_THRESHOLD;

		// Select interrupts

		Local_temp &= DMEIE_CLEAR & TEIE_CLEAR & HTIE_CLEAR & TCIE_CLEAR;
		Local_temp2 &= FEIE_CLEAR;

		Local_temp |= DMA_CFG->DMA_INT.DMA_DirectModeINT | DMA_CFG->DMA_INT.DMA_HalfTransferINT
				| DMA_CFG->DMA_INT.DMA_TransferCompleteINT | DMA_CFG->DMA_INT.DMA_TransferErrorINT;

		Local_temp2 |= DMA_CFG->DMA_INT.DMA_FIFO_ErrorINT;

		// Set Configuration
		DMA_MemoryArr[DMA_No]->REGx[DMA_CFG->DMA_StreamNo].SxCR |= Local_temp;
		DMA_MemoryArr[DMA_No]->REGx[DMA_CFG->DMA_StreamNo].SxFCR |= Local_temp2;

		// Update DMA Configuration State
		DMA_CONF_GRD[DMA_No] = DMA_Configured;
	}
	return DMA_ErrorS;
}

DMA_ErrorS_t DMA_enuInitData(DMA_NUMS_t DMA_No , DMA_Data_t *DMA_Data)
{
	DMA_ErrorS_t DMA_ErrorS = DMA_enuOk;

	if(DMA_Data == NULL)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else if(DMA_No<DMA_1 || DMA_No>DMA_2)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else
	{
		//Set Peripheral Address register
		DMA_MemoryArr[DMA_No]->REGx[DMA_Data->DMA_StreamNo].SxPAR = DMA_Data->Peripherial_ADD;

		//Set mem0 Address register
		DMA_MemoryArr[DMA_No]->REGx[DMA_Data->DMA_StreamNo].SxM0AR = DMA_Data->Memory0_ADD;

		// Set mem1 Address register if DBM on , else it will be masked by HW
		DMA_MemoryArr[DMA_No]->REGx[DMA_Data->DMA_StreamNo].SxM1AR = DMA_Data->Memory1_ADD;

		// Set Number of DMA transactions
		DMA_MemoryArr[DMA_No]->REGx[DMA_Data->DMA_StreamNo].SxNDTR = DMA_Data->Data_Num;

		// Update DMA Data Configuration State
		DMA_DATA_GRD[DMA_No] = DMA_DataConfigured;
	}

	return DMA_ErrorS;
}

DMA_ErrorS_t DMA_enuStart(DMA_NUMS_t DMA_No , DMA_STREAMS_t DMA_StreamNo)
{
	DMA_ErrorS_t DMA_ErrorS = DMA_enuOk;

	if(DMA_No<DMA_1 || DMA_No>DMA_2)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else if(DMA_CONF_GRD[DMA_No] != DMA_Configured ||
			DMA_DATA_GRD[DMA_No] != DMA_DataConfigured)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else
	{
		u32 Local_temp = 0;
		Local_temp &= ENABLE_CLEAR;
		Local_temp |= DMA_ENABLE;
		DMA_MemoryArr[DMA_No]->REGx[DMA_StreamNo].SxCR |= Local_temp;
	}

	return DMA_ErrorS;
}

DMA_ErrorS_t DMA_enuRegisterCallBack(DMA_NUMS_t DMA_No , void (*Call_Back)(void))
{
	DMA_ErrorS_t DMA_ErrorS = DMA_enuOk;

	if(DMA_No<DMA_1 || DMA_No>DMA_2)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else if(Call_Back == NULL)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else
	{
		PTF[DMA_No] = Call_Back;
	}

	return DMA_ErrorS;
}

DMA_ErrorS_t DMA_enuSop(DMA_NUMS_t DMA_No , DMA_STREAMS_t DMA_StreamNo)
{
	DMA_ErrorS_t DMA_ErrorS = DMA_enuOk;

	if(DMA_No<DMA_1 || DMA_No>DMA_2)
	{
		DMA_ErrorS = DMA_enuNotOk;
	}
	else
	{
		while(DMA_MemoryArr[DMA_No]->REGx[DMA_StreamNo].SxCR & ENABLE_CLEAR == 0);
	}

	return DMA_ErrorS;
}

DMA2_Stream7_IRQHandler(void)
{

}

DMA2_Stream5_IRQHandler(void)
{

}
