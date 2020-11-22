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

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t	fEventoTiempo_1 ;
extern uint8_t	fEventoTiempo_2 ;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Ev_Relay0 (void);

void Ev_Estado1 ( void );
void Ev_Estado2 ( void );
void Ev_Display ( void );



#endif /* TEMPORIZADORES_AP_TEMPORIZADORES_H_ */
