/*******************************************************************************************************************************//**
 *
 * @file		DR_Entradas.c
 * @brief		Descripcion del modulo
 * @date		6 dic. 2020
 * @author		Nicolas Taurozzi
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Entradas.h"

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
volatile uint8_t BufferEntradas_Dig = 0;

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
	\fn  		InitDigIN
	\brief		Inicializacion de las entradas digitales
 	\author 	Nicolas Taurozzi
 	\date 6 	dic. 2020
	\return 	No hay retorno
*/
void InitDigIN(void)
{
	SetDIR(D_IN0, ENTRADA);
}

/**
	\fn  		InitDigIN
	\brief		Debounce de las entradas digitales
 	\author 	Nicolas Taurozzi
 	\date 6 	dic. 2020
	\return 	No hay retorno
*/
void DebounceEntradas (void)
{
	static uint8_t ContadorEntradas_Dig[MAX_ENTRADAS] = {0};
	uint8_t in = 0, x;
	uint8_t i;

	if ( GetPIN( D_IN0 , ALTO) )
		in = 1;

	x = in ^ BufferEntradas_Dig;

	if ( !x )
	{
		for ( i=0 ; i < MAX_ENTRADAS ; i++ )
			ContadorEntradas_Dig[i] = 0;
	}
	else
	{
		for ( i=0 ; i<MAX_ENTRADAS ; i++ )
		{
			if ( x & (1<<i) )
			{
				ContadorEntradas_Dig[i]++;
				if ( ContadorEntradas_Dig[i] >= REBOTES )
						BufferEntradas_Dig = BufferEntradas_Dig ^ (1<<i);
			}
			else
				ContadorEntradas_Dig[i] = 0;
		}
	}
}

