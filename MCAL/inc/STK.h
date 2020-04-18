/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 26 March 2020                            */
/*Descrp: interface fiel of API's                  */
/*Vrsion: 0.0V                                     */
/***************************************************/

/*  file gaurd       */
#ifndef _STK_H_
#define _STK_H_

#define STK_BASE_ADDRESS   0XE000E010
#define STK_CTRL        *((volatile u32*)(STK_BASE_ADDRESS + 0x00))
#define STK_LOAD        *((volatile u32*)(STK_BASE_ADDRESS + 0x04))
#define STK_VAL         *((volatile u32*)(STK_BASE_ADDRESS + 0x08))
#define STK_CALIB       *((volatile u32*)(STK_BASE_ADDRESS + 0x0C))


#define STK_AHB_CLK_SRC                  (u8)1
#define STK_AHB_ClK_SRC_DIV8             (u8)0

#define STK_TICK_INT_ON                  (u8)1
#define STK_TICK_INT_OFF                 (u8)0

#define STK_ENABLE                   0x00000001
#define STK_DISABLE                  0xFFFFFFFE 




status_t STK_Initialization(void);
status_t STK_StartCount(void);
status_t STK_StopCount(void);

status_t STK_SetTime_ms(void);

status_t STK_SetCallBack(void(*Copy_ptr)(void));





#endif              // end of file gaurd 
