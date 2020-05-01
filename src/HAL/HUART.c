/*************************************************/
/*************************************************/
/*Author   : Ali Samir 							 */
/*Component: Handler_UART						 */					 
/*Layer    : ECUCAL								 */
/*************************************************/	
/*************************************************/	

#include "Std_Types.h"
#include "RCC.h"
#include "GPIO.h"
#include "UART.h"

#include "HUART.h"
#include "HUART_CFG.h"


uint32_t  clock = 8000000;
uint8_t Huart_Initialization(void)
{
	uint8_t Error_state=OK;
	uint32_t BaudRateDIV_Mantissa;
	uint32_t BaudRateDIV_Fraction;
	/**RCC Configuration**/
	RCC_PrephiralEnable(APB2, IOPA_EN);
	RCC_PrephiralEnable(APB2, USART1_EN);
	/**Gpio Configuraion**/
	GPIO_initStruct gpioUART_Tx;
	gpioUART_Tx.mode = GPIO_OUTPUT_AF_PP;
	gpioUART_Tx.speed = GPIO_OUTPUT_2MHZ;
	gpioUART_Tx.port = GPIO_PORTA;
	gpioUART_Tx.pin = GPIO_PIN_9;

	GPIO_initStruct gpioUART_Rx;
	gpioUART_Rx.mode = GPIO_INPUT_PULL_UP;
	gpioUART_Rx.speed = GPIO_INPUT;
	gpioUART_Rx.port = GPIO_PORTA;
	gpioUART_Rx.pin = GPIO_PIN_10;


	GPIO_init(&gpioUART_Tx);
	GPIO_init(&gpioUART_Rx);

	/**UART Defualt Configuraion**/
	//Error_state|=RCC_GetBusClock(APB2_BUS,&clock);
	BaudRateDIV_Mantissa = ( (clock) / (16*BAUD_RATE) );
	BaudRateDIV_Fraction = (( ( (clock) % (16*BAUD_RATE) ) *16 ) / (16*BAUD_RATE));
	Error_state|=UART_Initialization(BaudRateDIV_Mantissa,BaudRateDIV_Fraction,PARITY_BIT,DATA_BITS,STOP_BITS);
	return Error_state;
}
/*************************************************************************************************************************/

uint8_t Huart_Send(uint8_t *Buffer, uint16_t Length)
{
	uint8_t Error_state=OK;
	Error_state= UART_Send(Buffer,Length);
	return Error_state;

}
/*************************************************************************************************************************/
uint8_t Huart_Receive(uint8_t *Buffer, uint16_t Length)
{
	
	uint8_t Error_state=OK;
	Error_state= UART_Receive(Buffer,Length);
	return Error_state;

}
/*************************************************************************************************************************/
uint8_t Huart_Config(uint32_t BaudRate,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits)
{
	uint8_t Error_state=OK;
	uint32_t BaudRateDIV_Mantissa;
	uint32_t BaudRateDIV_Fraction;
if((ParityBits==PARITY_DISABLED || ParityBits==PARITY_EVEN || ParityBits==PARITY_ODD) && (DataSize==DATA_8_BITS || DataSize==DATA_9_BITS) && (StopBits==ONE_STOP_BIT || StopBits==TWO_STOP_BIT))
{
	BaudRateDIV_Mantissa = ( (clock) / (16*BAUD_RATE) );
	BaudRateDIV_Fraction = (( ( (clock) % (16*BAUD_RATE) ) *16 ) / (16*BAUD_RATE));
	Error_state=UART_Config(BaudRateDIV_Mantissa,BaudRateDIV_Fraction,ParityBits,DataSize,StopBits);
}
else
{
	Error_state=NOK;
}
return 	Error_state;
}

/*************************************************************************************************************************/

uint8_t Huart_SetTxCbf(TxCbf_t TxCbf)
{
	uint8_t Error_state=OK;
	if(TxCbf)
	{
		Error_state=UART_SetTxCallbf(TxCbf);
	}
	else
	{
		Error_state=NOK;
	}
	return Error_state;
}
/*************************************************************************************************************************/
uint8_t Huart_SetRxCbf(RxCbf_t RxCbf)
{
	uint8_t Error_state=OK;
	if(RxCbf)
	{
		Error_state = UART_SetRxCallbf(RxCbf);
	}
	else
	{
		Error_state=NOK;
	}
	return Error_state;
}














