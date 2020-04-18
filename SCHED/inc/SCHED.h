/***************************************************/
/*Author: Bassem Ezzat Abdelatife                  */
/* Date : 30 March 2020                            */
/*Descrp: interface file of scheduler 			   */
/*Vrsion: 0.3V                                     */
/***************************************************/

#ifndef SCHED_H_
#define SCHED_H_





typedef void (*task_t)(void);

typedef struct
{
	task_t Runnable;
	u32   priority;
	u32   periodicity;
}TASK_t;




void SCHED_CreateTask(TASK_t *Task );
void SCHED_Initialization(void);
void SCHED_StartScheduler(void);




#endif /* SCHED_INT_H_ */
