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

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define 	ON 			1
#define 	OFF			0
#define     EN_AGUA		1300
#define     EN_AIRE		4095
#define 	i2c1		1

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
extern volatile uint8_t init_tx;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint32_t Temp = 10;
volatile uint32_t Pres = 0;
volatile uint32_t Hum  = 8;//0;
volatile uint32_t Hum_tierra = 15;

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
	InicializarEntradasDig();
	InicializarRelays();
	InicializarBuzzer();
	InicializarMDE();
	BME280_init(1); //Configura los parámetros de medición y toma los valores necesarios en el canal 1 del I2C
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
	int8_t auxT[] = {"T:  C"};
	int8_t auxHT[] = {"r:  %"};
	int8_t auxHA[] = {"HA:  %"};

	//Tomo las mediciones del adc y del BME280
//	int32_t adc = ADC_get_average();
//	Hum_tierra = 100 - (adc - EN_AGUA) * 0.03710575139;
//	if(Hum_tierra >= 100) Hum_tierra = 99;
//	MeasureBME280(i2c1);

	//Preparo las mediciones para escribirlas en el LCD
	auxT[2] = Temp/10 + '0';
	auxT[3] = Temp%10 + '0';

	auxHT[2] = Hum_tierra/10 + '0';
	auxHT[3] = Hum_tierra%10 + '0';

	auxHA[3] = Hum/10 + '0';
	auxHA[4] = Hum%10 + '0';

	//Escribo en el LCD los valores de las mediciones
	Display_LCD( auxT , RENGLON_2 , 0 );
	Display_LCD( auxHT , RENGLON_2 , 5 );
	Display_LCD( auxHA , RENGLON_2 , 10 );

	//Envio los datos medidos por UART
	EnviarDatos();

	//En 1 seg vuelvo a llamar a esta misma funcion
	TimerStart( TM_MEDICION, MEDICION_TIME_SEG, Medir, SEG );
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

	switch (Tecla)
	{
		case 5:
				Hum_tierra++;
				break;
		case 4:
				Hum_tierra--;
				break;

		case 3:
				Hum ++;
				break;

		case 2:
				Temp++;
				break;

		case 1:
				Temp--;
				Hum --;
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
