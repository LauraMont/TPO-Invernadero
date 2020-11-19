/*
 * PR_UART0.h
 *
 *  Created on: Oct 31, 2019
 *      Author: augusto
 */

#ifndef PR_UART0_H_
#define PR_UART0_H_

#include "DR_tipos.h"

void UART0_init(void);

int32_t UART0_pop_rx(void);
void UART0_push_tx(uint8_t dato);

uint8_t is_ready(void);

void UART0_transmitir(uint8_t* msg);
#endif /* PR_UART0_H_ */
