/*
 * DR_PINSEL.h
 *
 *  Created on: Sep 12, 2019
 *      Author: augusto
 */

#ifndef DR_PINSEL_H_
#define DR_PINSEL_H_

void PINSEL_set_selection(uint8_t port, uint8_t pin, uint8_t selection);

void PINMODE_set_selection(uint8_t port, uint8_t pin, uint8_t selection);

#endif /* DR_PINSEL_H_ */
