/*
 * DR_ADC.c
 *
 *  Created on: 11 oct. 2020
 *      Author: nico
 */

#include "DR_ADC.h"
void ADC_init(void)
{
	PCONP |= (1 << 12);

	// div_PCLKSEL
	PCLKSEL0 &= ~(0x03 << 24);

	ADC->ADCR.PDN = 1;

//	PINSEL_set_selection(1, 31, 3);
	SetPINSEL(0,25,1); //Leer entrada
//	SetPINSEL(1,31,3); //Potenciometro
	ADC->ADCR.START = 0;

	// f_ADC = (f_CPU / div_PCLKSEL) / ((div_ADC + 1) * 65) = 192KHz
	ADC->ADCR.CLKDIV = 1;

	ADC->ADCR.SEL = (1 << 2);

	ADC->ADINTEN.ADINTEN0 = 0;
	ADC->ADINTEN.ADINTEN1 = 0;
	ADC->ADINTEN.ADINTEN2 = 1;
	ADC->ADINTEN.ADINTEN3 = 0;
	ADC->ADINTEN.ADINTEN4 = 0;
	ADC->ADINTEN.ADINTEN5 = 0;
	ADC->ADINTEN.ADINTEN6 = 0;
	ADC->ADINTEN.ADINTEN7 = 0;
	ADC->ADINTEN.ADGINTEN = 0;

	ISER0 |= (1 << 22);
}

void ADC_start_conversion(void)
{
	ADC->ADCR.START = 1;
}

uint32_t ADC_get_average(void)
{
	return ADC_average;
}

void ADC_IRQHandler(void)
{
	static uint32_t acummulator = 0;

	ADDR_reg_t ADDR2 = ADC->ADDR[2];

	ADC_buffer[ADC_buffer_index] = ADDR2.RESULT;
	acummulator += ADC_buffer[ADC_buffer_index];

	ADC_buffer_index++;
	ADC_buffer_index %= ADC_BUFF_SIZE;

	if(!ADC_buffer_index)
	{
		ADC_average = acummulator / ADC_BUFF_SIZE;
		acummulator = 0;
	}
}

