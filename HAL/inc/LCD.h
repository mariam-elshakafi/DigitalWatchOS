/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : April 2,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/


#ifndef   _LCD_H_
#define   _LCD_H_




/*
 *Description : This API shall configure the LCD GPIO Data and control pins
 *Parameters  : void
 *Return      : return status 
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
extern ERROR_S LCD_Config(void);

/*
 *Description : This API shall change the Process state to Write data process
 *Parameters  : Copy_u8word , Copy_u8Length
 *Return      : return status 
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
extern ERROR_S LCD_WriteDATA(const u8 * Copy_u8word ,u8 Copy_u8Length);

/*
 *Description : This API shall change the Process state to Write command process
 *Parameters  : Copy_u8Cmd
 *Return      : return status 
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 *
extern ERROR_S LCD_WriteCMD(const u8 Copy_u8Cmd);*/

/*
 *Description : This API shall change the Process state to Clear process
 *Parameters  : void
 *Return      : return status 
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
extern ERROR_S LCD_Clear(void);

/*
 *Description : This API shall change the process state to curserMove process
 *Parameters  :  Copy_u8PosX  ,Copy_u8PosY
 *Return      : return status 
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
extern ERROR_S LCD_GOTO(u8 Copy_u8PosX, u8 Copy_u8PosY);

/*
 *Description : The runnable task of LCD
 */
extern void LCD_Task(void);

//extern

#endif
