#include "Std_Types.h"
#include "GPIO.h"
#include "HRCC.h"
#include "LCD.h"
#include "SCHED.h"


int main()
{
	SCHED_Initialization();
	SCHED_StartScheduler();
	return 0;
}

/*APP:
 * Switch_Runnable (update switch states)
 * LCD_Runnable
 * Watch_Update_Runnable (++sec, ++min, ++hours)
 * Main_Runnable (read, send to lcd)
 */
