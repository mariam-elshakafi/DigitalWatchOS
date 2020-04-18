/**********************************************************/
/*Author: Bassem Ezzat Abdelatife                         */
/* Date : 30 March 2020                                   */
/*Descrp: configuration file of No of tasks and Tick time */
/*Vrsion: 0.3V                                            */
/**********************************************************/


#ifndef SCHED_CFG_H_
#define SCHED_CFG_H_

#define MAX_NO_TASK 1

#define Tick_ms    5000

typedef struct
 {
 	 TASK_t *  apptask;
 	u32 FirstDelay;
 }SysTaskInfo_t;

#endif /* SCHED_CONFIG_H_ */
