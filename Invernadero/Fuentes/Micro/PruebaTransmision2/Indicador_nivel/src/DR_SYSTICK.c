/*
 * DR_SYSTICK.c
 *
 *  Created on: Sep 20, 2019
 *      Author: augusto
 */

#include "DR_tipos.h"
#include "DR_SYSTICK.h"

#include "DR_timer.h"

#define	SYSTICK_BASE	0xE000E000 //!< Base del periferico SYSTICK

typedef struct {
	uint32_t RESERVED;
}SYSTICK_RESERVED_reg_t;

typedef struct {
	uint32_t ENABLE : 1;
	uint32_t TICKINT : 1;
	uint32_t CLKSOURCE : 1;
	uint32_t RESERVED_1 : 13;
	uint32_t COUNTFLAG : 1;
	uint32_t RESERVED_2 : 15;
}SYSTICK_CSR_reg_t;

typedef struct {
	uint32_t RELOAD : 23;
	uint32_t RESERVED : 9;
}SYSTICK_RVR_reg_t;

typedef struct {
	uint32_t CURRENT : 23;
	uint32_t RESERVED : 9;
}SYSTICK_CVR_reg_t;

typedef struct {
	uint32_t TENMS : 23;
	uint32_t RESERVED : 7;
	uint32_t SKEW : 1;
	uint32_t NOREF : 1;
}SYSTICK_CALIB_reg_t;

typedef struct {
	volatile SYSTICK_RESERVED_reg_t RESERVED[4];
	volatile SYSTICK_CSR_reg_t CSR;
	volatile SYSTICK_RVR_reg_t RVR;
	volatile SYSTICK_CVR_reg_t CVR;
	volatile SYSTICK_CALIB_reg_t CALIB;
}SYSTICK_reg_t;

static volatile SYSTICK_reg_t * const SYSTICK = (SYSTICK_reg_t *) SYSTICK_BASE; //!< Periferico SYSTICK

void SYSTICK_init(void) {
	SYSTICK->RVR.RELOAD = SYSTICK->CALIB.TENMS / 10; // 1mseg
	SYSTICK->RVR.RESERVED = 0;

	// Fijo el clock del systick como el clock de la CPU directamente
	SYSTICK->CSR.CLKSOURCE = 1;

	SYSTICK->CVR.CURRENT = 0x00; // Limpio current value

	// Habilito clock del systick
	SYSTICK->CSR.ENABLE = 1;

	// Habilito interrupcion de systick
	SYSTICK->CSR.TICKINT = 1;
}

void SysTick_Handler(void) {
	timer_discount();
}
