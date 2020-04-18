/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 26 March 2020                            */
/*Descrp: program file of implementaion            */
/*Vrsion: 0.0V                                     */
/***************************************************/ 

#include "BIT_MATH.h"
#include "Std_Types.h"

#include "STK.h"
#include "STK_CFG.h"



	/* global pointer to funcction for assignation of call back function */
void (*SysTick_CallBack)(void);

				/******************************************************/
				
		/*  initialization API function  */
status_t STK_Initialization(void)
{
	
/*
*	clear Enable pin (Disable )
*/
	 STK_CTRL &= STK_DISABLE ;

/* To select between AHB or AHB/8 CLK SRC.
/   get the from STK_CLK_SRC mask and  assign the returned value shift by 2 to pin
*/ STK_CTRL |= (Get_Bit(STK_CLK_SCR,0)<< 2 ) ;

	/* TO select between TICK INT on or off*/
STK_CTRL |= (Get_Bit(STK_TICK_INT,0)<< 1 ) ;

/*
*  note1:the VAL_register has randomly value at initialization so should be cleared at initialization code.
*  note2: writing any value to VAL_regist clears fields to zero and
*   clear COUNTFLAG bit in the STK_CTRL register to 0.
*/
		STK_VAL= 0;
	
return status_ok;
		
}  // end of function.


/*************************************************************************************/

	/* start count API            */

status_t STK_StartCount(void)
{
/*
 * Enable counting Bit.
 */
		 STK_CTRL |= STK_ENABLE ;

	
	return status_ok;
}  // end of function.

/*************************************************************************************/


	/* stop count API            */

status_t STK_StopCount()
{
/*
 * Disable Counting Bit.
 */
		 STK_CTRL &= STK_DISABLE ;
	
	return status_ok;
}

/*****************************************************************************************/
			
	/* set times required to value in ms systic */

status_t  STK_SetTime_ms(void)
{

/*
 *  Reload value = (desired) * SRC_CLK_PERIOD  -1
 */

status_t Loc_ErrorState = status_ok;

		if(STK_CLK_SCR == STK_AHB_CLK_SRC )
		{
			STK_LOAD = (TIME_ms*((AHB_CLK_SRC_Hz)/1000))-1;
		}
		else if(STK_CLK_SCR == STK_AHB_ClK_SRC_DIV8)
		{
			STK_LOAD = (TIME_ms*((AHB_CLK_SRC_Hz)/8000))-1;
		}
		else
		{
			Loc_ErrorState = status_nok;
		}

		STK_VAL =0;

	return Loc_ErrorState ;
}    // end of function.

			/**************************************************************/
			
/*
 *  setter funcion implementaion
*/

status_t STK_SetCallBack(void(*Copy_ptr)(void))
{

			SysTick_CallBack = Copy_ptr;

	return status_ok;
}	// end of function.

			/**************************************************************/
			
/*
 *  systick handler implementaion
*/
 void SysTick_Handler(void)
{
	 SysTick_CallBack();

}     //end of function.


