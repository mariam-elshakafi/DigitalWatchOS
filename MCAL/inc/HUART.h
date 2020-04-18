/*************************************************/
/*************************************************/
/*Author   : Ali Samir 							 */
/*Component: Handler_UART						 */					 
/*Layer    : ECUCAL								 */
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

/**Parity options**/
#define  PARITY_DISABLED		0x00000000
#define  PARITY_EVEN			0x00000400
#define  PARITY_ODD			    0x00000600

/**StopBits  you can use one stopBit or two StopBits **/

#define ONE_STOP_BIT		0x00000000
#define TWO_STOP_BIT		0x00002000

/**Data options you Can send or receive 8 or 9 Bits */

#define DATA_8_BITS			0x00000000
#define DATA_9_BITS			0x00001000

/**Baud Rate**/
#define  BAUD_RATE_9600		9600

/**Macros for Error return type**/
#define 	OK 		0
#define 	NOK  	1
#define 	BUSY 	2


typedef void(*TxCbf_t)(void);
typedef void(*RxCbf_t)(void);


/**UART Handler Functions**/

uint8_t Huart_Initialization(void)
uint8_t Huart_Send(uint8_t *Buffer, uint16_t Length);
uint8_t Huart_Receive(uint8_t *Buffer, uint16_t Length);
uint8_t Huart_Config(uint32_t BaudRate,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits);
uint8_t Huart_SetTxCbf(TxCbf_t TxCbf);
uint8_t Huart_SetRxCbf(RxCbf_t RxCbf);

#endif