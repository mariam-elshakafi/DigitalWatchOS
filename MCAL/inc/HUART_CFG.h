/*************************************************/
/*************************************************/
/*Author   : Ali Samir 							 */
/*Component: Handler_UART_Configuration			 */					 
/*Layer    : ECUCAL								 */
/*************************************************/	
/*************************************************/	

#ifndef HUART_CONFIG_H_
#define HUART_CONFIG_H_

/**Parity options you can select one option
*PARITY_DISABLED
*PARITY_EVEN	
*PARITY_ODD		
**/
#define  PARITY_BIT			 PARITY_DISABLED

/**StopBits  you can use one stopBit or two StopBits **/
#define STOP_BITS			ONE_STOP_BIT

/**Data options you Can send or receive 8 or 9 Bits */

#define DATA_BITS			DATA_8_BITS

/**Baud Rate**/
#define  BAUD_RATE			BAUD_RATE_9600
/*Mode options*/
#define SEND_MODE				SEND_MODE_DMA
#define RECEIVE_MODE			RECEIVE_MODE_DMA
#define MODE					DMA_MODE

#endif