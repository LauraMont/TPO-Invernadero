/*******************************************************************************************************************************//**
 *
 * @file		AP_Temporizadores.c
 * @brief		Descripcion del modulo
 * @date		18 sep. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <GPIO/DR_GPIO.h>
#include <PR_BME280.h>
#include "AP_Temporizadores.h"
#include "AP_funciones.h"
#include "PR_Temporizadores.h"
#include "Infotronic.h"

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
uint8_t	fEventoTiempo_2 = 0 ;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 18 sep. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/

void Ev_Relay0 (void)
{
	static uint8_t modulo = 0;

//	SetTOGGLE( RELAY0 );

	if ( modulo )
		TimerStart( 0 , 2 , Ev_Relay0 , SEG );
	else
		TimerStart( 0 , 5 , Ev_Relay0 , DEC );

	modulo ++;
	modulo %=2;
}


void Ev_Estado1 ( void )
{
	Medir();
}

void Ev_Display ( void )
{
	BarridoDisplay();
}


