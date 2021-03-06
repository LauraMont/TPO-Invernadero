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
#include "Aplicacion.h"
#include "PR_UART0.h"
#include "PR_Temporizadores.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		START_CHAR				('$')
#define		END_CHAR				('#')

#define 	INICIAR					(1)
#define		FINALIZAR				(2)

#define		DATA_BUFFER_RX_SIZE		(15)
#define 	DATA_BUFNAME_SIZE		(35)
#define 	DATA_BUFFER_TX_SIZE		(6)

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

typedef enum {
	RX_TRAMA_RESET = 0,
	WAITING_START,
	COMANDO,
	DETENER,
	WAITING_DATA,
	WAITING_NAME,
	WAITING_END,
	RX_TRAMA_ERROR
} rx_trama_state_en;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
uint8_t rx_trama_MDE(void);

rx_trama_state_en rx_trama_current_state(void);

uint32_t get_temp_min(void);
uint32_t get_temp_max(void);
uint32_t get_suministro(void);
uint32_t get_hum_amb(void);
uint32_t get_hum_tierra(void);
void get_name(char * name);
void EnviarDatos(void);

#endif /* RX_TRAMA_H_ */
