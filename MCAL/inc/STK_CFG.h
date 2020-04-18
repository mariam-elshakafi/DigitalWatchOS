/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 26 March 2020                            */
/*Descrp: configuration fiel of API's              */
/*Vrsion: 0.0V                                     */
/***************************************************/
/* file gaurd   */
#ifndef _STK_CFG_H_
#define _STK_CFG_H_

#include"STK_int.h"

/*
 options : 1) STK_AHB_CLK_SRC  ====>  clk  src from AHB 
*          2) STK_AHB_ClK_SRC_DIV8   ===> clk src from AHB/8
*/
#define STK_CLK_SCR   STK_AHB_ClK_SRC_DIV8


/* options : 1) STK_TICK_INT_ON ===> Enables the systick interrupt. 
*			 2)	STK_TICK_INT_OFF===> Disable the systick interrupt.
*/
#define STK_TICK_INT  STK_TICK_INT_ON


/*
 *  options : time in ms
 *  ex. define TIME_ms    1000      ===> TIME =  1 Sec.
 */

#define TIME_ms  5000


/*
 * This macro provieds the system CLK of the microcontroller.
 * options :
 */

#define AHB_CLK_SRC_Hz  8000000













#endif   // end of file gaurd.
