/*
 * USART.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Mohamed_ibrahim
 */

#ifndef USART_H_
#define USART_H_

/*				USART_CR1 			 	*/

#define OVSAMPLING_8                    0X8000
#define OVSAMPLING_16                   0X0

#define USART_ENABLE					0X2000
#define USART_DISABLE					0X0

#define USART_8_BIT						0X0
#define USART_9_BIT						0X1000

#define USART_PARITY_EN					0X400
#define USART_PARITY_DIS                0X0

#define USART_EVEN_PARITY               0X0
#define USART_ODD_PARITY                0X200

#define PEIE_ENABLE						0X100
#define PEIE_DISABLE 					0X0

#define TXEIE_ENABLE					0X80
#define TXEIE_DISABLE					0X0

#define TCIE_ENABLE						0X40
#define TCIE_DISABLE					0X0

#define RXNEIE_ENABLE					0X20
#define RXNEIE_DISABLE					0X0

#define TE_ENABLE						0X8
#define TE_DISABLE						0X0

#define RE_ENABLE						0X4
#define RE_DISABLE						0X0

/*				USART_CR2 			 	*/

#define USART_1_STOP_BIT				0X0
#define USART_2_STOP_BITS				0X2000

/*				USART DMA MODE			*/
#define USART_DMA_OFF					0
#define USART_DMA_SEND					1
#define USART_DMA_RECIEVE				2



typedef enum
{
	USART_enuOk=0,
	USART_enuNotOk
}USART_Errors_t;

typedef enum
{
	USART_1 = 0,
	USART_2,
	USART_6
}USART_Num_t;

typedef enum
{
	Buffer_enuOk=0,
	Buffer_enuNotOk
}Buffer_status_t;

typedef enum
{
	USART_Idle = 0,
	USART_Busy
}USART_status_t;

USART_Errors_t USART_enuInit(USART_Num_t USART_Num);
Buffer_status_t USART_enuSendBuffer(USART_Num_t USART_Num,u8 *buffer_in, u32 buffer_size);
Buffer_status_t USART_enuRecieveBuffer(USART_Num_t USART_Num,u8 *buffer_in, u32 buffer_size);

USART_Errors_t USART_enuRegisterCallBack_TXE(void (*Pfn)(void));
USART_Errors_t USART_enuRegisterCallBack_RX(void (*Pfn)(void));
#endif /* USART_H_ */
