/*******************************************************************************************************************************//**
 *
 * @file		DRUART0.h
 * @brief		Contiene protoptipos, includes y defines del modulo
 * @date		23 nov. 2020
 * @author		Nicolas Taurozzi
 *
 **********************************************************************************************************************************/
#ifndef DRIVERLPC_DR_UART0_H_
#define DRIVERLPC_DR_UART0_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	RX_BUFF_SIZE		64
#define 	TX_BUFF_SIZE		64

#define		DIR_UART0		( ( __RW uint32_t  * ) 0x4000C000UL )

#define		UART0RBR		DIR_UART0[0]	// Registro de Recepción RBR
#define		UART0THR		DIR_UART0[0]	// Registro de Transmisión THR
#define		UART0DLL		DIR_UART0[0]	// Parte baja del divisor de la UART0:
#define		UART0IER		DIR_UART0[1]	// Registro de Habilitación de interrupciones de la UART0:
#define		UART0DLM		DIR_UART0[1]	// Parte Alta del divisor de la UART0:
#define		UART0IIR		DIR_UART0[2]	// Registro de Identificación de interrupciones de la UART0:
#define		UART0LCR		DIR_UART0[3]	// Line CONTROL Register de la UART0:
#define		UART0LSR		DIR_UART0[5]	// Line STATUS Register de la UART0:

#define		UART_PCON_BIT		(3)
#define		UART_PCLK_BIT		(6)
#define		UART_PCLK_DIV		(0x00)
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define		UART0DLAB_OFF	(U0LCR & 0xEF)
#define		UART0DLAB_ON	(U0LCR | 0x80)

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint8_t UART0_rx_buff[];
extern volatile uint32_t UART0_rx_in, UART0_rx_out;

extern volatile uint8_t UART0_tx_buff[];
extern volatile uint32_t UART0_tx_in, UART0_tx_out;

extern volatile uint8_t UART0_flag_tx;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void UART0_init(void);
void UART0_push_rx(uint8_t dato);
int32_t UART0_pop_tx(void);
void UART0_write_tx_reg(uint8_t dato);

#endif /* DRIVERLPC_DR_UART0_H_ */
