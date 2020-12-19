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

/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define		TRUE            		X 
#define		FALSE           		X 

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

int STOP ( void );
int TimerValvula ( void );
int TimerEspera ( void );
int S_Nivel ( void );
int TimerError ( void );

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void MostrarDatos ( void );
void VentilarON ( void );
void VentilarOFF ( void );
void ValvulaON ( void );
void DispTimerValvula ( void );
void ValvulaOFF ( void );
void DispTimerEspera ( void );
void EncenderLed ( void );
void ApagarLed ( void );
void ApagarTimerEspera ( void );
void EncenderLampar ( void );
void ApagarLampara ( void );
void STOP ( void );
void ApagarTimerValvula ( void );

#endif /* INC_AP_FUNCIONESMDEE_H_ */
