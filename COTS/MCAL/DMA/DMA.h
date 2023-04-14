/*
 * DMA.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Mohamed_ibrahim
 */

#ifndef DMA_H_
#define DMA_H_

#include "STD_TYPES.h"

/*		DMA_SxCR CONFG	*/
#define DMA_ENABLE	 	    	0X1
#define DMA_DISABLE         	0X0

#define DMA_DMEI_ENABLE     	0X2
#define DMA_DMEI_DISABLE		0X0

#define DMA_TEI_ENABLE			0X4
#define DMA_TEI_DISABLE			0X0

#define DMA_HTI_ENABLE      	0X8
#define DMA_HTI_DISABLE     	0X0

#define DMA_TCI_ENABLE      	0X10
#define DMA_TCI_DISABLE     	0X0

#define DMA_PFCTRL          	0X0
#define PERIPHERAL_PFCTRL   	0X20

#define DMA_DIR_PER_MEM			0X0
#define DMA_DIR_MEM_PER			0X40
#define DMA_DIR_MEM_MEM			0X80

#define DMA_CIRC_ENABLE         0X100
#define DMA_CIRC_DISABLE		0X0

#define DMA_PINC_EN				0X200
#define DMA_PINC_DIS			0X0

#define DMA_MINC_EN				0X400
#define DMA_MINC_DIS			0X0

#define DMA_PSIZE_8				0X0
#define DMA_PSIZE_16			0X800
#define DMA_PSIZE_32			0X1000

#define DMA_MSIZE_8				0X0
#define DMA_MSIZE_16			0X2000
#define DMA_MSIZE_32			0X4000

#define DMA_PINCOS_EN			0X8000
#define DMA_PINCOS_DIS          0X0

#define DMA_PRIORITY_LOW		0X0
#define DMA_PRIORITY_MEDUIM		0X10000
#define DMA_PRIORITY_HIGH		0X20000
#define DMA_PRIORITY_VHIGH		0X30000

#define DMA_DBM_EN				0X40000
#define DMA_DBM_DIS				0X0

#define DMA_PBURST_SINGLE		0X0
#define DMA_PBURST_4			0X200000
#define DMA_PBURST_8			0X400000
#define DMA_PBURST_16			0X600000

#define DMA_MBURST_SINGLE		0X0
#define DMA_MBURST_4			0X800000
#define DMA_MBURST_8			0X1000000
#define DMA_MBURST_16			0X1800000

/*	DMA Channels	*/
#define DMA_CH_0				0X0
#define DMA_CH_1				0X2000000
#define DMA_CH_2				0X4000000
#define DMA_CH_3				0X6000000
#define DMA_CH_4				0X8000000
#define DMA_CH_5				0XA000000
#define DMA_CH_6				0XC000000
#define DMA_CH_7				0XE000000

/*		DMA_SxFCR CONFIG 	*/
#define DMA_FEI_ENABLE			0X80
#define DMA_FEI_DISABLE			0X0

#define DMA_DIRECTMODE_ENABLE	0X0
#define DMA_FIFOMODE_ENABLE		0X4

#define FIFO_THRESHOLD_1_4		0X0
#define FIFO_THRESHOLD_1_2		0X1
#define FIFO_THRESHOLD_3_4		0X2
#define FIFO_THRESHOLD_FULL		0X3

/*	DMA Streams	*/
typedef enum
{
	DMA_STREAM0 = 0,
	DMA_STREAM1,
	DMA_STREAM2,
	DMA_STREAM3,
	DMA_STREAM4,
	DMA_STREAM5,
	DMA_STREAM6,
	DMA_STREAM7
}DMA_STREAMS_t;

typedef enum
{
	DMA_1 = 0,
	DMA_2
}DMA_NUMS_t;

typedef enum
{
	DMA_enuOk = 0,
	DMA_enuNotOk
}DMA_ErrorS_t;

/*	DMA Configuration Struct  */
typedef struct
{
	DMA_STREAMS_t DMA_StreamNo;
	u32 DMA_ChannelNo;
	u32 DMA_Priority;

	u32 DMA_DataDirection;
	u32 DMA_Psize;
	u32 DMA_Msize;
	u32 DMA_FlowController;
	u32 DMA_PeripheralIncrement;
	u32 DMA_Pincos;
	u32 DMA_MemoryIncremet;

	u32 DMA_PBURST;
	u32 DMA_MBURST;

	u32 DMA_DirectMode;
	u32 DMA_DoubleBufferMode;
	u32 DMA_CircularMode;
	u32 DMA_FIFO_THRESHOLD;

	struct
	{
		u32 DMA_DirectModeINT;
		u32 DMA_TransferErrorINT;
		u32 DMA_HalfTransferINT;
		u32 DMA_TransferCompleteINT;
		u32 DMA_FIFO_ErrorINT;
	}DMA_INT;

}DMA_CFG_t;

typedef struct
{
	DMA_STREAMS_t DMA_StreamNo;
	u32 Peripherial_ADD;
	u32 Memory0_ADD;
	u32 Memory1_ADD;
	u16 Data_Num;
}DMA_Data_t;


/*		DMA APIs	*/
DMA_ErrorS_t DMA_enuInitCFG(DMA_NUMS_t DMA_No,DMA_CFG_t* DMA_CFG);
DMA_ErrorS_t DMA_enuInitData(DMA_NUMS_t DMA_No , DMA_Data_t *DMA_Data);
DMA_ErrorS_t DMA_enuStart(DMA_NUMS_t DMA_No , DMA_STREAMS_t DMA_StreamNo);
DMA_ErrorS_t DMA_enuRegisterCallBack(DMA_NUMS_t DMA_No , void (*Call_Back)(void));
DMA_ErrorS_t DMA_enuSop(DMA_NUMS_t DMA_No , DMA_STREAMS_t DMA_StreamNo);

#endif /* DMA_H_ */
