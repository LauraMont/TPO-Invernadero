/*******************************************************************************************************************************//**
 *
 * @file		${file_name}
 * @brief		Descripcion del modulo
 * @date		${date}
 * @author		Contiene los valores de referencia .Funciones que manejan los datos del proyecto
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Datos.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define	BAJO	1
#define T_BAJA	0
#define T_ALTA	1
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
static unsigned int N_AGUA = 0;			//Seria mejor usar defines para determinar el estado activo del sensor?
static unsigned int TEMPERATURA = 0;
static unsigned int HUMEDAD = 0;
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
 	\author
 	\date ${date}
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
**/
void Sys_Control()
{
	unsigned int N_AGUA_AUX = 0;
	unsigned int TEMPERATURA_AUX = 0;
	unsigned int HUMEDAD_AUX = 0;

	Pedir_Datos(&N_AGUA_AUX ,&TEMPERATURA_AUX,&HUMEDAD_AUX);
	if (N_AGUA_AUX == BAJO)		//Si el sensor no esta activado (no toca el agua)
	{
		//Podemos esperar unos segundos ,si sigue bajo cargo agua.
		//Este carga sin temporizador ,solo hasta que vuelva a activarse el sensor
	}
	if ( Comparo_Temperatura(TEMPERATURA_AUX) )
	{
		if (TEMPERATURA >= TEMPERATURA - 5) //Ejemplo : si la temperatura esta 5 °c mas que la referencia entro
		{
			//Dejo actuar el sys ventilacion x cantidad fija de tiempo previamente determinada
		}
		else if (TEMPERATURA_AUX <= TEMPERATURA - 5)
		{
			//Dejo actuar el sys iluminacion x cantidad fija de tiempo previamente determinada
		}
	}
	if (Comparo_Humedad(HUMEDAD_AUX))
	{
		//Como la comparacion ya me determino que esta por debajo de la necesaria
		//Riego una x cantidad de tiempo previamente determinada
	}
	Set_Valores(N_AGUA_AUX,TEMPERATURA_AUX,HUMEDAD_AUX);
}

void Set_Valores(unsigned int N_AGUA_AUX,unsigned int TEMPERATURA_AUX,unsigned int HUMEDAD_AUX)
{
	Set_N_Agua(N_AGUA_AUX);
	Set_Temperatura(TEMPERATURA_AUX);
	Set_Humedad(HUMEDAD_AUX);
}

void Pedir_Datos(unsigned int *N_AGUA_AUX,unsigned int* TEMPERATURA_AUX,unsigned int* HUMEDAD_AUX)
{
	* N_AGUA_AUX = Get_N_agua();
	* TEMPERATURA_AUX = Get_Temperatura();
	* HUMEDAD_AUX = Get_Humedad();
}

void Cargar_Datos_Referencia()			//Ingreso los datos de la base de datos de la planta
{

}
int Comparo_Temperatura(unsigned int TEMPERATURA_AUX)
{
	int status = 0;
	if ( (TEMPERATURA >= TEMPERATURA - 5) || (TEMPERATURA >= TEMPERATURA - 5 )) status = 1;
	return status;
}
int Comparo_Humedad(unsigned int HUMEDAD_AUX)
{

}
