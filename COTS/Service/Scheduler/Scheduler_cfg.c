/*
 * Scheduler_cfg.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Mohamed
 */
#include "STD_TYPES.h"
#include "Scheduler_cfg.h"
#include "APPs.h"

const Runnable_info_t Runnable_info[SCH_MAX_TASKS] = 
{
	[0] = 
	{
		.CBF = APP1,
		.first_delay = 100,
		.period = 1000,
	},
	
	[1] = 
	{
		.CBF = APP2,
		.first_delay = 0,
		.period = 500,
	} , 
	
	[2] = 
	{	
		.CBF = APP3,
		.first_delay = 1000,
		.period = 700,
	}
};


