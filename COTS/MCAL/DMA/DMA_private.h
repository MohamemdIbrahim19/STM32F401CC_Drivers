/*
 * DMA_private.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Mohamed
 */

#ifndef DMA_PRIVATE_H_
#define DMA_PRIVATE_H_
/************************************************************************************/
/*****************************		DMA_LISR/DMA_HISR	*****************************/
/************************************************************************************/

/*	FIFO Error Interrupt Flags	*/
#define FEIF_0		0
#define FEIF_1		6
#define FEIF_2		16
#define FEIF_3		22
#define FEIF_4		0
#define FEIF_5		6
#define FEIF_6		16
#define FEIF_7		22

/*	Direct mode Error Interrupt Flags	*/
#define DMEIF_0		2
#define DMEIF_1		8
#define DMEIF_2		18
#define DMEIF_3		24
#define DMEIF_4		2
#define DMEIF_5		8
#define DMEIF_6		18
#define DMEIF_7		24

/*	Stream transfer Error Interrupt Flags	*/
#define TEIF_0		3
#define TEIF_1		9
#define TEIF_2		19
#define TEIF_3		25
#define TEIF_4		3
#define TEIF_5		9
#define TEIF_6		19
#define TEIF_7		25

/*	Stream Half-transfer Interrupt Flags		*/
#define HTIF_0		4
#define HTIF_1		10
#define HTIF_2		20
#define HTIF_3		26
#define HTIF_4		4
#define HTIF_5		10
#define HTIF_6		20
#define HTIF_7		26

/*	Stream Transfer-Complete interrupt Flags	*/
#define TCIF_0		5
#define TCIF_1		11
#define TCIF_2		21
#define TCIF_3		27
#define TCIF_4		5
#define TCIF_5		11
#define TCIF_6		21
#define TCIF_7		27

/************************************************************************************/
/*****************************  DMA_LIFCR/DMA_HIFCR  	*****************************/
/************************************************************************************/

/*	Stream Clear FIFO Interrupt Flags	*/
#define CFEIF_0		0
#define CFEIF_1		6
#define CFEIF_2		16
#define CFEIF_3		22
#define CFEIF_4		0
#define CFEIF_5		6
#define CFEIF_6		16
#define CFEIF_7		22

/*	Direct mode Clear Interrupt Flags	*/
#define CDMEIF_0	2
#define CDMEIF_1	8
#define CDMEIF_2	18
#define CDMEIF_3	24
#define CDMEIF_4	2
#define CDMEIF_5	8
#define CDMEIF_6	18
#define CDMEIF_7	24


/*	Stream transfer Clear Error Interrupt Flags		*/
#define CTEIF_0		3
#define CTEIF_1		9
#define CTEIF_2		19
#define CTEIF_3		25
#define CTEIF_4		3
#define CTEIF_5		9
#define CTEIF_6		19
#define CTEIF_7		25


/*	Stream Half-transfer Clear Interrupt Flags		*/
#define CHTIF_0		4
#define CHTIF_1		10
#define CHTIF_2		20
#define CHTIF_3		26
#define CHTIF_4		4
#define CHTIF_5		10
#define CHTIF_6		20
#define CHTIF_7		26

/*	Stream Transfer-Complete Clear interrupt Flags	*/
#define CTCIF_0		5
#define CTCIF_1		11
#define CTCIF_2		21
#define CTCIF_3		27
#define CTCIF_4		5
#define CTCIF_5		11
#define CTCIF_6		21
#define CTCIF_7		27

#define NULL 		((void*)0)



#endif /* DMA_PRIVATE_H_ */
