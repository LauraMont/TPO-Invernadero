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

/**
*	\fn      int STOP ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  int : TRUE y FALSE
*/
int STOP1 ( void )
{
    int res = 0 ;

    // Coloque aqui su codigo

    return res ;
}

/**
*	\fn      int S_Nivel ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  int : TRUE y FALSE
*/
int S_Nivel ( void )
{
    int res = 0 ;

    // Coloque aqui su codigo

    return res ;
}

/**
*	\fn      int TimerError ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  int : TRUE y FALSE
*/
int TimerError ( void )
{
    int res = 0 ;

    // Coloque aqui su codigo

    return res ;
}

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

/**
*	\fn      void MostrarDatos ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void MostrarDatos ( void )
{
    // Coloque aqui su codigo

    return ;
}

/**
*	\fn      void VentilarON ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void DispTimerValvula ( void )
{
	TimerStart(TM_VALVULA, VALVULA_TIME_SEG, ValvulaCallback ,SEG);
}

void ValvulaCallback (void)
{
	TimerValvula = 1;
}

/**
*	\fn      void ApagarTimerEspera ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void DispTimerEspera ( void )
{
	TimerStart(TM_ESPERA, ESPERA_TIME_SEG, EsperaCallback ,SEG);
}

void EsperaCallback (void)
{
	TimerEspera = 1;
}

/**
*	\fn      void ApagarTimerEspera ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ApagarTimerEspera ( void )
{
	TimerStop(TM_ESPERA);
}

void AlarmaON(void)
{
	TimedBuzzer(1,SEG);
	TimerStart(TM_ALARMA, ALARMA_TIME_SEG, AlarmaON ,SEG);
}

void AlarmaOFF(void)
{
	TimerStop(TM_ALARMA);
}

/**
*	\fn      void EncenderLampar ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
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
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void ApagarLampara ( void )
{
	RelayOFF(2);
}

/**
*	\fn      void STOP ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void STOP ( void )
{
    // Coloque aqui su codigo

    return ;
}

