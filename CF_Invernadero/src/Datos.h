/*******************************************************************************************************************************//**
 *
 * @file		${file_name}
 * @brief
 * @date		${date}
 * @author
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DATOS_H_
#define DATOS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

#include "Sys_Iluminacion.h"
#include "Sys_Riego.h"
#include "Sys_Ventilacion.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

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

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void Cargar_Datos_Referencia();			//Ingreso los datos de la base de datos de la planta

bool Comparo_N_agua();					//La comparacion es con los valores de referencia
bool Comparo_Temperatura();
bool Comparo_Humedad();
void Set_Valores(unsigned int ,unsigned int,unsigned int);

void Pedir_Datos(unsigned int*,unsigned int*,unsigned int*);	//Pido los datos de las variables del proyecto
void Sys_Control();						//Comparo los datos de las variables del proyecto
#endif /* DATOS_H_ */
