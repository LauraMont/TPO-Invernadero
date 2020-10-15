/*
 * DR_SYSTICK.h
 *
 *  Created on: Sep 4, 2020
 *      Author: augusto
 */

#ifndef DR_SYSTICK_H_
#define DR_SYSTICK_H_

void Inicializar_systick(void);

uint32_t get_ticks(void);
void reset_ticks(void);

#endif /* DR_SYSTICK_H_ */

