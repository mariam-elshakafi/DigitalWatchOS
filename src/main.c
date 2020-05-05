#include "Std_Types.h"
#include "SCHED.h"
#include "WATCH.h"

/* Runnables:
 *
 * SWITCH_Runnable (update switch states)
 * LCD_Runnable (perform requested LCD services)
 * WATCH_Main_Runnable (update clock every second, display proper data on LCD)
 *
 * Interrupts:
 * Receive interrupt (Calls watch control logic when full data packet is received)
 *
 */

int main()
{
	WATCH_Initialization();
	SCHED_Initialization();
	SCHED_StartScheduler();
	return 0;
}
