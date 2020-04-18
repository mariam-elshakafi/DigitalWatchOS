/*************************************************/
/*************************************************/
/*Author   : Ali Samir 							 */
/*Component: UART								 */
/*Layer    : MCAL								 */
/*************************************************/	
/*************************************************/

#include "NVIC.h"
#include "DMA.h"
#include "UART.h"
#include "UART_CFG.h"

/**Macros of States of the buffer **/
 
#define 	IDLE_STATE	0
#define 	BUSY_STATE	1

/**Driver Masks**/
#define DEFAULT_MASK					0x0000200C
#define USART_TC_FLAG					0x00000040
#define TCEIE_ENABLE					0x00000040
#define TXEIE_ENABLE					0x00000080
#define RXNEIE_ENABLE					0x00000020
	
#define TC_FLAG							0x00000040
#define TXE_FLAG						0x00000080
#define RXNE_FLAG						0x00000020

#define DATA_SIZE_CLEAR_MASK			0xFFFFEFFF
#define PARITY_BIT_CLEAR_MASK			0xFFFF3FFF
#define STOP_BITS_CLEAR_MASK			0xFFFFCFFF

/*DMA enable transmitter*/
#define UART_DMAT_SET       0x00000080
/*DMA enable receiver*/
#define UART_DMAR_SET       0x00000040

/**UART Registers**/

typedef struct
{
	uint32_t	SR;
	uint32_t	DR;
	uint32_t	BRR;
	uint32_t	CR1;
	uint32_t	CR2;
	uint32_t	CR3;
	uint32_t	GTPR;
}UART_t;

/**Macros of Base address**/
#define UART ((UART_t*)0x40013800)

/**Data Parameters**/
typedef struct
{
	uint8_t * Data;
	uint32_t Position;
	uint32_t Size;
	uint8_t BufferState;
}DataBuffer_t;


/**Define of Transmit and Recive object from Data struct**/

static DataBuffer_t  Transmit_Buffer;
static DataBuffer_t  Recieve_Buffer;


/**Notificatios CallBack for Transmit and Recive**/

static TxCbf_t Transmit_Notify;
static RxCbf_t Recieve_Notify;


/*************************************************************************************************************************/

uint8_t UART_Initialization(uint32_t BaudRateDIV_Mantissa, uint32_t BaudRateDIV_Fraction,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits)

{
	uint8_t Error_state=OK;
#ifndef UART_USE_DMA
	UART->BRR=BaudRateDIV_Fraction | (BaudRateDIV_Mantissa<<4);
	UART->CR1 = DEFAULT_MASK | DataSize | ParityBits | RXNEIE_ENABLE | TCEIE_ENABLE;
	UART->CR2 = StopBits;
	Local_Error|=NVIC_Clear_Pending(USART1);
	Local_Error|=NVIC_EnableIRQ(USART1);

#else
	UART->BRR=BaudRateDIV_Fraction | (BaudRateDIV_Mantissa<<4);
	UART->CR1 = DEFAULT_MASK | DataSize | ParityBits | TCEIE_ENABLE;
	UART->CR2 = StopBits;
	NVIC_EnableInterrupt(NVIC_IRQNUM_USART1);
	NVIC_EnableInterrupt(NVIC_IRQNUM_DMA1_CHANNEL5);
	/* Tx Configurations */
	dmaPrephCfg_t cfg = 
	{
		.channel = DMA_CH_4,
		.interrupt = DMA_INT_NO_INT,
		.direction = DMA_READ_FROM_MEM,
		.circular = DMA_CIRCULAR_MODE_OFF,
		.prephInc = DMA_PREPH_INC_OFF,
		.memInc = DMA_MEM_INC_ON,
		.prephSize = DMA_PREPH_8_BIT,
		.memSize = DMA_MEM_8_BIT,
		.priority = DMA_PRIORITY_HIGH
	};
	DMA_ConfigurePrephChannel(&cfg);
	cfg.channel = DMA_CH_5;
	cfg.interrupt = DMA_INT_TRANSFER_COMPLETE;
	cfg.direction = DMA_READ_FROM_PREPH;
	DMA_ConfigurePrephChannel(&cfg);
	DMA_SetCallBack(DMA_CH_5, USART1_IRQHandler);
	UART->CR3 |= UART_DMAT_SET | UART_DMAR_SET;
	Recieve_Buffer.BufferState=IDLE_STATE;
	Transmit_Buffer.BufferState=IDLE_STATE;

#endif
	return Error_state;

}

/*************************************************************************************************************************/

