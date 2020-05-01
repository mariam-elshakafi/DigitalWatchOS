/************************************************************************************/
/*  Author  :  Mira Mousa                                                           */
/*  Version :  01                                                                   */
/*  Date    :  15 Jan 2020                                                          */
/************************************************************************************/

#include "Std_Types.h"
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
Std_ReturnType RCC_HSClockCtrl(u32 Copy_u8Clockname,u32 Copy_u8State ,u32 Copy_u8ClockRDY)
{
	Std_ReturnType state = E_OK;
	/*	Enabling the clock source*/
	if(Copy_u8State)
	{
		/*	Set the clock on bit */
		RCC->CR |= Copy_u8Clockname;
		/*	Check the clock ready bit till rise
		 * to make sure the clock is enabled*/
		if(!(RCC->CR & Copy_u8ClockRDY))
    {
      state = E_NOT_OK;
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
      state = E_NOT_OK;
    }
	}
	return state;
}


/*  Description : This API configure system clock source Switch               */
Std_ReturnType RCC_ClockSource(u32 Copy_u8Clockname,u32 Copy_u8SysClkState)
{
	Std_ReturnType state = E_OK;
	/*Clear System clock switch bits*/
	RCC->CFGR &= CLK_CLR;
	/*Select System clock switch name*/
	RCC->CFGR |= Copy_u8Clockname;
	/*Check if the clock is selected*/
	if(!((RCC->CFGR & Copy_u8SysClkState) == Copy_u8SysClkState) )
	{
		state = E_NOT_OK;
	}
	return state;
}

/*  Description : This API configure PLL clock select                               */
Std_ReturnType RCC_PLLSRC(u32 Copy_u8Clockname,u32 Copy_u8MulOrDiv,u32 Copy_u8Operation)
{
  Std_ReturnType state = E_OK;
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
Std_ReturnType RCC_LSClockCtrl(u32 Copy_u8Clockname,u32 Copy_u8State ,u32 Copy_u8ClockRDY)
{
	Std_ReturnType state = E_OK;
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
        state = E_NOT_OK;
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
        state = E_NOT_OK;
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
        state = E_NOT_OK;
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
        state = E_NOT_OK;
      }
		}
	}
	return state;
}


/*  Description : This API Enable prepheral clock                                              */
extern Std_ReturnType RCC_PrephiralEnable(u32 Copy_u8Bus, u32 Copy_u8PreName)
{
  Std_ReturnType state = E_OK;
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
      state = E_NOT_OK;
      break;
  }
  return state;
}


/*  Description : This API disable prepheral clock                                              */
extern Std_ReturnType RCC_PrephiralDisable(u32 Copy_u8Bus, u32 Copy_u8PreName)
{
  Std_ReturnType state = E_OK;
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
      state = E_NOT_OK;
      break;
  }
  return state;
}
