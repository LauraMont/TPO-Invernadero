#include "PR_UART0.h"
#include "DR_UART0.h"

#define DATA_SIZE 6

void UART0_init(void) {
	UART0_dr_init();
}

int32_t UART0_pop_rx(void) {
	if(UART0_rx_in == UART0_rx_out) {
		return -1;
	} else {
		int32_t ret = UART0_rx_buff[UART0_rx_out];

		UART0_rx_out++;

		if(UART0_rx_out == RX_BUFF_SIZE) {
			UART0_rx_out = 0;
		}

		return ret;
	}
}

void UART0_push_tx(uint8_t dato) {
	if(UART0_flag_tx) {
		UART0_tx_buff[UART0_tx_in] = dato;

		UART0_tx_in++;

		if(UART0_tx_in == TX_BUFF_SIZE) {
			UART0_tx_in = 0;
		}
	} else {
		UART0_write_tx_reg(dato);
		UART0_flag_tx = 1;
	}
}

void UART0_transmitir(uint8_t* msg) {
	uint32_t idx = 0;

	for( idx =0 ; idx<DATA_SIZE; idx++){
		UART0_push_tx(msg[idx]);
	}
}
