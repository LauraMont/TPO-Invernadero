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
#include "PR_Temporizadores.h"
#include "DR_LCD.h"
#include "DR_Teclado.h"
#include "DR_Display.h"
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
extern uint8_t	Demora_LCD;
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
	STRELOAD = ( STCALIB / 4 )-1;//Cuento cada una milésima
	STCURR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;
}

void SysTick_Handler(void)
{
	TimerDescount ( );
	TecladoSW();
	BarridoDisplay();
	if(Demora_LCD)
				Demora_LCD--;

	Dato_LCD();
}
