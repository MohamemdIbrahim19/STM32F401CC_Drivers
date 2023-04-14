/*
 * USART_cfg.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Mohamed_ibrahim
 */

#ifndef USART_CFG_H_
#define USART_CFG_H_

/*					USART_MODES STATE CONTROL					*/
#define USART_STATE                            USART_ENABLE
#define USART_PARITY_STATE			           USART_PARITY_DIS
#define USART_RECIEVER_STATE                   RE_ENABLE
#define USART_TRANSMITTER_STATE                TE_ENABLE

/*					USART INTERRUPTS CONTROL					*/
#define USART_PARITY_INT				       PEIE_DISABLE
#define USART_TXE_INT					       TXEIE_DISABLE
#define USART_TC_INT					       TCIE_DISABLE
#define USART_RXE_INT					       RXNEIE_DISABLE

/*					USART DATA FRAME CONTROL					*/
#define USART_DATA_FRAME				       USART_8_BIT
#define USART_STOP_BITS                        USART_1_STOP_BIT
#define USART_PARITY_CONFG				       USART_EVEN_PARITY

/*					USART BAUD RATE CONTROL						*/
#define USART_SAMPLING					       OVSAMPLING_8
#define USART_BAUD_RATE                        (9600)

#define USART_DMA_MODE							USART_DMA_SEND

#endif /* USART_CFG_H_ */
