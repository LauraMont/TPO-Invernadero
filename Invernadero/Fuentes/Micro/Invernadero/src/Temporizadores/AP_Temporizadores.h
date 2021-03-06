/*******************************************************************************************************************************//**
 *
 * @file		AP_Temporizadores.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		18 sep. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef TEMPORIZADORES_AP_TEMPORIZADORES_H_
#define TEMPORIZADORES_AP_TEMPORIZADORES_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	MEDICION_TIME_SEG   1
#define 	VALVULA_TIME_SEG 	3
#define		ESPERA_TIME_SEG 	10
#define		ALARMA_TIME_SEG 	10
#define		RX_TIMEOUT_MSECS	50
#define		ERR_TIMEOUT_MSECS	250
#define		DATOS_TIMEOUT_SECS	5
#define		MOSTRAR_ESTADO_SEG  1

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef enum
{
	TM_MEDICION = 0,
	TM_VALVULA,
	TM_ESPERA,
	TM_ALARMA,
	TIMER_ID_RX,
	TIMER_ID_ERR,
	TIMER_ID_DATOS,
	TM_BUZZER,
	TM_MOSTAR_ESTADO
} Timers_ID;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t	fEventoTiempo_1 ;
extern uint8_t	fEventoTiempo_2 ;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Ev_Estado1 ( void );
void Ev_Display ( void );
void Ev_Buzzer(void);

#endif /* TEMPORIZADORES_AP_TEMPORIZADORES_H_ */
