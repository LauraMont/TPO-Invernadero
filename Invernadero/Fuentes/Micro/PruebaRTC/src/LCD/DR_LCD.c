/*******************************************************************************************************************************//**
 *
 * @file		DR_LCD.c
 * @brief		Descripcion del modulo
 * @date		22 nov. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_LCD.h"

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
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 22 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/


void Config_LCD (void)
{
	unsigned int i;

	SetPIN(EN,OFF); Demora_LCD = 10;

	while(Demora_LCD);//Demora Inicial

	for(i=0 ; i<3; i++)
	{
		//Configuración en 8 bits
		SetPIN(d4,ON); SetPIN(d5,ON);
		SetPIN(d6,OFF); SetPIN(d7,OFF);
		SetPIN(RS,OFF);
		SetPIN(EN,ON); SetPIN(d5,OFF);

		Demora_LCD = 2;
		while(Demora_LCD);
	}

	//Configuración en 4 bits
	SetPIN(d4,OFF); SetPIN(d5,ON);
	SetPIN(d6,OFF); SetPIN(d7,OFF);
	SetPIN(RS,OFF);
	SetPIN(EN,ON); SetPIN(d5,OFF);

	Demora_LCD = 1;
	while(Demora_LCD);

	//A partir de aca el LCD pasa a 4 bits !!!
	//DL = 0: 4 bits de datos -N = 1: 2 lineas - F = 0: 5x7 puntos
	PushLCD(0x28, LCD_CONTROL);

	//D = 0: display OFF - C=0: Cursos OFF - B=0: Blink OFF
	PushLCD(0x08, LCD_CONTROL);

	//Clear Display
	PushLCD(0x01, LCD_CONTROL);

	//I/D=1: Incrementa puntero - S=0: NO Shift Display
	PushLCD(0x06, LCD_CONTROL);

	//Activo el LCD y listo para usar !
	//D=1: display ON - C=0: Cursor OFF - B=0: Blink OFF
	PushLCD(0x0c, LCD_CONTROL);

}


uint8_t PushLCD(uint8_t dato, uint8_t control)
{
	if(cantidadColaLCD >= TOP_BUFFER_LCD)
		return -1;

	Buffer_LCD[inxInLCD] = (dato >> 4) & 0x0f;
	if(control == LCD_CONTROL)
		Buffer_LCD[inxInLCD] |= 0x80;

	inxInLCD++;

	Buffer_LCD[inxInLCD] = dato & 0x0f;
	if(control == LCD_CONTROL)
		Buffer_LCD[inxInLCD] |= 0x80;

	cantidadColaLCD += 2;

	inxInLCD++;
	inxInLCd %= TOPE_BUFFER_LCD;

	return 0;
}

int PopLCD(void)
{
	int8_t dato;

	if(cantidadColaLCD == 0)
		return -1;

	dato = Buffer_LCD[inxOutLCD];

	cantidadColaLCD --;

	inxOutLCd++;
	inxOutLCd %= TOPE_BUFFER_LCD;

	return dato;
}


void Dato_LCD(void)
{
	int32_t data;

	if((data = PopLCD()) == -1)
		return;

	SetPIN(d4, ((uint8_t) data)) >> 3 & 0x01);
	SetPIN(d5, ((uint8_t) data)) >> 2 & 0x01);
	SetPIN(d6, ((uint8_t) data)) >> 1 & 0x01);
	SetPIN(d7, ((uint8_t) data)) >> 0 & 0x01);

	if( ((uint8_t) data) & 0x80)
		SetPIN(RS, OFF);
	else
		SetPIN(RS,ON);

	SetPIN(EN,ON);
	SetPIN(EN,OFF);
}





















