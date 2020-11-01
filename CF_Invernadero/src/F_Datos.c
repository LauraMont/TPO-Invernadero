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
#include "F_Datos.h"
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
static uint32_t N_AGUA = 0;			//Seria mejor usar defines para determinar el estado activo del sensor?
static uint32_t TEMPERATURA = 0;
static uint32_t HUMEDAD_T = 0;
static uint32_t HUMEDAD_A = 0;
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
	uint32_t N_AGUA_AUX = 0;
	uint32_t TEMPERATURA_AUX = 0;
	uint32_t HUMEDAD_T_AUX = 0;
	uint32_t HUMEDAD_A_AUX = 0;

	Pedir_Datos(&N_AGUA_AUX ,&TEMPERATURA_AUX,&HUMEDAD_T_AUX ,&HUMEDAD_T_AUX);
	if (N_AGUA_AUX == BAJO)		//Si el sensor no esta activado (no toca el agua)
	{
		Led_ON();//Se enciende Led avisando que el nivel de agua esta bajo
	}
	else if(N_AGUA_AUX == ALTO)
	{
		Led_OFF();//Apagamos Led
	}

	if ( Comparo_Temperatura(TEMPERATURA_AUX) )
	{
		if (TEMPERATURA >= TEMPERATURA + 1) //Ejemplo : si la temperatura esta 1 °c mas que la referencia entro
		{
			Sys_Ventilacion();	//Dejo actuar el sys ventilacion x cantidad fija de tiempo previamente determinada
		}
		else if (TEMPERATURA_AUX <= TEMPERATURA - 1)
		{
			Sys_Iluminacion();//Dejo actuar el sys iluminacion x cantidad fija de tiempo previamente determinada
		}
	}

	if (Comparo_Humedad_Tierra(HUMEDAD_T_AUX))
	{
		//Puedo ingresar un flag indicando que la planta no necesita riego
	}
	if (Comparo_Humedad_Ambiente(HUMEDAD_A_AUX))
	{
		Sys_Ventilacion();	//Disperso la humedad en el ambiente
	}

	Set_Valores(N_AGUA_AUX,TEMPERATURA_AUX,HUMEDAD_T_AUX,HUMEDAD_A_AUX);	//Cargo los valores actuales al proyecto
}

void Set_Valores(uint32_t N_AGUA_AUX,uint32_t TEMPERATURA_AUX,uuint32_t HUMEDAD_A_AUX,uint32_t HUMEDAD_T_AUX)
{
	Set_N_Agua(N_AGUA_AUX);
	Set_Temperatura(TEMPERATURA_AUX);
	Set_Humedad_T(HUMEDAD_T_AUX);
	Set_Humedad_A(HUMEDAD_A_AUX);
}

void Pedir_Datos(uint32_t *N_AGUA_AUX,uint32_t* TEMPERATURA_AUX,uint32_t* HUMEDAD_A_AUX ,uint32_t HUMEDAD_T_AUX)
{
	* TEMPERATURA_AUX = Get_Temperatura();
	* N_AGUA_AUX = Get_N_Agua();
	* HUMEDAD_A_AUX = Get_Humedad_T();
	* HUMEDAD_T_AUX = Get_Humedad_A();
}

void Cargar_Datos_Referencia()			//Ingreso los datos de la base de datos de la planta
{

}
uint32_t Comparo_Temperatura(uint32_t TEMPERATURA_AUX)	//Comparo si esta en el rango de temperatura
{
	return (( (TEMPERATURA_AUX <= TEMPERATURA + 1) || (TEMPERATURA_AUX >= TEMPERATURA - 1 )) ? : 1 ,0);

}
uint32_t Comparo_Humedad_T(uint32_t HUMEDAD_T_AUX)	//Comparo si sobrepasa o es igual a la humedad maxima
{
	return (( HUMEDAD_T_AUX >= HUMEDAD_T )?: 1 , 0 );

}
uint32_t Comparo_Humedad_A(uint32_t HUMEDAD_A_AUX)	//Comparo si sobrepasa la maxima
{
	return (( HUMEDAD_A_AUX >= HUMEDAD_A )?: 1 , 0 );
}
