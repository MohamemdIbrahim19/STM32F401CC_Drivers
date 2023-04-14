/*
 * Scheduler.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Mohamed_ibrahim
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef enum
{
	SCH_enuOk = 0,
	SCH_enuNotOk	
}SCH_ERRORS_t;


SCH_ERRORS_t SCH_enuInit();
void SCH_enuStart();
void SCH_tick(void);

#endif /* SCHEDULER_H_ */
