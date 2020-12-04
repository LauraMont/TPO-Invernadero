/*******************************************************************************************************************************//**
 *
 * @file		DR_UART0.c
 * @brief		Contiene las definiciones de las funciones del modulo
 * @date		23 nov. 2020
 * @author		Taurozzi, Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_UART0.h"

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint8_t UART0_rx_buff[RX_BUFF_SIZE];
volatile uint32_t UART0_rx_in, UART0_rx_out;

volatile uint8_t UART0_tx_buff[TX_BUFF_SIZE];
volatile uint32_t UART0_tx_in, UART0_tx_out;

volatile uint8_t UART0_flag_tx;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/**
	\fn    	void UART0_init(void)
	\brief  Inicializacion del UART0
 	\author Nicolás Taurozzi
 	\date   23/11/2020
	\return No hay retorno
*/
void UART0_init(void)
{
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
	SetPINSEL(0, 2, 1); // Tx
	SetPINSEL(0, 3, 1); // Rx

	// 5 - Habilitacion de interrupciones en el periferico y en el NVIC

	// Ponemos DLAB = 0
	UART0LCR &= ~(1 << 7);

	// Habilitamos interrupciones del periferico
	UART0IER |= (1 << 0);

	// Habilitamos en el NVIC
	ISER0 |= (1 << 5);
}

/**
	\fn    	void UART0_push_rx(uint8_t dato)
	\brief  Guarda en el vector de recepcion un dato
 	\author Nicolás Taurozzi
 	\date   23/11/2020
 	\param  [in] uint8_t dato: dato a guardar en el vector de recepcion
	\return No hay retorno
*/
void UART0_push_rx(uint8_t dato)
{
	UART0_rx_buff[UART0_rx_in] = dato;

	UART0_rx_in++;

	if(UART0_rx_in == RX_BUFF_SIZE) {
		UART0_rx_in = 0;
	}
}

/**
	\fn    	int32_t UART0_pop_tx(void)
	\brief  Saca un dato del vector de transmision
 	\author Nicolás Taurozzi
 	\date   23/11/2020
	\return int32_t ret: valor que saco del vector de transmision
*/
int32_t UART0_pop_tx(void)
{
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

/**
	\fn    	void UART0_write_tx_reg(uint8_t dato)
	\brief  Fuerza la transmision de un dato
 	\author Nicolás Taurozzi
 	\date   23/11/2020
 	\param  [in] uint8_t dato: dato a transmitir
	\return No hay retorno
*/
void UART0_write_tx_reg(uint8_t dato)
{
	UART0IER |= (1 << 1);
	UART0THR = dato;
}


/**
	\fn    	void UART0_IRQHandler(void)
	\brief  Handler de las interrupciones
 	\author Nicolás Taurozzi
 	\date   23/11/2020
	\return No hay retorno
*/
void UART0_IRQHandler(void)
{
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
