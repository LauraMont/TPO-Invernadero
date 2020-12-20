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
#define		ALARMA                  		4	//!< Maquina: ControlRiego, Coloque aqui una descripcion

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
static uint8_t ControlInvernadero ( uint8_t );
static uint8_t ControlRiego ( uint8_t  Estado );
static uint8_t ControlHumedad ( uint8_t );
static uint8_t ControlTemperatura ( uint8_t );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
volatile uint8_t F_NuevaPlanta ;      		//!< Coloque aqui una descripcion
volatile uint8_t F_LeerDatos ;        		//!< Coloque aqui una descripcion
volatile uint8_t F_DatosListos ;      		//!< Coloque aqui una descripcion
volatile uint8_t Cuidando = FALSE;      		//!< Coloque aqui una descripcion

volatile uint8_t Suministro;
volatile uint8_t AmbienteMedido ;     		//!< Coloque aqui una descripcion
volatile uint8_t AmbienteMax ;        		//!< Coloque aqui una descripcion
volatile uint8_t AmbienteMin ;        		//!< Coloque aqui una descripcion
volatile uint8_t HumedadMedida ;      		//!< Coloque aqui una descripcion
volatile uint8_t HumedadMin;         		//!< Coloque aqui una descripcion
volatile uint8_t Control = FALSE ;            		//!< Coloque aqui una descripcion
volatile uint8_t TempMedida ;         		//!< Coloque aqui una descripcion

volatile uint8_t TempBajaMin ;        		//!< Coloque aqui una descripcion
volatile uint8_t TempBajaMax ;        		//!< Coloque aqui una descripcion
volatile uint8_t TempAltaMin ;        		//!< Coloque aqui una descripcion
volatile uint8_t TempAltaMax ;        		//!< Coloque aqui una descripcion
volatile uint8_t Dato_rx ;            		//!< Coloque aqui una descripcion
volatile uint8_t F_RecibiDatos ;      		//!< Coloque aqui una descripcion
volatile uint8_t DataValid ;          		//!< Coloque aqui una descripcion

volatile uint8_t TimerValvula = 0;
volatile uint8_t TimerEspera = 0;

static char name[DATA_BUFNAME_SIZE];
volatile uint8_t name_lng = 0;


