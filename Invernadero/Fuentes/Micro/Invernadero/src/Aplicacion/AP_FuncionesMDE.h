/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/

#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "Aplicacion.h"
#include "AP_MDE.h"

/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

int STOP1( void );
int TimerError ( void );

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void MostrarDatos ( void );
void VentilarON ( void );
void VentilarOFF ( void );

//RIEGO
void ValvulaON ( void );
void ValvulaOFF ( void );
void Alarma(uint8_t activar);
void AlarmaON(void);
void AlarmaOFF(void);

void DispTimerValvula ( void );
void DispTimerEspera ( void );
void ApagarTimerEspera ( void );
void ApagarTimerValvula ( void );
void ValvulaCallback (void);
void EsperaCallback (void);


void EncenderLampar ( void );
void ApagarLampara ( void );
void STOP ( void );
void ApagarTimerValvula ( void );

#endif /* INC_AP_FUNCIONESMDEE_H_ */
