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
#define     EN_AGUA		1400
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
volatile uint8_t  Hum_tierra = 10;

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
//	EnviarDatos();
//	uint8_t  TanqueVacio = 0;
	int8_t auxT[] = {"T:  c"};
	int8_t auxHT[] = {"R:  %"};
	int8_t auxHA[] = {"HA:  %"};
//	int32_t adc = ADC_get_average();
//	Hum_tierra = 100 - (adc - EN_AGUA) * 0.03710575139;
//	TanqueVacio = GetIN();
//	MeasureBME280(i2c1);
//
	auxT[2] = Temp/10 + '0';
	auxT[3] = Temp%10 + '0';

	auxHT[2] = Hum_tierra/10 + '0';
	auxHT[3] = Hum_tierra%10 + '0';

	auxHA[3] = Hum/10 + '0';
	auxHA[4] = Hum%10 + '0';


//
//	for(uint8_t i=0; i<4 ; i++)//Repito la cantidad de digitos de la presión
//	{
//		uint8_t aux;
//		aux = Pres%10;
//		Pres /= 10;
//		auxP[8-i] = aux + '0';
//	}
//
//	if(humedad > 70) 	Display_LCD( "HUMEDO!!!" , RENGLON_1 , 0 );
//	else
//	{
		Display_LCD( auxT , RENGLON_2 , 0 );
		Display_LCD( auxHT , RENGLON_2 , 5 );
		Display_LCD( auxHA , RENGLON_2 , 11 );

//	}
//
//	if(TanqueVacio)
//		Alarma(ON);
//	else
//		Alarma(OFF);

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
//				Display(Temp);
				Hum_tierra++;
				break;
		case 4:
//				Display(Pres);

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
	\fn  	Alarma
	\brief 	Toma las acciones necesarias en caso de que el tanque este vacio
 	\author Taurozzi, Nicolás
 	\date 	24/11/20
 	\params [in] activar: ON u OFF según se prenda o no
	\return No hay retorno
*/
//void Alarma(uint8_t activar)
//{
//	static uint8_t flag = 0;
//	static uint8_t contador = 0;
//
//	/*Los valores de los tiempos de funcionamiento estan divididos por 2
//	  porque el programa tarda aproximadamente dos segundo en aumentar en 1
//	  El valor de contador, por lo que reduciendo a la mitad los valores se
//	  consiguen tiempos aproximados a los que se necesitan */
//	if (activar && (contador == 0 ||contador == 5))//Solo prendo el buzzer durante 1 segundo si modo es 1 y cada 10 segundos
//	{
////		RelayON(0);
//		TimedBuzzer(5,DEC);
//		flag = 1;
//	}
//	else if (!activar)
//	{
//		BuzzerOFF();
////		RelaysOFF();
//		flag = 0;
//		contador = 0;
//	}
//	if(flag) contador ++;
//	if(contador == 11) contador = 0; //Reinicio el contador si llega a 10
//
//}

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
