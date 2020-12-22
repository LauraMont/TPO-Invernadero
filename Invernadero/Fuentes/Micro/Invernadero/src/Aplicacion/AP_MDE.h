/**
*	\file       AP_MDE.h
*	\brief      Prototipos, defines, etc. de las diferentes la M de E
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/

#ifndef INC_AP_MDEE_H_
#define INC_AP_MDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "Aplicacion.h"
#include <string.h>
/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define 	RED			1
#define 	TANQUE  	0
#define 	CANT_TAREAS	6
#define		HUM_LIMITE  10

//Macros de los mensajes a escribir en la pantalla LCD
#define 	MSG_ESPERANDO 		"ESPERANDO..." , RENGLON_1 , 2
#define 	MSG_CUIDANDO  		":CUIDANDO  " , RENGLON_1 , name_lng
#define 	MSG_REGANDO   		":REGANDO   " , RENGLON_1 , name_lng
#define 	MSG_TVACIO    		":T.VACIO   " , RENGLON_1 , name_lng
#define 	MSG_ENFRIANDO 		":ENFRIANDO " , RENGLON_1 , name_lng
#define 	MSG_VENTILANDO		":VENTILANDO" , RENGLON_1 , name_lng
#define 	MSG_CALENTANDO		":CALENTANDO" , RENGLON_1 , name_lng

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
//Enumeracion de los estados posibles para enviar a la aplicacion,
//esta tiene la misma enumeracion desde la cual interpreta el estado actual
typedef enum
{
	WAITING = 0,
	CARING,
	WATERING,
	WARMING,
	COOLING,
	VENTILATE,
	ALARM
} estado_invernadero;

typedef struct
{
	uint8_t esperando;
	uint8_t cuidando;
	uint8_t regando;
	uint8_t	calentando;
	uint8_t enfriando;
	uint8_t ventilando;
	uint8_t alarma;
}estados;

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
extern volatile uint8_t AmbienteMedido ;
extern volatile uint8_t AmbienteMax ;
extern volatile uint8_t AmbienteMin ;
extern volatile uint8_t HumedadMedida ;
extern volatile uint8_t HumedadMin ;
extern volatile uint8_t Control ;
extern volatile uint8_t TempMedida ;
extern volatile uint8_t TempMax ;
extern volatile uint8_t TempMin ;
extern volatile uint8_t TempBajaMin ;
extern volatile uint8_t TempBajaMax ;
extern volatile uint8_t TempAltaMin ;
extern volatile uint8_t TempAltaMax ;
extern volatile uint8_t F_RecibiDatos ;
extern volatile uint8_t Cuidando;
extern volatile uint8_t TimerValvula;
extern volatile uint8_t TimerEspera;
extern volatile uint8_t name_lng;

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
void MaquinaDeEstados ( void );
void Mostrar_Estados(void);

#endif /* INC_AP_MDEE_H_ */
