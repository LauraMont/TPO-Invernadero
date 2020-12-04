/*******************************************************************************************************************************//**
 *
 * @file		DR_Teclado.c
 * @brief		Descripcion del modulo
 * @date		23 nov. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Teclado.h"

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
volatile uint8_t tecla = NO_KEY;

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
 	\date 23 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
#include "DR_Teclado.h"

void InicializarTeclado(void)
{
	SetDIR(Tecla_1, ENTRADA);
	SetDIR(Tecla_2, ENTRADA);
	SetDIR(Tecla_3, ENTRADA);
	SetDIR(Tecla_4, ENTRADA);
	SetDIR(Tecla_5, ENTRADA);
}

/** @fn void DriverTecladoSW (  void )
 * @brief Elimina el rebote de la tecla pulsada
 * @details Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> REBOTES: Cantidad de veces que se cuenta un cambio de estado para darlo por valido
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		</ul>
 * @param 	void.
 * @return	void.
 */
void TecladoSW (void)
{
	    static uint8_t CodigoAnterior = NO_KEY;
		static uint8_t EstadosEstables = 0;
		uint8_t CodigoActual;

		CodigoActual = TecladoHW();

		if( CodigoActual == NO_KEY )
		{
			CodigoAnterior = NO_KEY;
			EstadosEstables = 0;
			return;
		}

		if( EstadosEstables == 0)
		{
			CodigoAnterior = CodigoActual;
			EstadosEstables = 1;
			return;
		}

		if( EstadosEstables == REBOTES )
		{
			EstadosEstables = REBOTES + 1;
			tecla = CodigoAnterior;
			return;
		}

		if( EstadosEstables > REBOTES )
			return;

		if( CodigoActual == CodigoAnterior )
			EstadosEstables ++;
		else
			EstadosEstables = 0;

		return;
}

uint8_t TecladoHW(void)
{
	if (GetPIN(Tecla_1,BAJO)) return 1;
	if (GetPIN(Tecla_2,BAJO)) return 2;
	if (GetPIN(Tecla_3,BAJO)) return 3;
	if (GetPIN(Tecla_4,BAJO)) return 4;
	if (GetPIN(Tecla_5,BAJO)) return 5;

	return NO_KEY;
}

