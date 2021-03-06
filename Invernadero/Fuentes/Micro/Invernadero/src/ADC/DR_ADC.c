/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC.c
 * @brief		Descripcion del modulo
 * @date		23 nov. 2020
 * @author		Taurozzi, Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_ADC.h"

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
static volatile ADC_per_t *ADC = ADC_BASE;

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
	\fn  	void ADC_init(void)
	\brief 	Inicializa el ADC
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/

void ADC_init(void)
{
	PCONP |= (1 << 12);

	// div_PCLKSEL
	PCLKSEL0 &= ~(0x03 << 24);

	ADC->ADCR.PDN = 1;

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

/**
	\fn  	void ADC_start_conversion(void)
	\brief 	Inicia las conversiones del ADC
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void ADC_start_conversion(void)
{
	ADC->ADCR.START = 1;
}

/**
	\fn  	uint32_t ADC_get_average(void)
	\brief 	Toma el promedio de las cuentas del ADC
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return uint32_t ADC_average: Promedio de las mediciones del ADC
*/
uint32_t ADC_get_average(void)
{
	return ADC_average;
}

/**
	\fn  	void ADC_IRQHandler(void)
	\brief 	Handler de las interrupciones
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
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

/**
	\fn  	TimeADC
	\brief 	Contador para iniciar cada medicion del ADC
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void TimeADC(void)
{
	static uint32_t adc_counter = 0;

	adc_counter++;
	adc_counter %= 10;//Cantidad de ms

	if(!adc_counter)
	{
		ADC_start_conversion();
	}
}
