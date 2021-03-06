/*******************************************************************************************************************************//**
 *
 * @file		AP_funciones.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		23 nov. 2020
 * @author		Nicolas Taurozzi
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef APLICACION_AP_FUNCIONES_H_
#define APLICACION_AP_FUNCIONES_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Aplicacion.h"

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
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Inicializar(void);
void LeerTeclado(void);
void ApagarLuces(void);
void Medir(void);
void Alarma(uint8_t modo);

#endif /* APLICACION_AP_FUNCIONES_H_ */
