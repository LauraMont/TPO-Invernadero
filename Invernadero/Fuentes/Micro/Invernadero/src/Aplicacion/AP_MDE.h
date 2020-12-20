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
#define 	RED		1
#define 	TANQUE  0
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

//extern volatile uint8_t F_LeerDatos ;
extern volatile uint8_t F_DatosListos ;
extern volatile uint8_t F_RecibiDatos ;
extern volatile uint8_t DataValid ;
extern volatile uint8_t Cuidando;

extern volatile uint8_t TimerValvula;
extern volatile uint8_t TimerEspera;

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
void MaquinaDeEstados ( void );

#endif /* INC_AP_MDEE_H_ */
