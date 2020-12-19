/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Grupo3
*	\date       17-12-2020 18:28:30
*/
/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET                    		0
//Maquina: Control
#define		ESPERA                   		1	//!< Maquina: Control, Coloque aqui una descripcion 
#define		CUIDANDO                 		2	//!< Maquina: Control, Coloque aqui una descripcion 

//Maquina: LecturaDeDatos
#define		WAITING_START            		1	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 
#define		COMANDO                  		2	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 
#define		DETENER                  		3	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 
#define		WAITING_DATA             		4	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 
#define		WAITING_END              		5	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 
#define		ERROR                    		6	//!< Maquina: LecturaDeDatos, Coloque aqui una descripcion 

//Maquina: ControlRiego
#define		ESPERA                   		1	//!< Maquina: ControlRiego, Coloque aqui una descripcion 
#define		REGADO                   		2	//!< Maquina: ControlRiego, Coloque aqui una descripcion 
#define		REGANDO                  		3	//!< Maquina: ControlRiego, Coloque aqui una descripcion 
#define		Alarma                   		4	//!< Maquina: ControlRiego, Coloque aqui una descripcion 

//Maquina: ControlHumedad
#define		ESPERA                   		1	//!< Maquina: ControlHumedad, Coloque aqui una descripcion 
#define		VENTILADO                		2	//!< Maquina: ControlHumedad, Coloque aqui una descripcion 
#define		VENTILANDO               		3	//!< Maquina: ControlHumedad, Coloque aqui una descripcion 

