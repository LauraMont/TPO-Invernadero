/*
 * DR_GPIO.c
 *
 *  Created on: Sep 12, 2019
 *      Author: augusto
 */

#include "DR_tipos.h"
#include "DR_GPIO.h"

typedef struct {
	uint32_t FIODIR;
}FIODIR_reg_t;

typedef struct {
	uint32_t FIOSET;
}FIOSET_reg_t;

typedef struct {
	uint32_t FIOCLR;
}FIOCLR_reg_t;

typedef struct {
	uint32_t FIOPIN;
}FIOPIN_reg_t;

typedef struct {
	uint32_t FIOMASK;
}FIOMASK_reg_t;

typedef struct {
	FIODIR_reg_t FIODIR;
	uint32_t RESERVED_1[3];
	FIOMASK_reg_t FIOMASK;
	FIOPIN_reg_t FIOPIN;
	FIOSET_reg_t FIOSET;
	FIOCLR_reg_t FIOCLR;
}GPIO_per_t;

#define		GPIO0_BASE		((GPIO_per_t *)(0x2009C000))
#define		GPIO1_BASE		((GPIO_per_t *)(0x2009C020))
#define		GPIO2_BASE		((GPIO_per_t *)(0x2009C040))
#define		GPIO3_BASE		((GPIO_per_t *)(0x2009C060))
#define		GPIO4_BASE		((GPIO_per_t *)(0x2009C080))

static GPIO_per_t *GPIO[] = {
		GPIO0_BASE,
		GPIO1_BASE,
		GPIO2_BASE,
		GPIO3_BASE,
		GPIO4_BASE
};

void GPIO_set_dir(uint8_t port, uint8_t pin, uint8_t dir) {
	if(dir)
	{
		dir = 1;
	}

	GPIO[port]->FIODIR.FIODIR &= ~(1 << pin);
	GPIO[port]->FIODIR.FIODIR |= (dir << pin);
}

void GPIO_set_pin(uint8_t port, uint8_t pin) {
	GPIO[port]->FIOSET.FIOSET |= (1 << pin);
}

void GPIO_clear_pin(uint8_t port, uint8_t pin) {
	GPIO[port]->FIOCLR.FIOCLR |= (1 << pin);
}

void GPIO_toggle_pin(uint8_t port, uint8_t pin) {
	GPIO[port]->FIOPIN.FIOPIN ^= (1 << pin);
}

uint8_t GPIO_read_pin(uint8_t port, uint8_t pin) {
	return (GPIO[port]->FIOPIN.FIOPIN & (1 << pin)) >> pin;
}
