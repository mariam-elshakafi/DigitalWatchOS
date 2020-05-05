/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 30 March 2020                            */
/*Descrp: configuration file of scheduler tasks    */
/*Vrsion: 0.3V                                     */
/***************************************************/

#include "Std_Types.h"

#include "SCHED.h"
#include "SCHED_CFG.h"

extern TASK_t SWITCH_Task;
extern TASK_t LCD_Task;
extern TASK_t WATCH_Task;

const  SysTaskInfo_t ArrSysTask[] = { {&SWITCH_Task, 0},
									  {&WATCH_Task,  0},
									  {&LCD_Task,    0}
									};

