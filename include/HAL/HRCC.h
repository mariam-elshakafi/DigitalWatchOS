/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA									*/
/*									DATE    : April 5 ,2020									*/
/*									version : V1.0											*/
/********************************************************************************************/

#ifndef _HRCC_H_
#define _HRCC_H_

#define HRCC_PORTA 	GPIO_PORTA
#define HRCC_PORTB  GPIO_PORTB
#define HRCC_PORTC 	GPIO_PORTC
#define HRCC_PORTD 	3
#define HRCC_PORTE  4
#define HRCC_PORTF 	5
#define HRCC_PORTG 	6


/*
 * Description : This API shall initialize system clock
 * parameters  : void
 * Return      : Std_ReturnType
 *                  ERROR_OK
 *                  ERROR_NOK
 */
extern Std_ReturnType  HRCC_SystemClockInit(void);

/*
 * Description : This API shall Enable clock on port
 * parameters  : Copy_u32Port 
 *                  GPIOA
 *                  GPIOB
 *                  GPIOC
 *                  GPIOD
 *                  GPIOE
 *                  GPIOF                    
 * Return      : Std_ReturnType
 *                  ERROR_OK
 *                  ERROR_NOK
 */
extern Std_ReturnType  HRCC_PortCLockEnable(u32 Copy_u32Port);

#endif
