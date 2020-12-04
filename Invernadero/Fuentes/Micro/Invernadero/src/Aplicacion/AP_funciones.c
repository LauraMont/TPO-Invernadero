/*******************************************************************************************************************************//**
 *
 * @file		AP_funciones.c
 * @brief		Descripcion del modulo
 * @date		23 nov. 2020
 * @author		Taurozzi, Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "AP_funciones.h"
#include "stdio.h"
#include "stdlib.h"
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
extern volatile uint8_t carga_timeout_flag;
extern volatile uint8_t reset_flag;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint32_t Temp = 0;
volatile uint32_t Pres= 0;
volatile uint32_t Hum= 0;
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
	\fn  	Inicializar(void)
	\brief 	Inicializa todos los periféricos
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void Inicializar(void)
{
	InicializarPLL( );
	InicializarSysTick ( );
	InicializarUART0();
	ADC_init();
	Init_I2C1();

	InitLCD();
	InicializarDisplay();
	InicializarTeclado();

	BME280_init(1); //Configura los parámetros de medición y toma los valores necesarios
}

/**
	\fn  	void Medir(void)
	\brief 	Inicializa la medició
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void Medir(void)
{
	uint8_t i = 0;
//	int8_t auxT[3];
//	int8_t auxH[3];
//	int8_t auxP[7];
	Temp = get_temp(1);
	Pres = get_pres(1);
	Hum =  get_hum(1);

//	MySprintf(auxT, Temp);
//	MySprintf(auxH, Hum);
//	MySprintf(auxP, Pres);
//	sprintf(auxT, "%dC", Temp);
//	sprintf(auxH, "%d", Hum);
//	sprintf(auxT, "%dhPa", Pres);
	if(!i)
	{
		Display_LCD( "Temp:  C" , RENGLON_1 , 0 );
		Display_LCD( "Hum:  %" , RENGLON_1 , 9 );
		Display_LCD( "Pres:    hPa" , RENGLON_2 , 0 );
		i=i;
	}

//	Display_LCD( auxT, RENGLON_1 , 5 );
//	Display_LCD( auxH , RENGLON_1 , 13 );
//	Display_LCD( auxP , RENGLON_2 , 5 );


	TimerStart( 1, 1, Ev_Estado1, SEG );    //  Las líneas comentadas son para que la medición se repita cada 1 segundo
}

void MySprintf(int8_t * lugar, int32_t valor)
{
	for(uint8_t i = CantDigitos(valor); i > 0; i--)
	{
		lugar[i] = valor + '0';
	}
}
/**
	\fn  	LeerTeclado(void)
	\brief 	Toma la tecla del teclado
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void LeerTeclado(void)
{
	uint8_t Tecla = GetKey();
//	uint8_t auxT[16];
//	uint8_t auxP[16];

	switch (Tecla)
	{
		case 5:
//				sprintf(aux, "Temperatura: %d", Temp);
//				CleanLCD(RENGLON_1);
//				if(!i)
//				{
//					Display_LCD( "HOLA" , RENGLON_1 , 0 );
//					i = 1;
//				}
//				else
//				{
//					Display_LCD( "CHAU", RENGLON_1 , 0 );
//					i = 0;
//				}
				Display(Temp);
				break;
		case 4:
				Display(Pres);
				break;

		case 3:
				Display(Hum);
				break;

		default:
				 break;
	}
}

/**
	\fn  	LeerTeclado(void)
	\brief 	Toma la tecla del teclado
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
	\return No hay retorno
*/
void ApagarLuces(void)
{
	SetDIR(led0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led2, SALIDA);//Seteo el relay 0 como salida

	SetDIR(RELAY0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY2, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY3, SALIDA);//Seteo el relay 0 como salida

	SetPIN(led0, OFF);
	SetPIN(led1, OFF);
	SetPIN(led2, OFF);

	SetPIN(RELAY0, OFF);
	SetPIN(RELAY1, OFF);
	SetPIN(RELAY2, OFF);
	SetPIN(RELAY3, OFF);
}
