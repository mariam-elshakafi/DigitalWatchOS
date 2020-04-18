/************************************************************************************/
/*  Author  :  Mira Mousa                                                           */
/*  Version :  01                                                                   */
/*  Date    :  15 Jan 2020                                                          */
/************************************************************************************/

#include "STD_Types.h"

#include "RCC.h"

/************************************************************************************/
/*  defining RCC registers using structure method                                   */
/************************************************************************************/
typedef struct
{
	u32 CR;        //RCC_CR
	u32 CFGR;      //RCC_CFGR
	u32 CIR;       //RCC_CIR
	u32 APB2RSTR;  //RCC_APB2RSTR
	u32 APB1RSTR;  //RCC_APB1RSTR
	u32 AHBENR;    //RCC_AHBRSTR
	u32 APB2ENR;   //RCC_APB2ENR
	u32 APB1ENR;   //RCC_APB1ENR
	u32 BDCR;      //RCC_BDCR
	u32 CSR;       //RCC_CSR
}RCC_Prepheral;

#define RCC ((RCC_Prepheral*)0x40021000)



/*  Description : This API configure Enable and Disable High Speed Clock Source          */
ERROR_S RCC_HSClockCtrl(u8 Copy_u8Clockname,u8 Copy_u8State ,u8 Copy_u8ClockRDY)
{
	ERROR_S state = ERROR_OK;
	/*	Enabling the clock source*/
	if(Copy_u8State)
	{
		/*	Set the clock on bit */
		RCC->CR |= Copy_u8Clockname;
		/*	Check the clock ready bit till rise
		 * to make sure the clock is enabled*/
		if(!(RCC->CR & Copy_u8ClockRDY))
    {
      state = ERROR_NOK;
    }
    
	}
	else
	{
		/*	Clear the clock on bit */
		RCC->CR &= ~Copy_u8Clockname;
		/*	Check the clock ready bit till clear
		 *to make sure the Clock is disabled	*/
		if(RCC->CR & Copy_u8ClockRDY)
		{
      state = ERROR_NOK;
    }
	}
	return state;
}


/*  Description : This API configure system clock source Switch               */
ERROR_S RCC_ClockSource(u8 Copy_u8Clockname,u8 Copy_u8SysClkState)
{
	ERROR_S state = ERROR_OK;
	/*Clear System clock switch bits*/
	RCC->CFGR &= CLK_CLR;
	/*Select System clock switch name*/
	RCC->CFGR |= Copy_u8Clockname;
	/*Check if the clock is selected*/
	if(!((RCC->CFGR & Copy_u8SysClkState) == Copy_u8SysClkState) )
	{
		state = ERROR_NOK;
	}
	return state;
}

/*  Description : This API configure PLL clock select                               */
ERROR_S RCC_PLLSRC(u8 Copy_u8Clockname,u8 Copy_u8MulOrDiv,u8 Copy_u8Operation)
{
  ERROR_S state = ERROR_OK;
	/*Check if it HSI or HSE*/
	if(HSI == Copy_u8Clockname)
	{
		/*Clear PLL CLK source bit to choose HSI*/
		RCC->CFGR &= PLLSRCHSI;
	}
	else
	{
		/*SET PLL CLK source bit to choose HSE*/
		RCC->CFGR |= PLLSRCHSE;
	}

	/*Check for operation to be done on the clock*/
	if((DIV == Copy_u8MulOrDiv))
	{
		/*Clear for no Division */
		RCC->CFGR &= PLL_HSEPRE;
		/*Applying factor mask*/
		RCC->CFGR |= Copy_u8Operation;
	}
	else
	{
		/*Clear for applying the mask */
		RCC->CFGR &= PLLMUL_CLR;
		/*Applying factor mask*/
		RCC->CFGR |= Copy_u8Operation;
	}
  return state;

}


/*  Description : This API configure Enabling nd Disabling Low Speed Clock Source        */
ERROR_S RCC_LSClockCtrl(u8 Copy_u8Clockname,u8 Copy_u8State ,u8 Copy_u8ClockRDY)
{
	ERROR_S state = ERROR_OK;
	if(LSEON == Copy_u8Clockname)
	{
		/*	Enabling the clock source*/
		if(Copy_u8State)
		{
			/*	Set the clock on bit */
			RCC->BDCR |= Copy_u8Clockname;
			/*	Check the clock ready bit till rise
			 * to make sure the clock is enabled*/
			if(!(RCC->BDCR & Copy_u8ClockRDY))
			{
        state = ERROR_NOK;
      }
		}
		else
		{
			/*	Clear the clock on bit */
			RCC->BDCR &= ~Copy_u8Clockname;
			/*	Check the clock ready bit till clear
			 *to make sure the Clock is disabled	*/
			if(RCC->BDCR & Copy_u8ClockRDY)
			{
        state = ERROR_NOK;
      }
		}
	}
	else
	{
		if(Copy_u8State)
		{
			/*	Set the clock on bit */
			RCC->CSR |= Copy_u8Clockname;
			/*	Check the clock ready bit till rise
			 * to make sure the clock is enabled*/
			if(!(RCC->CSR & Copy_u8ClockRDY))
			{
        state = ERROR_NOK;
      }
		}
		else
		{
			/*	Clear the clock on bit */
			RCC->CSR &= ~Copy_u8Clockname;
			/*	Check the clock ready bit till clear
			 *to make sure the Clock is disabled	*/
			if(RCC->CSR & Copy_u8ClockRDY)
			{
        state = ERROR_NOK;
      }
		}
	}
	return state;
}


/*  Description : This API Enable prepheral clock                                              */
extern ERROR_S RCC_PrephiralEnable(u8 Copy_u8Bus, u8 Copy_u8PreName)
{
  ERROR_S state = ERROR_OK;
  switch(Copy_u8Bus)
  {
    case AHB:
      RCC->AHBENR  |= Copy_u8PreName;
      break;
    case APB2:
      RCC->APB2ENR |= Copy_u8PreName;
      break;
    case APB1:
      RCC->APB1ENR |= Copy_u8PreName;
      break;
    default:
      state = ERROR_NOK;
      break;
  }
  return state;
}


/*  Description : This API disable prepheral clock                                              */
extern ERROR_S RCC_PrephiralDisable(u8 Copy_u8Bus, u8 Copy_u8PreName)
{
  ERROR_S state = ERROR_OK;
  switch(Copy_u8Bus)
  {
    case AHB:
      RCC->AHBENR  &= ~Copy_u8PreName;
      break;
    case APB2:
      RCC->APB2ENR &= ~Copy_u8PreName;
      break;
    case APB1:
      RCC->APB1ENR &= ~Copy_u8PreName;
      break;
    default:
      state = ERROR_NOK;
      break;
  }
  return state;
}
