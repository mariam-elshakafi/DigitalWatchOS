#include "Std_Types.h"
#include "HUART.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "SWITCH.h"
#include "SWITCH_CFG.h"
#include "SCHED.h"


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



#define WATCH_RUN_MODE    0
#define WATCH_CFG_MODE    1

#define WATCH_HRS_FIELD   0
#define WATCH_MIN_FIELD   1
#define WATCH_SEC_FIELD   2

#define WATCH_FIRST_POS   1

static u16 WATCH_counter;
static u8 WATCH_fields[3];
static u8 WATCH_frozenVal = WATCH_fields[WATCH_HRS_FIELD];
static u8 WATCH_mode = WATCH_RUN_MODE;
static u8 WATCH_position = WATCH_HRS_FIELD;
static u8 WATCH_day, WATCH_month, WATCH_year;

WATCH_frame_t sendFrame;
WATCH_frame_t receiveFrame;


WATCH_UpdateDate()
{
	WATCH_day++;
}


void WATCH_Update(u8 watchMode)
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

void WATCH_Send(void)
{

	u8 swCounter = 0;
	for (swCounter = 0; swCounter < SWITCH_NUM; swCounter++)
	{
		sendFrame.switchStates[swCounter] = SWITCH_readSwitchState(swCounter);
	}

	Huart_Send(sendFrame.buffer, 6);
}


void WATCH_Control(void)
{
	if(receiveFrame.switchStates[SWITCH_CFG] == SWITCH_PRESSED)
	{
		WATCH_mode ^= 1;
	}

	if (WATCH_mode == WATCH_CFG_MODE)
	{
		if (receiveFrame.switchStates[SWITCH_INC] == SWITCH_PRESSED)
		{
			WATCH_fields[WATCH_position]++;
			WATCH_Update(WATCH_CFG_MODE);
		}
		else if (receiveFrame.switchStates[SWITCH_DEC] == SWITCH_PRESSED)
		{
			WATCH_fields[WATCH_position]--;
			WATCH_Update(WATCH_CFG_MODE);
		}
		else if (receiveFrame.switchStates[SWITCH_RIGHT] == SWITCH_PRESSED)
		{
			if (WATCH_position < 2)
			{
				WATCH_position++;
				WATCH_frozenVal = WATCH_fields[WATCH_position];
			}
		}
		else if (receiveFrame.switchStates[SWITCH_LEFT] == SWITCH_PRESSED)
		{
			if (WATCH_position > 0)
			{
				WATCH_position--;
				WATCH_frozenVal = WATCH_fields[WATCH_position];
			}

		}
	}
}



void WATCH_Display(void)
{
	static u8 attitude = 0;
	switch (attitude)
	{
		case 0:
			LCD_Cursor_ON_OFF(LCD_CURSOR_OFF);
			break;
		case 1:
			LCD_GOTO(WATCH_FIRST_POS,LCD_FIRST_ROW);
			break;
		case 2:
			if(WATCH_mode == WATCH_RUN_MODE)
			{
				// hktb kolo mn el awl
			}
			else if (WATCH_mode == WATCH_CFG_MODE)
			{
				//hnktb f el frozen value
			}
	}
}

void WATCH_Main_Runnable(void)
{

	/* Update in background */
	if(WATCH_counter == 20)
	{
		WATCH_fields[WATCH_SEC_FIELD]++;
		WATCH_Update(WATCH_RUN_MODE);
		WATCH_counter = 0;
	}

	WATCH_counter++;

	Huart_Receive(receiveFrame.buffer, 6);

	WATCH_Control();

	WATCH_Display();

	WATCH_Send();

}
