/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Control( void ) ;
static void Inicializar_LecturaDeDatos( void ) ;
static void Inicializar_ControlRiego( void ) ;
static void Inicializar_ControlHumedad( void ) ;
static void Inicializar_Temperatura( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar_Control( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
static void Inicializar_Control( void )
{

    return ;
}

/**
*	\fn      void Inicializar_LecturaDeDatos( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
static void Inicializar_LecturaDeDatos( void )
{
    return ;
}

/**
*	\fn      void Inicializar_ControlRiego( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
static void Inicializar_ControlRiego( void )
{
    //!< Coloque aqui su codigo
	HumedadMedida = 0 ;
	HumedadMin = 0 ;

    return ;
}

/**
*	\fn      void Inicializar_ControlHumedad( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
static void Inicializar_ControlHumedad( void )
{
    //!< Coloque aqui su codigo
	AmbienteMedido = 0 ;
	AmbienteMax = 0 ;
	AmbienteMin = 0 ;

    return ;
}

/**
*	\fn      void Inicializar_Temperatura( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
static void Inicializar_Temperatura( void )
{
    //!< Coloque aqui su codigo

    return ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void InicializarMDE( void )
{
    //Coloque aqui su codigo


	Inicializar_Control( );

	Inicializar_LecturaDeDatos( );

	Inicializar_ControlRiego( );

	Inicializar_ControlHumedad( );

	Inicializar_Temperatura( );

	
    return ;
}

