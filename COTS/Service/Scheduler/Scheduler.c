/*
 * Scheduler.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Mohamed_ibrahim
 */

#include "STD_TYPES.h"
#include "Scheduler_cfg.h"
#include "Scheduler.h"
#include "Timer0.h"

typedef struct  
{
	Runnable_info_t* Task_infoPtr;
	u32 Remaining_time;
}Task_t;

Task_t Task_list[SCH_MAX_TASKS];

u8 Dispatch_Flag = 0;

static void _Sched(void);

SCH_ERRORS_t SCH_enuInit()
{
	SCH_ERRORS_t SCH_ERRORS = SCH_enuOk;
	u8 Local_couter = 0;
	
	//  Set timer 0 Mode | enable interrupt
	TMR0_vidInitPreCompile();
		
	//  Set Timer OV in milliseconds
	TMR0_enuSetTickTimeMS(1);
		
	//  Set Task1 address
	TMR0_enuRegisterCallback(SCH_tick);
	
	/*initialize data*/
	for(Local_couter=0 ; Local_couter<SCH_MAX_TASKS ; Local_couter++)
	{
		Task_list[Local_couter].Task_infoPtr = &(Runnable_info[Local_couter]);
		Task_list[Local_couter].Remaining_time = Runnable_info[Local_couter].first_delay;
	}
	return SCH_ERRORS;
}

void SCH_enuStart()
{
	// Start counting
	TMR0_enuStart();
	
	while(1)
	{
		if(Dispatch_Flag == 1)
		{
			_Sched();
			Dispatch_Flag = 0;
		}
	}
}

void SCH_tick(void)
{
	if(Dispatch_Flag == 0)
	{
		Dispatch_Flag = 1;
	}
	else
	{
		/*		Cpu load 100%		*/
		/*		Take Action Here	*/
	}

}

static void _Sched(void)
{
	u8 Local_counter = 0;
	for(Local_counter=0 ; Local_counter<SCH_MAX_TASKS ; Local_counter++)
	{
		if(Task_list[Local_counter].Task_infoPtr)
		{
			if(Task_list[Local_counter].Task_infoPtr->CBF)
			{
				if(Task_list[Local_counter].Remaining_time == 0)
				{
					Task_list[Local_counter].Task_infoPtr->CBF();
					Task_list[Local_counter].Remaining_time = Task_list[Local_counter].Task_infoPtr->period;
					
				}
				else
				{
					Task_list[Local_counter].Remaining_time -= SCH_TICKMS;
				}
			}
		}
	}
}