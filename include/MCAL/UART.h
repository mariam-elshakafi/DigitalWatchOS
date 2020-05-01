/*************************************************/
/*************************************************/
/*Author   : Ali Samir 							 */
/*Component: UART								 */
/*Layer    : MCAL								 */
/*************************************************/	
/*************************************************/

#ifndef _UART_H
#define _UART_H

/**Standard Types defination**/
typedef unsigned char 	uint8_t;
typedef unsigned short 	int uint16_t;
typedef unsigned long 	int uint32_t;
typedef signed 	 char 	int8_t;
typedef signed   short 	int int16_t;
typedef signed   short 	int int32_t;

/**Macros for Error return type**/
#define 	OK 		0
#define 	NOK  	1
#define 	BUSY 	2

typedef void(*TxCbf_t)(void);
typedef void(*RxCbf_t)(void);

/**UART Functions**/

uint8_t UART_Initialization(uint32_t BaudRateDIV_Mantissa, uint32_t BaudRateDIV_Fraction,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits);

uint8_t UART_Send(uint8_t *Buffer, uint16_t Length);

uint8_t UART_Receive(uint8_t *Buffer, uint16_t Length);

uint8_t UART_Config(uint32_t BaudRateDIV_Mantissa, uint32_t BaudRateDIV_Fraction,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits);

uint8_t UART_SetTxCallbf(TxCbf_t TxCbf);

uint8_t UART_SetRxCallbf(RxCbf_t RxCbf);

void DMA_ChannelFour_Finish(void);

void DMA_ChannelFive_Finish(void);

#endif