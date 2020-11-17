#ifndef DRIVERLPC_DR_UART0_H_
#define DRIVERLPC_DR_UART0_H_

#include "DR_tipos.h"

#define 	RX_BUFF_SIZE		64
#define 	TX_BUFF_SIZE		64

extern volatile uint8_t UART0_rx_buff[];
extern volatile uint32_t UART0_rx_in, UART0_rx_out;

extern volatile uint8_t UART0_tx_buff[];
extern volatile uint32_t UART0_tx_in, UART0_tx_out;

extern volatile uint8_t UART0_flag_tx;

void UART0_dr_init(void);

void UART0_push_rx(uint8_t dato);
int32_t UART0_pop_tx(void);

void UART0_write_tx_reg(uint8_t dato);

#endif /* DRIVERLPC_DR_UART0_H_ */
