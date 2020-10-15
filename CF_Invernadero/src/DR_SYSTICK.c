/*
 * DR_SYSTICK.c
 *
 *  Created on: Sep 4, 2020
 *      Author: augusto
 */

#include "DR_tipos.h"
#include "DR_SYSTICK.h"

typedef struct
{
	uint32_t ENABLE : 1;
	uint32_t TICKINT : 1;
	uint32_t CLKSOURCE : 1;
	uint32_t : 13;
	uint32_t COUNTFLAG : 1;
	uint32_t : 15;
}STCTRL_t;

typedef struct
{
	__RW STCTRL_t STCTRL;
	__RW uint32_t STRELOAD;
	__RW uint32_t STCURR;
	__R uint32_t STCALIB;
}SYSTICK_t;

#define		SYSTICK		((SYSTICK_t*) 0xE000E010UL)

/**
 * \brief Inicializacion del systick cada 10mseg
 * Es necesario tener inicializado el PLL
 */
void Inicializar_systick(void)
{
	SYSTICK->STRELOAD = SYSTICK->STCALIB;
	SYSTICK->STCTRL.CLKSOURCE = 1; // Clock interno
	SYSTICK->STCURR = 0;
	SYSTICK->STCTRL.TICKINT = 1;
	SYSTICK->STCTRL.ENABLE = 1;
}

static uint32_t contador = 0;

uint32_t get_ticks(void)
{
	return contador;
}

void reset_ticks(void)
{
	contador = 0;
}

/**
 * \brief Interrupcion de Systick cada 10msegs
 */
void SysTick_Handler(void)
{
	contador++;
}
