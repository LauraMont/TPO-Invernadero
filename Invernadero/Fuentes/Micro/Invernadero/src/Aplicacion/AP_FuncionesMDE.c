/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** VARIABLES PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/


/**
*	\fn      void VentilarON ( void )
*	\brief   Enciende el relay del cooler
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void VentilarON ( void )
{
	RelayON(1);
}

/**
*	\fn      void VentilarOFF ( void )
*	\brief   Apaga el relay del cooler
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void VentilarOFF ( void )
{
	RelayOFF(1);
}

/**
*	\fn      void ValvulaON ( void )
*	\brief   Enciende el relay de la valvula
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ValvulaON ( void )
{
	RelayON(0);
}

/**
*	\fn      void ValvulaOFF ( void )
*	\brief   Apaga el relay de la valvula
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ValvulaOFF ( void )
{
	RelayOFF(0);
}

/**
*	\fn      void DispTimerValvula ( void )
*	\brief   Inicia el timer de la valvula
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void DispTimerValvula ( void )
{
	TimerStart(TM_VALVULA, VALVULA_TIME_SEG, ValvulaCallback ,SEG);
}

/**
*	\fn      void ValvulaCallback (void)
*	\brief   Funcion callback que pone un flag en 1
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ValvulaCallback (void)
{
	TimerValvula = 1;
}

/**
*	\fn      void ApagarTimerEspera ( void )
*	\brief   Detiene el timer de la valvula
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ApagarTimerValvula ( void )
{
	TimerStop(TM_VALVULA);
}

/**
*	\fn      void DispTimerEspera ( void )
*	\brief   Inicia el timer de espera
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void DispTimerEspera ( void )
{
	TimerStart(TM_ESPERA, ESPERA_TIME_SEG, EsperaCallback ,SEG);
}

/**
*	\fn      void EsperaCallback (void)
*	\brief   Funcion callback que pone un flag en 1
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void EsperaCallback (void)
{
	TimerEspera = 1;
}

/**
*	\fn      void ApagarTimerEspera ( void )
*	\brief   Detiene el timer de espera
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ApagarTimerEspera ( void )
{
	TimerStop(TM_ESPERA);
}

/**
*	\fn      void AlarmaON(void)
*	\brief   Inicia la alarma con un ciclo de 1/10 seg
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void AlarmaON(void)
{
	TimedBuzzer(1,SEG);
	Display_LCD(MSG_TVACIO);
	TimerStart(TM_ALARMA, ALARMA_TIME_SEG, AlarmaON ,SEG);
}

/**
*	\fn      void AlarmaOFF(void)
*	\brief   Apaga la alarma
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void AlarmaOFF(void)
{
	TimerStop(TM_ALARMA);
}

/**
*	\fn      void EncenderLampar ( void )
*	\brief   Enciende el raly de la lampara
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void EncenderLampar ( void )
{
	RelayON(2);
}

/**
*	\fn      void ApagarLampara ( void )
*	\brief   Apaga el relay de la lampara
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ApagarLampara ( void )
{
	RelayOFF(2);
}



