/*
 * PR_Timers.h
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#ifndef PR_TIMER_H_
#define PR_TIMER_H_

#include "DR_tipos.h"

typedef void (*timer_callback)(uint32_t);

void timer_event(void);

void timer_start(uint32_t id, uint32_t msecs, timer_callback callback);

void timer_stop(uint32_t id);

#endif /* PR_TIMER_H_ */
