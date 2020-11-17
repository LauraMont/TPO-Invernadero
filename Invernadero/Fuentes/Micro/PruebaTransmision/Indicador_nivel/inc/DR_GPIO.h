/*
 * DR_GPIO.h
 *
 *  Created on: Sep 12, 2019
 *      Author: augusto
 */

#ifndef DR_GPIO_H_
#define DR_GPIO_H_

#include "DR_tipos.h"

void GPIO_set_dir(uint8_t port, uint8_t pin, uint8_t dir);
void GPIO_set_pin(uint8_t port, uint8_t pin);
void GPIO_clear_pin(uint8_t port, uint8_t pin);
void GPIO_toggle_pin(uint8_t port, uint8_t pin);
uint8_t GPIO_read_pin(uint8_t port, uint8_t pin);

#endif /* DR_GPIO_H_ */
