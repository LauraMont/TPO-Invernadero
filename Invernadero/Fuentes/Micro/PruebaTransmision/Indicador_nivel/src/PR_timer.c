/*
 * PR_timer.c
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#include "PR_timer.h"
#include "DR_timer.h"

void timer_event(void) {
	uint32_t i;

	for(i = 0; i < MAX_TIMERS; i++) {
		if(timers[i].expired) {
			timers[i].callback(i);
		}
	}
}

void timer_start(uint32_t id, uint32_t msecs, timer_callback callback) {
	timers[id].expired = 0;
	timers[id].msecs = msecs;
	timers[id].callback = callback;
	timers[id].active = 1;
}

void timer_stop(uint32_t id) {
	timers[id].active = 0;
}
