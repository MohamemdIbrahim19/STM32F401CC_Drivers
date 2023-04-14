/*
 * Scheduler_cfg.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Mohamed_ibrahim
 */

#ifndef SCHEDULER_CFG_H_
#define SCHEDULER_CFG_H_

#define SCH_MAX_TASKS              3
#define SCH_TICKMS                 1


typedef struct  
{
	void (*CBF)(void);
	u32 first_delay;
	u32 period;
}Runnable_info_t;

extern const Runnable_info_t Runnable_info[SCH_MAX_TASKS];


#endif /* SCHEDULER_CFG_H_ */
