/*
 * DR_timer.h
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#ifndef DR_TIMER_H_
#define DR_TIMER_H_

#include "PR_timer.h"
#include "DR_tipos.h"

#define		MAX_TIMERS		(5)

typedef struct {
	uint8_t active;
	uint8_t expired;
	uint32_t msecs;
	timer_callback callback;
}timer_t;

extern volatile timer_t timers[];

void timer_discount(void);

#endif /* DR_TIMER_H_ */
