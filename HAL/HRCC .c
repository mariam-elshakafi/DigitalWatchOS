/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA									*/
/*									DATE    : April 5 ,2020									*/
/*									version : V1.0											*/
/********************************************************************************************/

#include "STD_Types.h"
#include "RCC.h"

#include "HRCC.h"
#include "HRCC_CFG.h"


/*
 * Description : This API shall initialize system clock
 * parameters  : void
 * Return      : ERROR_S
 *                  ERROR_OK
 *                  ERROR_NOK
 */
 ERROR_S  HRCC_SystemClockInit(void)
 {
    ERROR_S ERROR_STATE = ERROR_NOK;
    switch(HRCC_SYSTEM_CLOCK)
    {
        case HSI :
            ERROR_STATE |= RCC_HSClockCtrl(HSION, ENABLE , HSIRDY);
            ERROR_STATE |= RCC_ClockSource(HRCC_SYSTEM_CLOCK , ENABLE);    
            break;
        case HSE :
            ERROR_STATE |= RCC_HSClockCtrl(HSEON, ENABLE , HSERDY);
            ERROR_STATE |= RCC_ClockSource(HRCC_SYSTEM_CLOCK , ENABLE);
            break;
        case PLL :
            ERROR_STATE |= RCC_HSClockCtrl(PLLON, ENABLE , PLLRDY);
            ERROR_STATE |= RCC_ClockSource(HRCC_SYSTEM_CLOCK , ENABLE);
            break;
        default  :
            ERROR_STATE = ERROR_NOK;
    }
    return ERROR_STATE;

 }

/*
 * Description : This API shall Enable clock on port
 * parameters  : Copy_u32Port 
 *                  HRCC_PORTA
 *                  HRCC_PORTB
 *                  HRCC_PORTC
 *                  HRCC_PORTD
 *                  HRCC_PORTE
 *                  HRCC_PORTF
 * Return      : ERROR_S
 *                  ERROR_OK
 *                  ERROR_NOK
 */
 ERROR_S  HRCC_PortCLockEnable(u32 Copy_u32Port)
 {
    ERROR_S ERROR_STATE = ERROR_NOK;

    ERROR_STATE |= RCC_PrephiralEnable( APB2 , Copy_u32Port);
    switch(Copy_u32Port)
    {
    	case HRCC_PORTA:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPA_EN);
    	    break;
    	case HRCC_PORTB:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPB_EN);
    	    break;
    	case HRCC_PORTC:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPC_EN);
    	    break;
    	case HRCC_PORTD:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPD_EN);
    	    break;
    	case HRCC_PORTE:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPE_EN);
    	    break;
    	case HRCC_PORTF:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPF_EN);
    	    break;
    	case HRCC_PORTG:
    	    ERROR_STATE |= RCC_PrephiralEnable( APB2 , IOPG_EN);
    	    break;

    }

    return ERROR_STATE;
 }

