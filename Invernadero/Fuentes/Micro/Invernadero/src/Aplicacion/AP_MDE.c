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
#define		ESPERA                   		1	//!< Maquina: Control
#define		CUIDANDO                 		2	//!< Maquina: Control

//Maquina: LecturaDeDatos
#define		WAITING_START            		1	//!< Maquina: LecturaDeDatos
#define		COMANDO                  		2	//!< Maquina: LecturaDeDatos
#define		DETENER                  		3	//!< Maquina: LecturaDeDatos
#define		WAITING_DATA             		4	//!< Maquina: LecturaDeDatos
#define		WAITING_END              		5	//!< Maquina: LecturaDeDatos
#define		ERROR                    		6	//!< Maquina: LecturaDeDatos

//Maquina: ControlRiego
#define		ESPERA                   		1	//!< Maquina: ControlRiego
#define		REGADO                   		2	//!< Maquina: ControlRiego
#define		REGANDO                  		3	//!< Maquina: ControlRiego
#define		ALARMA                  		4	//!< Maquina: ControlRiego

//Maquina: ControlHumedad
#define		ESPERA                   		1	//!< Maquina: ControlHumedad
#define		VENTILADO                		2	//!< Maquina: ControlHumedad
#define		VENTILANDO               		3	//!< Maquina: ControlHumedad

//Maquina: Temperatura
#define		ESPERA                   		1	//!< Maquina: Temperatura
#define		ESTABLE                  		2	//!< Maquina: Temperatura
#define		CALENTANDO               		3	//!< Maquina: Temperatura
#define		REFRESCANDO              		4	//!< Maquina: Temperatura


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
//Flags de la maquina de recepcion UART
volatile uint8_t F_NuevaPlanta ;
volatile uint8_t F_LeerDatos ;
volatile uint8_t Cuidando = FALSE;
volatile uint8_t Control = FALSE ;

volatile uint8_t Suministro;

//Variables para la maquina de control de humedad
volatile uint8_t AmbienteMedido ;
volatile uint8_t AmbienteMax ;
volatile uint8_t AmbienteMin ;

//Variables  y flags para la maquina de control de riego
volatile uint8_t HumedadMedida ;
volatile uint8_t HumedadMin;
volatile uint8_t TimerValvula = 0;
volatile uint8_t TimerEspera = 0;

//Variables para la maquina de control de temperatura
volatile uint8_t TempMedida ;
volatile uint8_t TempBajaMin ;
volatile uint8_t TempBajaMax ;
volatile uint8_t TempAltaMin ;
volatile uint8_t TempAltaMax ;

//Variables de uso general
volatile uint8_t Status = 0;	//Estado para enviar a la aplicacion
static char name[DATA_BUFNAME_SIZE]; //Nombre recibido desde la aplicacion
volatile uint8_t name_lng = 0;		//Largo del nombre
volatile uint8_t enfriando = 0, ventilando = 0;//Flags para indicar un estado en particular

//Valores medidos por los sensores
extern volatile uint32_t Temp;
extern volatile uint32_t Hum;
extern volatile uint32_t Hum_tierra;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static uint8_t Control ( uint8_t Estado )
*	\brief   Máquina de estados de control
*	\details Se encarga de iniciar o detener el cuidado de la planta
*			 segun el flag cuidando que lo controla la trama de recepcion
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

            Estado = ESPERA;

            break;

        case ESPERA :	//Estoy esperando a que se reciban los datos que sucede cuando cuidado sea TRUE
        	if(!i)
        	{
        		CleanLCD(RENGLON_1);
      			Display_LCD( MSG_ESPERANDO );
            	Status = WAITING;
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
            	Status = CARING;
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
*	\brief   Maquina de estados para el control del riego
*	\details Se encarga de controlar el riego del invernadero,
*			 que cuando tiene la tierra seca riega en un ciclo de
*			 3 segundos de riego y 10 segundos en los que espera a
*			 que el agua decante antes de volver a regar para evitar
*			 el sobre-riego
*	\author  Grupo3
*	\date    17-12-2020 18:28:30
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  uint8_t : estado siguiente
*/

static uint8_t ControlRiego ( uint8_t  Estado )
{
	static uint8_t TanqueVacio = 0;
	static uint8_t i = 0;
/*
 * Desde la aplicacion se indica si el suministro sera por red o por un tanque,
 * si es por red se trunca TanqueVacio a cero y no se evalua el sensor de
 * nivel, pero si el suministro es de tanque si se evalua el sensor cada vez que
 * se entra a la maquina
 * */
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
            	Display_LCD( MSG_CUIDANDO );
            	Status = CARING;
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
            	Display_LCD( MSG_REGANDO );
            	Status = WATERING;
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
//        	if(!i)
//        	{
//            	Display_LCD( MSG_TVACIO );
//            	Status = ALARM;
//            	i++;
//        	}
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
*	\brief   CMaquina para el control de la humedad
*	\details Se encarga de mantener la humedad del ambiente por debajo
*			 del nivel maximo admitido por la planta
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
/*
 * Al terimar de ventilar la maquina vuelve a ventilado, pero si
 * en ese mismo momento se encontraba enfriando, el lugar de cambiar
 * status a cuidando lo cambia a enfriando. Esta precaucion se debe a
 * que ambos parametros se reducen con el mismo cooler, y caso contrario
 * al detenerse el ventilado también se detendria enfriando
 * */
        	if(!i)
        	{
        		if(enfriando)
        		{
                	Display_LCD( MSG_ENFRIANDO );
                	Status = COOLING;
        		}
        		else
        		{
                	Display_LCD( MSG_CUIDANDO );
                	Status = CARING;
        		}
            	i++;
        	}
            if ( AmbienteMedido >= AmbienteMax )
            {
                VentilarON();
                ventilando = 1;
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
            	Display_LCD( MSG_VENTILANDO );
            	Status = VENTILATE;
            	i++;
        	}
            if ( AmbienteMedido <= AmbienteMin )
            {
            	if(!enfriando) //Si el invernadero esta enfriando no apago el ventilador
            		VentilarOFF();
            	ventilando = 0;
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
*	\brief   Maquina que se encarga del cuidado de la temperatura
*	\details Se encarga de mantener la temperatura entres los limites
*			 admisibles por la planta. Enfria el ambiente con el cooler
*			 o lo calienta con la lampara incandescente
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
//Se tiene la misma precaución que en la máquina de control
//de humedad para evitar que se solapen los estados
        	if(!i)
        	{
        		if(ventilando)
        		{
                	Display_LCD( MSG_VENTILANDO );
                	Status = VENTILATE;
        		}
        		else
        		{
                	Display_LCD( MSG_CUIDANDO );
                	Status = CARING;
        		}
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
            	enfriando = 1;
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
            	Display_LCD( MSG_CALENTANDO );
            	Status = WARMING;
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
				Display_LCD( MSG_ENFRIANDO );
				Status = COOLING;
            	i++;
        	}
            if ( TempMedida <= TempAltaMin )
            {
            	if(!ventilando) //Si en el mismo momento se esta ventilando no apago el cooler
            		VentilarOFF();
            	i = 0;
                enfriando = 0;
                Estado = ESTABLE;
            }

            if ( Control == FALSE )
            {
          		VentilarOFF();
                enfriando = 0;
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
*	\brief   Funcion general de las maquinas de estado
*	\details Engloba las máquinas de estado en una sola función.
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