//Maquina: Temperatura
#define		ESPERA                   		1	//!< Maquina: Temperatura, Coloque aqui una descripcion 
#define		ESTABLE                  		2	//!< Maquina: Temperatura, Coloque aqui una descripcion 
#define		CALENTANDO               		3	//!< Maquina: Temperatura, Coloque aqui una descripcion 
#define		REFRESCANDO              		4	//!< Maquina: Temperatura, Coloque aqui una descripcion 

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Control ( int );
static int LecturaDeDatos ( int );
static int ControlRiego ( int );
static int ControlHumedad ( int );
static int Temperatura ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int F_NuevaPlanta ;      		//!< Coloque aqui una descripcion
int F_LeerDatos ;        		//!< Coloque aqui una descripcion
int F_DatosListos ;      		//!< Coloque aqui una descripcion
int ControlRiego ;       		//!< Coloque aqui una descripcion
int ControlHumedad ;     		//!< Coloque aqui una descripcion
int AmbienteMedido ;     		//!< Coloque aqui una descripcion
int AmbienteMax ;        		//!< Coloque aqui una descripcion
int AmbienteMin ;        		//!< Coloque aqui una descripcion
int HumedadMedida ;      		//!< Coloque aqui una descripcion
int HumedadMin ;         		//!< Coloque aqui una descripcion
int Control ;            		//!< Coloque aqui una descripcion
int TempMedida ;         		//!< Coloque aqui una descripcion
int TempMax ;            		//!< Coloque aqui una descripcion
int TempMin ;            		//!< Coloque aqui una descripcion
int TempBajaMin ;        		//!< Coloque aqui una descripcion
int TempBajaMax ;        		//!< Coloque aqui una descripcion
int TempAltaMin ;        		//!< Coloque aqui una descripcion
int TempAltaMax ;        		//!< Coloque aqui una descripcion
int Dato_rx ;            		//!< Coloque aqui una descripcion
int F_RecibiDatos ;      		//!< Coloque aqui una descripcion
int DataValid ;          		//!< Coloque aqui una descripcion

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Control ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Control ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            Control = FALSE;
            F_DatosListos = FALSE;

            Estado = ESPERA;

            break;

        case ESPERA :
            if ( F_DatosListos == TRUE )
            {
                Control = TRUE;

                Estado = CUIDANDO;
            }

            break;

        case CUIDANDO :
            if ( F_DatosListos == FALSE )
            {
                Control = FALSE;

                Estado = ESPERA;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int LecturaDeDatos ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int LecturaDeDatos ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            F_DatosListos = FALSE;

            Estado = WAITING_START;

            break;

        case WAITING_START :
            if ( Dato_rx == PESOS )
            {

                Estado = COMANDO;
            }

            break;

        case COMANDO :
            if ( Dato_rx == DETENER )
            {
                F_RecibiDatos = FALSE;

                Estado = DETENER;
            }

            if ( Dato_rx == INICIAR )
            {

                Estado = WAITING_DATA;
            }

            if ( DataValid == FALSE )
            {
                F_RecibiDatos = FALSE;

                Estado = ERROR;
            }

            break;

        case DETENER :
            if ( F_RecibiDatos == FALSE )
            {
                F_DatosListos = FALSE;

                Estado = WAITING_END;
            }

            if ( DataValid == FALSE )
            {
                F_RecibiDatos = FALSE;

                Estado = ERROR;
            }

            break;

        case WAITING_DATA :
            if ( DataValid == TRUE )
            {
                F_RecibiDatos = TRUE;

                Estado = WAITING_END;
            }

            if ( DataValid == FALSE )
            {
                F_RecibiDatos = FALSE;

                Estado = ERROR;
            }

            break;

        case WAITING_END :
            if ( F_RecibiDatos == TRUE && Dato_rx == Numeral )
            {
                F_DatosListos = TRUE;

                Estado = WAITING_START;
            }

            if ( F_DatosListos == FALSE && Dato_rx == Numeral )
            {
                STOP();

                Estado = WAITING_START;
            }

            break;

        case ERROR :
            if ( TimerError() )
            {

                Estado = WAITING_START;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int ControlRiego ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int ControlRiego ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            ValvulaOFF();

            Estado = ESPERA;

            break;

        case ESPERA :
            if ( Control == TRUE )
            {

                Estado = REGADO;
            }

            break;

        case REGADO :
            if ( HumedadMedida <= HumedadMin && S_Nivel() )
            {
                ValvulaON();
                DispTimerValvula();

                Estado = REGANDO;
            }

            if ( !S_Nivel() )
            {
                EncenderLed();

                Estado = Alarma;
            }

            if ( Control == FALSE )
            {

                Estado = ESPERA;
            }

            break;

        case REGANDO :
            if ( TimerValvula() )
            {
                DispTimerEspera();
                VentilarOFF();

                Estado = REGANDO;
            }

            if ( !S_Nivel() )
            {
                ValvulaOFF();
                ApagarTimerEspera();
                EncenderLed();

                Estado = Alarma;
            }

            if ( HumedadMedida >= HumedadMin )
            {
                ValvulaOFF();
                ApagarTimerEspera();
                ApagarTimerValvula();

                Estado = REGADO;
            }

            if ( Control == FALSE )
            {
                ValvulaOFF();
                ApagarTimerEspera();

                Estado = ESPERA;
            }

            if ( TimerEspera() && HumedadMedida <= HumedadMin )
            {
                ValvulaON();
                DispTimerValvula();

                Estado = REGANDO;
            }

            break;

        case Alarma :
            if ( S_Nivel() )
            {
                ApagarLed();

                Estado = REGADO;
            }

            if ( Control == FALSE )
            {
                ApagarLed();

                Estado = ESPERA;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int ControlHumedad ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int ControlHumedad ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            VentilarOFF();

            Estado = ESPERA;

            break;

        case ESPERA :
            if ( Control == TRUE )
            {

                Estado = VENTILADO;
            }

            break;

        case VENTILADO :
            if ( AmbienteMedido >= AmbienteMax )
            {
                VentilarON();

                Estado = VENTILANDO;
            }

            if ( Control == FALSE )
            {

                Estado = ESPERA;
            }

            break;

        case VENTILANDO :
            if ( AmbienteMedido <= AmbienteMin )
            {
                VentilarOFF();

                Estado = VENTILADO;
            }

            if ( Control == FALSE )
            {
                VentilarOFF();

                Estado = ESPERA;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int Temperatura ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Temperatura ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            ApagarLampara();
            VentilarOFF();

            Estado = ESPERA;

            break;

        case ESPERA :
            if ( Control == TRUE )
            {

                Estado = ESTABLE;
            }

            break;

        case ESTABLE :
            if ( TempMedida <= TempBajaMin )
            {
                EncenderLampar();

                Estado = CALENTANDO;
            }

            if ( TempMedida >= TempAltaMin )
            {
                VentilarON();

                Estado = REFRESCANDO;
            }

            if ( Control == FALSE )
            {

                Estado = ESPERA;
            }

            break;

        case CALENTANDO :
            if ( TempMedida >= TempBajaMax )
            {
                ApagarLampara();

                Estado = ESTABLE;
            }

            if ( Control == FALSE )
            {
                ApagarLampara();

                Estado = ESPERA;
            }

            break;

        case REFRESCANDO :
            if ( TempMedida <= TempAltaMax )
            {
                VentilarOFF();

                Estado = ESTABLE;
            }

            if ( Control == FALSE )
            {
                VentilarOFF();

                Estado = ESPERA;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void MaquinaDeEstados ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Control = RESET;
    static int estados_LecturaDeDatos = RESET;
    static int estados_ControlRiego = RESET;
    static int estados_ControlHumedad = RESET;
    static int estados_Temperatura = RESET;

    // Coloque su codigo aqui

    estados_Control = Control( estados_Control );
    estados_LecturaDeDatos = LecturaDeDatos( estados_LecturaDeDatos );
    estados_ControlRiego = ControlRiego( estados_ControlRiego );
    estados_ControlHumedad = ControlHumedad( estados_ControlHumedad );
    estados_Temperatura = Temperatura( estados_Temperatura );


    return ;
}

