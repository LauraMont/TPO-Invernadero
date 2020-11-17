/*
 * DR_timer.c
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#include "DR_timer.h"

volatile timer_t timers[MAX_TIMERS];

void timer_discount(void) {
	uint8_t i;

	for(i = 0; i < MAX_TIMERS; i++) {
		if(timers[i].active && !timers[i].expired) {
			timers[i].msecs--;

			if(!timers[i].msecs) {
				timers[i].expired = 1;
			}
		}
	}
}
