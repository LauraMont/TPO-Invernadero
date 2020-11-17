/*
 * RxTrama.h
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#ifndef RX_TRAMA_H_
#define RX_TRAMA_H_

typedef enum {
	RX_TRAMA_RESET = 0,
	WAITING_START,
	WAITING_DATA,
	WAITING_END,
	RX_TRAMA_ERROR
} rx_trama_state_en;

void rx_trama_MDE(void);

rx_trama_state_en rx_trama_current_state(void);

/*static*/ uint32_t get_temp_min(void);
/*static*/ uint32_t get_temp_max(void);
/*static*/ uint32_t get_humidity(void);

#endif /* RX_TRAMA_H_ */
