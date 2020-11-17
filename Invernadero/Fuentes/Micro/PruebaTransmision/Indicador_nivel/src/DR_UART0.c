#include "DR_UART0.h"
#include "DR_tipos.h"
#include "DR_PLL.h"
#include "DR_PINSEL.h"

#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		UART0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		UART0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		UART0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		UART0IER		DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		UART0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		UART0IIR		DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		UART0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		UART0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

//Macros UART0
#define		UART0DLAB_OFF	(U0LCR & 0xEF)
#define		UART0DLAB_ON	(U0LCR | 0x80)

volatile uint8_t UART0_rx_buff[RX_BUFF_SIZE];
volatile uint32_t UART0_rx_in, UART0_rx_out;

volatile uint8_t UART0_tx_buff[TX_BUFF_SIZE];
volatile uint32_t UART0_tx_in, UART0_tx_out;

volatile uint8_t UART0_flag_tx;

void UART0_dr_init(void) {
	#define		UART_PCON_BIT		(3)

	#define		UART_PCLK_BIT		(6)
	#define		UART_PCLK_DIV		(0x00)

	// 1 - PCONP
	PCONP |= (1 << UART_PCON_BIT);

	// 2 - PCLKSEL = /4 = 25MHz = PCLK_UART0
	PCLKSEL0 &= ~(0x03 << UART_PCLK_BIT);
	PCLKSEL0 |= (UART_PCLK_DIV << UART_PCLK_BIT);

	// 3 - Registros de la UART

	// Configuracion del baudrate
	// baudrate = PCLK_UART0 / (16 * DIV)
	// En nuestro caso, con DIV = 162 ==> baudrate = 9600
	// La cuenta exacta da: baudrate = 9645
	// Ponemos DLAB = 1
	UART0LCR |= (1 << 7);

	// Escribir el divisor en 162
	// Most Significant Nibble <- xxxx | xxxx -> Least Significant Nibble
	// Most Significant Byte <- xxxxxxxx | xxxxxxxx -> Least Significant Byte
	UART0DLM = 0;
	UART0DLL = 162;

	// Largo de 8 bits:
	UART0LCR &= ~(0x03 << 0);
	UART0LCR |= (0x03 << 0);

	// Bits de stop (1):
	UART0LCR &= ~(1 << 2);

	// Sin paridad:
	UART0LCR &= ~(1 << 3);

	// 4 - Seleccion de funcion de pines
	PINSEL_set_selection(0, 2, 1); // Tx
	PINSEL_set_selection(0, 3, 1); // Rx

	// 5 - Habilitacion de interrupciones en el periferico y en el NVIC

	// Ponemos DLAB = 0
	UART0LCR &= ~(1 << 7);

	// Habilitamos interrupciones del periferico
	UART0IER |= (1 << 0);

	// Habilitamos en el NVIC
	ISER0 |= (1 << 5);
}

void UART0_push_rx(uint8_t dato) {
	UART0_rx_buff[UART0_rx_in] = dato;

	UART0_rx_in++;

	if(UART0_rx_in == RX_BUFF_SIZE) {
		UART0_rx_in = 0;
	}
}

int32_t UART0_pop_tx(void) {
	if(UART0_tx_in == UART0_tx_out) {
		return -1;
	} else {
		int32_t ret = UART0_tx_buff[UART0_tx_out];

		UART0_tx_out++;

		if(UART0_tx_out == TX_BUFF_SIZE) {
			UART0_tx_out = 0;
		}

		return ret;
	}
}

void UART0_write_tx_reg(uint8_t dato) {
	UART0IER |= (1 << 1);
	UART0THR = dato;
}

void UART0_IRQHandler(void) {
	uint32_t int_pending;

	do {
		uint32_t reg_iir = UART0IIR;
		uint32_t interrupt_cause = (reg_iir >> 1) & 0x07;
		int_pending = (reg_iir & 0x01) ^ 0x01;

		/* Analizar interrupciones y accionar en consecuencia */
		switch(interrupt_cause) {
		case 0x03: { // RLS
			// TODO: Handle this
			break;
		}

		case 0x02: { // RDA
			UART0_push_rx(UART0RBR);
			break;
		}

		case 0x06: { // CTI
			// TODO: Handle this
			break;
		}

		case 0x01: { // THRE
			int32_t dato = UART0_pop_tx();

			if(dato != -1) {
				UART0_write_tx_reg(dato);
			} else {
				UART0_flag_tx = 0;
				UART0IER &= ~(1 << 1);
			}

			break;
		}
		}
	} while(int_pending);
}
