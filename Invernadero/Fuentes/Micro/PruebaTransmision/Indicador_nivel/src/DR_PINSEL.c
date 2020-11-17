/*
 * DR_PINSEL.c
 *
 *  Created on: Sep 12, 2019
 *      Author: augusto
 */


#include "DR_tipos.h"
#include "DR_PINSEL.h"

#define		PINSEL_BASE		((uint32_t *)(0x4002C000))
#define		PINMODE_BASE	((uint32_t *)(0x4002C040))

void PINSEL_set_selection(uint8_t port, uint8_t pin, uint8_t selection) {
	if(selection > 0x03) {
		selection = 0;
	}

	PINSEL_BASE[(port * 2) + (pin / 16)] &= ~(0x03 << ((pin % 16) * 2));
	PINSEL_BASE[(port * 2) + (pin / 16)] |= (selection << ((pin % 16) * 2));
}

void PINMODE_set_selection(uint8_t port, uint8_t pin, uint8_t selection) {
	if(selection > 0x03) {
		selection = 0;
	}

	PINMODE_BASE[(port * 2) + (pin / 16)] &= ~(0x03 << ((pin % 16) * 2));
	PINMODE_BASE[(port * 2) + (pin / 16)] |= (selection << ((pin % 16) * 2));
}
