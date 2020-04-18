/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 30 March 2020                            */
/*Descrp: program file of implementaion            */
/*Vrsion: 0.3V                                     */
/***************************************************/


#include"Std_Types.h"
#include"BIT_MATH.h"

#include"STK.h"
#include "SCHED.h"

#include "SCHED_CFG.h"

typedef struct
{
	SysTaskInfo_t *AppTask;
	u32 RemainToExcute;
	u32 PeriodicTick;
	u8  State;
}SysTasks_t;

 volatile u8 FlagStauts = 0;

static SysTasks_t ArrTASK[MAX_NO_TASK];
extern const SysTaskInfo_t ArrSysTask[MAX_NO_TASK];


void SCHED_CreateTask(TASK_t *Task )
{

	if(Task)
	{
ArrTASK[Task ->priority].AppTask ->apptask ->Runnable =Task ->Runnable;
ArrTASK[Task ->priority].PeriodicTick = (Task ->periodicity)/Tick_ms;
	}
}


static void SCHED_SCHEDULER()
{
 u32 iteration;
 for(iteration=0 ; iteration < MAX_NO_TASK ; iteration ++)
 {
	 if(ArrTASK[iteration].RemainToExcute == 0)
	 {
		 ArrTASK[iteration].AppTask ->apptask ->Runnable();
		 ArrTASK[iteration].RemainToExcute = ArrTASK[iteration].PeriodicTick ;
	 }
	 ArrTASK[iteration].RemainToExcute --;
		STK_StartCount();

 }

}

static void SCHED_SetFlag(void)
{
		FlagStauts = 1;
}

 void SCHED_StartScheduler()
{
		STK_StartCount();

	while(1)
	{
	if(FlagStauts == 1)
	{

		FlagStauts = 0;


		SCHED_SCHEDULER();


	}
    }
}

 void SCHED_Initialization(void)
 {
	 u32 iteration ;
	 STK_Initialization();  // timer configuration

	 STK_SetTime_ms();  //set timer every 5 sec.   and sys freq =8MHz

	 STK_SetCallBack(&SCHED_SetFlag);  // set CBF.

 	for(iteration =0 ; iteration <MAX_NO_TASK ; iteration++)
 	{

 		ArrTASK[iteration].AppTask = &(ArrSysTask[iteration]);
 		ArrTASK[iteration].RemainToExcute = ArrSysTask[iteration].FirstDelay;
 		ArrTASK[iteration].PeriodicTick = (ArrSysTask[iteration].apptask ->periodicity)/Tick_ms;
 		SCHED_CreateTask(((ArrTASK[iteration].AppTask)->apptask));
 	}



 }





