uint8_t UART_Send(uint8_t *Buffer, uint16_t Length)
{
	uint8_t Error_state=OK;
#ifndef UART_USE_DMA
	if(Buffer && Length>0)
	{
		if(Transmit_Buffer.BufferState==IDLE_STATE)
		{
			Transmit_Buffer.Data=Buffer;
			Transmit_Buffer.Size=Length;
			Transmit_Buffer.Position=0;
			Transmit_Buffer.BufferState=BUSY_STATE;
			UART->DR = Transmit_Buffer.Data[Transmit_Buffer.Position];
			Transmit_Buffer.Position++;
		}
		else
		{
			Error_state=BUSY;
		}
	}
	else
	{
		Error_state=NOK;
	}
#else
	Transmit_Buffer.BufferState=BUSY_STATE;
	DMA_TransferPrephData(DMA_CH_4,(uint32_t)(&(UART->DR)), (uint32_t)Buffer, Length);
#endif
	return Error_state;
}

/*************************************************************************************************************************/

uint8_t UART_Receive(uint8_t *Buffer, uint16_t Length)
{
	uint8_t Error_state=OK;
#ifndef UART_USE_DMA
	if(Buffer && Length>0)
	{
		if(Recieve_Buffer.BufferState==IDLE_STATE)
		{
			Recieve_Buffer.Size=Length;
			Recieve_Buffer.Position=0;
			Recieve_Buffer.Data=Buffer;
			Recieve_Buffer.BufferState=BUSY_STATE;
		}
		else
		{
			Error_state=BUSY;
		}
	}
	else
	{
		Error_state= NOT_OK;
	}
#else
	Recieve_Buffer.BufferState=BUSY_STATE;
	DMA_TransferPrephData(DMA_CH_5,(uint32_t)(&(UART->DR)), (uint32_t)Buffer, Length);

#endif
	return Error_state;
}

/*************************************************************************************************************************/

uint8_t UART_Config(uint32_t BaudRateDIV_Mantissa, uint32_t BaudRateDIV_Fraction,uint32_t ParityBits,uint32_t DataSize,uint32_t StopBits)

{
		uint8_t Error_state=OK;
		UART->CR1 &= DATA_SIZE_CLEAR_MASK;
		UART->CR1 |=DataSize;
		UART->CR1 &= PARITY_BIT_CLEAR_MASK;
		UART->CR1 |= ParityBits;		
		UART->CR2 &= STOP_BITS_CLEAR_MASK;
		UART->CR2 |= StopBits;
		UART->BRR=BaudRateDIV_Fraction | (BaudRateDIV_Mantissa<<4);
		return Error_state;
}
/*************************************************************************************************************************/


uint8_t UART_SetTxCallbf(TxCbf_t TxCbf)
{
	uint8_t Error_state=OK;
	Transmit_Notify=TxCbf;
	return Error_state;

}
/*************************************************************************************************************************/

uint8_t UART_SetRxCallbf(RxCbf_t RxCbf)
{
	uint8_t Error_state=OK;
	Recieve_Notify=RxCbf;
	return Error_state;
}
/*************************************************************************************************************************/

void USART1_IRQHandler(void)
{
#ifndef UART_USE_DMA
		uint32_t local_var;
		if(UART->SR & TC_FLAG)
		{	
			UART->SR&=~TC_FLAG;
	if(Transmit_Buffer.BufferState==BUSY_STATE)
	{
			if(Transmit_Buffer.Position != Transmit_Buffer.Size)
			{
				UART->DR = Transmit_Buffer.Data[Transmit_Buffer.Position];
				Transmit_Buffer.Position++;
			}
			else
			{
				Transmit_Buffer.Position=0;
				Transmit_Buffer.Size=0;
				Transmit_Buffer.Data=NULL;
				Transmit_Buffer.BufferState=IDLE_STATE;
			
				if(TxNotify)
				    {TxNotify();}
				else
					{asm("NOP");}
				
			}
	}
		else
		{
			asm("NOP");
		}

	}
	else
	{
		local_var=UART->DR;
		asm("NOP");
	}
		
/**********************************************************/
		if(UART->SR & RXNE_FLAG)
	{
		UART->SR &= ~USART_RXNE_FLAG;
		if(Recieve_Buffer.BufferState==STATE_BUSY)
		{
			if(Recieve_Buffer.Position != Recieve_Buffer.Size)
			{
				
				Recieve_Buffer.Data[Recieve_Buffer.Position]=UART->DR;
				Recieve_Buffer.Position++;
			}
			else
			{
				Recieve_Buffer.Data=NULL;
				Recieve_Buffer.Position=0;
				Recieve_Buffer.Size=0;
				Recieve_Buffer.BufferState=IDLE_STATE;
				UART->CR1 &= ~USART_RXNEIE_ENABLE;
				if(RxNotify)
				{RxNotify();}
				else
			 	{asm("NOP");}
			}
		}
		else
		{
			asm("NOP");
		}

	}
	else
	{
		asm("NOP");
	}
#else
	if(UART->SR&USART_TC_FLAG)
	{
		UART->SR &= ~(USART_TC_FLAG);
		Transmit_Buffer.BufferState=IDLE_STATE;
		if(Transmit_Notify)
		{
			Transmit_Notify();
		}
	}
	else
	{
		Recieve_Buffer.BufferState=IDLE_STATE;
		if(Recieve_Notify)
		{
			Recieve_Notify();
		}
	}

#endif
}