/*******************************************************************************************************************************//**
 *
 * @file		rx_trama.h
 * @brief		Contiene protoptipos, includes y defines del modulo
 * @date		23 nov. 2020
 * @author		Nicolas Taurozzi
 *
 **********************************************************************************************************************************/

#ifndef RX_TRAMA_H_
#define RX_TRAMA_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "PR_UART0.h"
#include "PR_Temporizadores.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		START_CHAR			('$')
#define		END_CHAR			('#')

#define		TIMER_ID_RX			(0)
#define		RX_TIMEOUT_MSECS	(50)

#define		TIMER_ID_ERR		(1)
#define		ERR_TIMEOUT_MSECS	(250)

#define		TIMER_ID_DATOS		(2)
#define		DATOS_TIMEOUT_SECS	(5)

#define		DATA_BUFFER_SIZE	(8)
#define 	DATOS_BUFFER_SIZE	(4)

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef enum {
	RX_TRAMA_RESET = 0,
	WAITING_START,
	WAITING_DATA,
	WAITING_END,
	RX_TRAMA_ERROR
} rx_trama_state_en;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
void rx_trama_MDE(void);

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
rx_trama_state_en rx_trama_current_state(void);

uint32_t get_temp_min(void);
uint32_t get_temp_max(void);
uint32_t get_riego(void);

static void restart_rx_timeout(void);
static void stop_rx_timeout(void);

static void start_rx_timeout(void);
static void rx_timeout_callback(void);

static void start_err_timeout(void);
static void err_timeout_callback(void);

static void start_datos_timeout(void);
static void datos_timeout_callback(void);
static void stop_datos_timeout(void);

static void err_func(void);

static void update_datos(void);				//Funcion que actualiza los datos a enviar

static uint32_t get_humedad(void);				//Funcion que regresará los valores medidos
static uint32_t get_temp(void);					//Funcion que regresará los valores medidos

static int32_t check_if_data_valid(int32_t dato_rx);
#endif /* RX_TRAMA_H_ */
