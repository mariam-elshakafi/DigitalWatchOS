/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : April 2,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/


#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_

#define     LCD_BIT_MODE                 8

#define     LCD_GPIO_D0_PORT           GPIO_PORTA
#define     LCD_GPIO_D0_PIN            GPIO_PIN_0
#define     LCD_GPIO_D1_PORT           GPIO_PORTA
#define     LCD_GPIO_D1_PIN            GPIO_PIN_1
#define     LCD_GPIO_D2_PORT           GPIO_PORTA
#define     LCD_GPIO_D2_PIN            GPIO_PIN_2
#define     LCD_GPIO_D3_PORT           GPIO_PORTA
#define     LCD_GPIO_D3_PIN            GPIO_PIN_3
#define     LCD_GPIO_D4_PORT           GPIO_PORTA
#define     LCD_GPIO_D4_PIN            GPIO_PIN_4
#define     LCD_GPIO_D5_PORT           GPIO_PORTA
#define     LCD_GPIO_D5_PIN            GPIO_PIN_5
#define     LCD_GPIO_D6_PORT           GPIO_PORTA
#define     LCD_GPIO_D6_PIN            GPIO_PIN_6
#define     LCD_GPIO_D7_PORT           GPIO_PORTA
#define     LCD_GPIO_D7_PIN            GPIO_PIN_7

#define     LCD_GPIO_EN_PORT           GPIO_PORTA
#define     LCD_GPIO_EN_PIN            GPIO_PIN_10
#define     LCD_GPIO_RW_PORT           GPIO_PORTA
#define     LCD_GPIO_RW_PIN            GPIO_PIN_9
#define     LCD_GPIO_RS_PORT           GPIO_PORTA
#define     LCD_GPIO_RS_PIN            GPIO_PIN_8

#define     LCD_ROWS_NUM                  2

#define     LCD_MAX_DATA_BUFFER_LEN       32

#define     LCD_FIRST_ROW                 0x80
#define     LCD_SCND_ROW                  0xC0

#endif
