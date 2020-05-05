#include "Std_Types.h"
#include <stdio.h>
#include "GPIO.h"
#include "RCC.h"
#include "HRCC.h"
#include "HUART.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"
#include "SCHED.h"

#include "WATCH.h"
#include "WATCH_CFG.h"

/**
 * @brief This is the structure of the frame to be send over UART.
 *
 */
typedef struct
{
	u8 swCfgState;
	u8 swIncState;
	u8 swDecState;
	u8 swRightState;
	u8 swLeftState;
	u8 swDateState;
} WATCH_switchStates_t;

typedef union
{
	WATCH_switchStates_t switchStates;
	u8 buffer[6];
} WATCH_frame_t;


/*-------------------------- Macros --------------------------*/

#define WATCH_RUN_MODE                0
#define WATCH_CFG_MODE                1

#define WATCH_HRS_FIELD               0
#define WATCH_MIN_FIELD               1
#define WATCH_SEC_FIELD               2

#define WATCH_FIRST_POS               0


#define WATCH_DISPLAY_CURSOR_OFF      0
#define WATCH_DISPLAY_GOTO_START      1
#define WATCH_DISPLAY_WRITE_DATA      2
#define WATCH_DISPLAY_MOVE_CURSOR     3
#define WATCH_DISPLAY_CURSOR_ON       4
#define WATCH_DISPLAY_HOLD_CURSOR     7

/*-------------------------- Global Variables --------------------------*/

static volatile u16 WATCH_counter;
static volatile u8 WATCH_fields[3];
static volatile u8 WATCH_frozenVal;
static volatile u8 WATCH_mode = WATCH_RUN_MODE;
static volatile u8 WATCH_position = WATCH_HRS_FIELD;
static volatile u8 WATCH_day = 5;
static volatile u8 WATCH_month = 5;
static volatile u16 WATCH_year = 2020;
static volatile u8 WATCH_displayState = 0;

WATCH_frame_t sendFrame;
WATCH_frame_t receiveFrame;


/*-------------------------- WATCH Tasks --------------------------*/

TASK_t WATCH_Task = {WATCH_Main_Runnable, 1, 50};



/*-------------------------- Private Functions --------------------------*/



/**
 * @brief This function updates date when full 24 hours have passed
 *
 */
static void WATCH_UpdateDate(void)
{
	WATCH_day++;
	if (WATCH_day > 30)
	{
		WATCH_day = 1;
		WATCH_month++;
	}

	if (WATCH_month > 12)
	{
		WATCH_month = 1;
		WATCH_year++;
	}
}


/**
 * @brief This function updates time when a second has passed, or when configuration switches are used
 * 		  (i.e : updates according to watch mode)
 *
 * @param watchMode holds the mode passed by the calling program
 *			@arg WATCH_RUN_MODE
 *			@arg WATCH_CFG_MODE
 *
 */
static void WATCH_Update(u8 watchMode)
{
	if (WATCH_fields[WATCH_SEC_FIELD] == 60)
	{
		WATCH_fields[WATCH_SEC_FIELD] = 0;
		if (watchMode == WATCH_RUN_MODE)
		{
			WATCH_fields[WATCH_MIN_FIELD]++;
		}
	}
	if (WATCH_fields[WATCH_MIN_FIELD] == 60)
	{
		WATCH_fields[WATCH_MIN_FIELD] = 0;
		if (watchMode == WATCH_RUN_MODE)
		{
			WATCH_fields[WATCH_HRS_FIELD]++;
		}
	}
	if (WATCH_fields[WATCH_HRS_FIELD] == 24)
	{
		WATCH_fields[WATCH_HRS_FIELD] = 0;
		WATCH_UpdateDate();
	}

	/* Section of ugly if conditions */
	if (watchMode == WATCH_CFG_MODE)
	{
		if (WATCH_fields[WATCH_SEC_FIELD] > 60)
		{
			WATCH_fields[WATCH_SEC_FIELD] = 59;
		}
		if (WATCH_fields[WATCH_MIN_FIELD] > 60)
		{
			WATCH_fields[WATCH_MIN_FIELD] = 59;
		}
		if (WATCH_fields[WATCH_HRS_FIELD] > 24)
		{
			WATCH_fields[WATCH_HRS_FIELD] = 23;
		}
	}
}


/**
 * @brief This function sends switch states through UART.
 *
 */
static void WATCH_Send(void)
{

	u8 swCounter = 0;
	for (swCounter = 0; swCounter < SWITCH_NUM; swCounter++)
	{
		sendFrame.buffer[swCounter] = SWITCH_readSwitchState(swCounter);
	}

	Huart_Send(sendFrame.buffer, 6);
}




/**
 * @brief This function is called upon receiving control frame. It has the main watch logic as follows:
 * 			1. When CFG switch is pressed, change current watch mode.
 * 			2. When watch mode is Running mode, other switches have no effect (except for the DATE switch which is handled elsewhere).
 * 			3. When watch mode is Configuration mode, perform operations according to pressed switch (INC, DEC, LEFT, RIGHT).
 *
 */
