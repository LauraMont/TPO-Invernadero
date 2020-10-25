/*******************************************************************************************************************************//**
 *
 * @file		PR_Temporizadores.c
 * @brief		Descripcion del modulo
 * @date		18 sep. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_Temporizadores.h"

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
uint32_t TmrRun[ TEMPORIZADORES ];
void (*TmrFunciones[ TEMPORIZADORES ])(void);
uint8_t TmrFlag[ TEMPORIZADORES ];
uint8_t TmrPause[ TEMPORIZADORES ];
uint8_t TmrBase[ TEMPORIZADORES ];

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


int8_t TimerStart ( uint8_t ev , uint32_t t , void (* f_ev )(void), uint8_t base )
{
	int8_t salida = 0 ;

	switch ( base )
	{
		case MIL: TmrRun[ ev ] = MILECIMA * t; break;

		case DEC: TmrRun[ ev ] = MILECIMA * DECIMA * t; break;

		case SEG: TmrRun[ ev ] = MILECIMA * DECIMA * SEGUNDO * t; break;

		case MIN: TmrRun[ ev ] = MILECIMA * DECIMA * SEGUNDO * MINUTO * t; break;

		default: salida = -1; break;
	}

	TmrFunciones[ ev ] = f_ev;
	TmrBase[ ev ] = base;

	return salida;
}

void TimerDescount ( void )
{
	int i;
	for ( i = 0 ; i < TEMPORIZADORES ; i ++)
	{
		if ( TmrRun[ i ] )
		{
			if ( !TmrPause [ i ] ) // RUN = 0
			{
				TmrRun[ i ] --;
				if (!TmrRun[ i ])
					TmrFlag[ i ] = 1;
			}
		}
	}
}

void TimerEvent ( void )
{
	uint8_t i;

	for ( i = 0 ; i < TEMPORIZADORES ; i ++)
	{
		if (TmrFlag[ i ])
		{
			TmrFlag[ i ] = 0;
			TmrFunciones[ i ]();
		}
	}
}


int8_t TimerPause ( uint8_t ev , uint8_t modo )
{
	int8_t salida = 0;

	if ( ev < TEMPORIZADORES )
	{
		TmrPause [ ev ] = modo;
		salida = -1;
	}
	return salida;
}


int8_t TimerGet ( uint8_t ev , uint32_t *t )
{
	int8_t salida = - 1;

	if ( ev < TEMPORIZADORES && TmrRun[ ev ])
	{
		salida = 0;

		switch ( TmrBase[ ev ] )
		{
			case DEC: *t = TmrRun[ ev ] / DECIMA ; break;

			case SEG: *t = TmrRun[ ev ] / DECIMA / SEGUNDO; break;

			case MIN: *t = TmrRun[ ev ] / DECIMA  / SEGUNDO / MINUTO; break;
		}
	}

	return salida;
}

int8_t TimerSet ( uint8_t ev , uint32_t t )
{
	int8_t salida = - 1;

	if ( ev < TEMPORIZADORES && TmrRun[ ev ] )
	{
		salida = 0;

		switch ( TmrBase[ ev ] )
		{
			case DEC: TmrRun[ ev ] = t * DECIMA ; break;

			case SEG: TmrRun[ ev ] = t * DECIMA * SEGUNDO; break;

			case MIN: TmrRun[ ev ] = t * DECIMA  * SEGUNDO * MINUTO; break;
		}
	}

	return salida;
}

int8_t TimerStop ( uint8_t ev  )
{
	int8_t salida = -1;

	if ( ev < TEMPORIZADORES )
	{
		TmrRun[ ev ] = 0;
		TmrFlag[ ev ] = 0;
		TmrFunciones[ ev ] = (void *) 0;
		salida = 0;
	}
	return salida;
}

void TimerClose ( void )
{
	uint8_t i;

	for( i = 0 ; i < TEMPORIZADORES ; i ++ )
		TimerStop ( i  );
	return ;
}