extern volatile uint32_t Temp;
extern volatile uint32_t Hum;
extern volatile uint32_t Hum_tierra;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static uint8_t Control ( uint8_t Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  uint8_t : estado siguiente
*/

static uint8_t ControlInvernadero ( uint8_t  Estado )
{
	static uint8_t i = 0;
    switch ( Estado )
    {

        case RESET :
            Control = FALSE;
            F_DatosListos = FALSE;

            Estado = ESPERA;

            break;

        case ESPERA :
        	if(!i)
        	{
        		CleanLCD(RENGLON_1);
      			Display_LCD( "ESPERA" , RENGLON_1 , 5 );
        		i++;
        	}
        	if ( Cuidando == TRUE )
            {
                Control = TRUE;
                get_name(name);
                name_lng = strlen(name);

                //Valores recibidos
                AmbienteMin = get_hum_amb();
				HumedadMin  = get_hum_tierra();
				TempBajaMax = get_temp_min();
				TempAltaMax = get_temp_max();
				Suministro = get_suministro();

				//Valores de referencia
				AmbienteMax = AmbienteMin + 5;
				TempBajaMin = TempBajaMax + 5;
				TempAltaMin = TempAltaMax - 5;

				Display_LCD( name , RENGLON_1 , 0 );
                i=0;
                Estado = CUIDANDO;
            }

            break;

        case CUIDANDO :
        	if(!i)
        	{
            	Display_LCD( ":CUIDANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
        	if ( Cuidando == FALSE )
            {
        		i=0;
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
*	\fn      static uint8_t ControlRiego ( uint8_t Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  uint8_t : estado siguiente
*/

static uint8_t ControlRiego ( uint8_t  Estado )
{
	static uint8_t TanqueVacio = 0;
	static uint8_t i = 0;
	if(Suministro == RED)
		TanqueVacio  = 0;
	else
		TanqueVacio = GetIN();
	HumedadMedida = Hum_tierra;

    switch ( Estado )
    {

        case RESET :
            ValvulaOFF();
            AlarmaOFF();

            Estado = ESPERA;

            break;

        case ESPERA :

            if ( Control == TRUE )
            {
                Estado = REGADO;
            }
            break;

        case REGADO :

        	if(!i)
        	{
            	Display_LCD( ": CUIDANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( HumedadMedida < HumedadMin && !TanqueVacio )
            {
                ValvulaON();
                DispTimerValvula();
                i = 0;
                Estado = REGANDO;
            }

            if ( TanqueVacio )
            {
            	AlarmaON();
            	i = 0;
                Estado = ALARMA;
            }

            if ( Control == FALSE )
            {
            	i = 0;
                Estado = ESPERA;
            }

            break;

        case REGANDO :
        	if(!i)
        	{
            	Display_LCD( ": REGANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( TimerValvula )
            {
            	TimerValvula = 0;
                DispTimerEspera();
                ValvulaOFF();
            	i = 0;
                Estado = REGANDO;
            }

            if ( TanqueVacio )
            {
                ValvulaOFF();
                ApagarTimerEspera();
                ApagarTimerValvula();
                AlarmaON();
            	i = 0;
                Estado = ALARMA;
            }

            if ( HumedadMedida >= HumedadMin )
            {
                ValvulaOFF();
                ApagarTimerEspera();
                ApagarTimerValvula();
                i = 0;
                Estado = REGADO;
            }

            if ( Control == FALSE )
            {
                ValvulaOFF();
                ApagarTimerEspera();
                ApagarTimerValvula();
            	i = 0;
                Estado = ESPERA;
            }

            if ( TimerEspera && HumedadMedida <= HumedadMin )
            {
            	TimerEspera = 0;
                ValvulaON();
                DispTimerValvula();
            	i = 0;
                Estado = REGANDO;
            }

            break;

        case ALARMA :
        	if(!i)
        	{
            	Display_LCD( ": T.VACIO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( !TanqueVacio )
            {
                AlarmaOFF();
                i = 0;
                Estado = REGADO;
            }

            if ( Control == FALSE )
            {
                AlarmaOFF();
                i = 0;
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
*	\fn      static uint8_t ControlHumedad ( uint8_t Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  uint8_t : estado siguiente
*/

static uint8_t ControlHumedad ( uint8_t  Estado )
{
	static uint8_t i = 0;
	AmbienteMedido = Hum;

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
        	if(!i)
        	{
            	Display_LCD( ": CUIDANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( AmbienteMedido >= AmbienteMax )
            {
                VentilarON();
                i = 0;
                Estado = VENTILANDO;
            }

            if ( Control == FALSE )
            {
                i = 0;
                Estado = ESPERA;
            }

            break;

        case VENTILANDO :
        	if(!i)
        	{
            	Display_LCD( ": VENTILANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( AmbienteMedido <= AmbienteMin )
            {
                VentilarOFF();
                i = 0;
                Estado = VENTILADO;
            }

            if ( Control == FALSE )
            {
                VentilarOFF();
                i = 0;
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
*	\fn      static uint8_t Temperatura ( uint8_t Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  uint8_t : estado siguiente
*/

static uint8_t ControlTemperatura ( uint8_t  Estado )
{
	static uint8_t i = 0;
	TempMedida  = Temp;

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
        	if(!i)
        	{
            	Display_LCD( ": CUIDANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( TempMedida <= TempBajaMax )
            {
                EncenderLampar();
            	i = 0;
                Estado = CALENTANDO;
            }

            if ( TempMedida >= TempAltaMax )
            {
                VentilarON();
            	i = 0;
                Estado = REFRESCANDO;
            }

            if ( Control == FALSE )
            {

                Estado = ESPERA;
            }

            break;

        case CALENTANDO :
        	if(!i)
        	{
            	Display_LCD( ": CALENTANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( TempMedida >= TempBajaMin )
            {
                ApagarLampara();
                i = 0;
                Estado = ESTABLE;
            }

            if ( Control == FALSE )
            {
                ApagarLampara();
                i = 0;
                Estado = ESPERA;
            }

            break;

        case REFRESCANDO :
        	if(!i)
        	{
            	Display_LCD( ": ENFRIANDO" , RENGLON_1 , name_lng );
        		i++;
        	}
            if ( TempMedida <= TempAltaMin )
            {
                VentilarOFF();
                i = 0;
                Estado = ESTABLE;
            }

            if ( Control == FALSE )
            {
                VentilarOFF();
                i = 0;
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
    static uint8_t estados_Control = RESET;
    static uint8_t estados_trama_rx = RESET;
    static uint8_t estados_ControlRiego = RESET;
    static uint8_t estados_ControlHumedad = RESET;
    static uint8_t estados_ControlTemperatura = RESET;

    (void) estados_trama_rx;
    estados_Control            = ControlInvernadero( estados_Control );
    estados_trama_rx           = rx_trama_MDE();
    estados_ControlRiego       = ControlRiego( estados_ControlRiego );
    estados_ControlHumedad     = ControlHumedad( estados_ControlHumedad );
    estados_ControlTemperatura = ControlTemperatura( estados_ControlTemperatura );

    return ;
}

