/*
 * DR_LCD.h
 *
 *  Created on: Nov 9, 2020
 *      Author: USER
 */

#ifndef SRC_DRIVERINFOTRONIC_DR_LCD_H_
#define SRC_DRIVERINFOTRONIC_DR_LCD_H_


/*******************************************************************************************************************************//**
 *
 * @file		DR_LCD.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Nov 9, 2020
 * @author		
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_GPIO.h"
#include "PR_LCD.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

//GPIOS LCD:
#define     PORT0       0
#define     PORT1       1
#define     PORT2       2
#define     PORT3       3
#define		LCD_D4		PORT0,5			//GPIO0
#define		LCD_D5		PORT0,10		//GPIO0
#define		LCD_D6		PORT2,4			//GPIO2
#define		LCD_D7		PORT2,5			//GPIO2
#define		LCD_RS		PORT2,6			//GPIO2
#define		LCD_BF		PORT0,28		//GPIO1
#define		LCD_E		PORT0,4			//GPIO0
#define		LCD_E_OFF				SetPIN(LCD_E,0)
#define		LCD_E_ON				SetPIN(LCD_E,1)
#define		LCD_RS_OFF				SetPIN(LCD_RS,0)
#define		LCD_RS_ON				SetPIN(LCD_RS,1)
#define		LCD_DATO(d4,d5,d6,d7)	SetPIN(LCD_D4,d4);SetPIN(LCD_D5,d5);SetPIN(LCD_D6,d6);SetPIN(LCD_D7,d7)

#define     TOPE_BUFFER_LCD        100

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;
extern uint8_t Buffer_LCD[TOPE_BUFFER_LCD]; /*!< Buffer de datos relacionados con el LCD*/
extern uint8_t inxOutLCD; /*!< Indice de output del LCD (Capa drivers)*/
extern uint8_t inxInLCD; /*!< Indice de input del LCD (Capa primitivas)*/
extern uint8_t cantidadColaLCD; /*!< Cantidad de datos que faltan convertir del buffer del LCD*/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InitLCD ( void );
void Dato_LCD( void );
void InitLCD ( void );
void Dato_LCD ( void );
int16_t PopLCD ( void );
int8_t PushLCD ( uint8_t , uint8_t );
void Display_LCD( char *, char, char);
void GuardarMensajeLCD( char *, char * );



#endif /* SRC_DRIVERINFOTRONIC_DR_LCD_H_ */