static void WATCH_Control(void)
{
	if(receiveFrame.switchStates.swCfgState == SWITCH_PRESSED)
	{
		WATCH_mode ^= 1;
	}

	if (WATCH_mode == WATCH_CFG_MODE)
	{
		if (receiveFrame.switchStates.swIncState == SWITCH_PRESSED)
		{
			/* 3la asa enha msh sa3et Mark */
			WATCH_fields[WATCH_position]++;
			WATCH_Update(WATCH_CFG_MODE);
			WATCH_frozenVal = WATCH_fields[WATCH_position];
		}
		else if (receiveFrame.switchStates.swDecState == SWITCH_PRESSED)
		{
			WATCH_fields[WATCH_position]--;
			WATCH_Update(WATCH_CFG_MODE);
			WATCH_frozenVal = WATCH_fields[WATCH_position];
		}
		else if (receiveFrame.switchStates.swRightState == SWITCH_PRESSED)
		{
			if (WATCH_position < 2)
			{
				WATCH_position++;
				WATCH_frozenVal = WATCH_fields[WATCH_position];
				WATCH_displayState = 0;
			}
		}
		else if (receiveFrame.switchStates.swLeftState == SWITCH_PRESSED)
		{
			if (WATCH_position > 0)
			{
				WATCH_position--;
				WATCH_frozenVal = WATCH_fields[WATCH_position];
				WATCH_displayState = 0;
			}

		}
	}
}


/**
 * @brief This function handles display status, and also handles the DATE switch.
 *
 */
static void WATCH_Display(void)
{
	u8 WATCH_displayDataBuffer[20];
	if ((receiveFrame.switchStates.swDateState == SWITCH_PRESSED) && (WATCH_displayState == WATCH_DISPLAY_WRITE_DATA))
	{
		sprintf(WATCH_displayDataBuffer,"%.2d/%.2d/%.4d",WATCH_day,WATCH_month,WATCH_year);
		LCD_WriteDATA(WATCH_displayDataBuffer,10);
		WATCH_displayState = 0;
		return ;
	}
	switch (WATCH_displayState++)
	{
		case WATCH_DISPLAY_CURSOR_OFF:
			LCD_Cursor_ON_OFF(LCD_CURSOR_OFF);
			break;

		case WATCH_DISPLAY_GOTO_START:
			LCD_GOTO(WATCH_FIRST_POS,LCD_FIRST_ROW);
			break;

		case WATCH_DISPLAY_WRITE_DATA:
			if(WATCH_mode == WATCH_RUN_MODE)
			{
				sprintf(WATCH_displayDataBuffer,"%.2d:%.2d:%.2d  ",WATCH_fields[WATCH_HRS_FIELD],WATCH_fields[WATCH_MIN_FIELD],WATCH_fields[WATCH_SEC_FIELD]);
			}
			else if (WATCH_mode == WATCH_CFG_MODE)
			{
				switch (WATCH_position)
				{
					case WATCH_HRS_FIELD:
						sprintf( WATCH_displayDataBuffer,"%.2d:%.2d:%.2d  ",WATCH_frozenVal,WATCH_fields[WATCH_MIN_FIELD],WATCH_fields[WATCH_SEC_FIELD]);
						break;
					case WATCH_MIN_FIELD:
						sprintf( WATCH_displayDataBuffer,"%.2d:%.2d:%.2d  ",WATCH_fields[WATCH_HRS_FIELD],WATCH_frozenVal,WATCH_fields[WATCH_SEC_FIELD]);
						break;
					case WATCH_SEC_FIELD:
						sprintf( WATCH_displayDataBuffer,"%.2d:%.2d:%.2d  ",WATCH_fields[WATCH_HRS_FIELD],WATCH_fields[WATCH_MIN_FIELD],WATCH_frozenVal);
						break;
				}
			}
			LCD_WriteDATA(WATCH_displayDataBuffer,10);
			break;

		case WATCH_DISPLAY_MOVE_CURSOR:
			LCD_GOTO(((3*WATCH_position)+1),LCD_FIRST_ROW);
			break;

		case WATCH_DISPLAY_CURSOR_ON:
			if(WATCH_mode == WATCH_CFG_MODE)
			{
				LCD_Cursor_ON_OFF(LCD_CURSOR_ON);
			}
			break;

		case WATCH_DISPLAY_HOLD_CURSOR:
			WATCH_displayState = WATCH_DISPLAY_CURSOR_OFF;
			break;
	}
}


/*-------------------------- WATCH APIs --------------------------*/


/**
 * @brief This API is used to initialize watch elements.
 *
 */
void WATCH_Initialization(void)
{
	HRCC_SystemClockInit();
	HRCC_PortCLockEnable(HRCC_PORTA);
	HRCC_PortCLockEnable(HRCC_PORTB);
	HRCC_PortCLockEnable(HRCC_PORTC);
	RCC_PrephiralEnable(AHB,DMA1_EN);
	LCD_Config();

	SWITCH_init();

	Huart_Initialization();

	Huart_SetRxCbf(&WATCH_Control);

	WATCH_frozenVal = WATCH_fields[WATCH_HRS_FIELD];
}


/**
 * @brief This API is the runnable of the Watch that calls other functions to fully control the system.
 * It's called every 50 ms. If periodicity is to be changed. Change WATCH_SEC_MULTIPLIER to a proper value accordingly.
 *
 * WATCH_SEC_MULTIPLIER * periodicity = 1 second
 *
 */

void WATCH_Main_Runnable(void)
{

	/* Update in background */
	if(WATCH_counter == WATCH_SEC_MULTIPLIER)
	{
		WATCH_fields[WATCH_SEC_FIELD]++;
		WATCH_Update(WATCH_RUN_MODE);
		WATCH_counter = 0;
	}

	WATCH_counter++;

	Huart_Receive(receiveFrame.buffer, 6);

	WATCH_Display();

	if(WATCH_counter % 2 == 0)
	{
		WATCH_Send();
	}
}
