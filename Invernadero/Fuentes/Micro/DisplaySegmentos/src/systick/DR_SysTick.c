/*******************************************************************************************************************************//**
 *
 * @file		DR_SysTick.c
 * @brief		Descripcion del modulo
 * @date		4 de may. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_SysTick.h"
#include "../Temporizadores/PR_Temporizadores.h"
#include "../ADC/DR_ADC.h"
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

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/** @fn void SysTickInic ( void )
 * @details Inicializacion del systick
 * @details No Portable
 * @param 	void
 * @return 	void.
 */
void InicializarSysTick ( void )
{
	STRELOAD = (STCALIB/10);//Cuento cada una milésima
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}

void SysTick_Handler(void)
{
	TimerDescount ( );
	static uint32_t adc_counter = 0;

	adc_counter++;
	adc_counter %= 10;

	if(!adc_counter)
	{
		ADC_start_conversion();
	}
}
