/*******************************************************************************************************************************//**
 *
 * @file		rx_trama.c
 * @brief		Contiene las definiciones de las funciones del modulo
 * @date		23 nov. 2020
 * @author		Taurozzi, Nicolás
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <AP_trama_UART.h>

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
extern volatile uint32_t Temp;
extern volatile uint32_t Hum;
extern volatile uint32_t Hum_tierra;
extern volatile uint8_t Status;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

static rx_trama_state_en rx_trama_state = RX_TRAMA_RESET;

volatile uint8_t init_tx = 0;
static uint8_t rx_timeout_flag = 0;
static uint8_t err_timeout_flag = 0;
static uint8_t datos_timeout_flag = 0;

static uint8_t iniciar_flag = 0;
static uint8_t detener_flag = 1;

static uint8_t data_buffer[DATA_BUFFER_RX_SIZE];
static uint8_t name_buffer[DATA_BUFNAME_SIZE];
static uint8_t data_counter = 0;
static uint8_t name_counter = 0;

static uint8_t datos_enviar_buffer[DATA_BUFFER_TX_SIZE];

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static void restart_rx_timeout(void);
static void stop_rx_timeout(void);

static void start_rx_timeout(void);
static void rx_timeout_callback(void);

static void start_err_timeout(void);
static void err_timeout_callback(void);

static void start_datos_timeout(void);
static void datos_timeout_callback(void);
static void stop_datos_timeout(void);

static void err_func(void);

static void update_datos(void);

static int32_t check_if_data_valid(int32_t dato_rx);
static int32_t check_if_name_valid(int32_t dato_rx);

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/* TRAMA RX
 *
 * $CTMTmHTHAS%Nombre&#
 *
 * C: Comando, TM: temperatura maxima, Tm: temperatura minima, HT:Humedad de la tierra
 * HA: humedad ambiente, S: Suministro
 */

/* TRAMA TX
 *
 * $TEHTHAS#
 *
 * TE: temperatura HT:Humedad de la tierra HA: humedad ambiente, S: Status
 */

/**
	\fn    	void rx_trama_MDE(void)
	\brief  Máquina de estados de recepción
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/

uint8_t rx_trama_MDE(void)
{
	static int32_t dato_rx;

	switch(rx_trama_state)
	{
		case RX_TRAMA_RESET:
		{
			rx_trama_state = WAITING_START;
			break;
		}

		case WAITING_START:
		{
			dato_rx = UART0_pop_rx();

			if(dato_rx == START_CHAR)
			{
				start_rx_timeout();
				data_counter = 0;
				name_counter = 0;
				rx_trama_state = COMANDO;
			}

			if(dato_rx != -1 && dato_rx != START_CHAR)
			{
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}

			break;
		}

		case COMANDO:
		{
			dato_rx = UART0_pop_rx();

			if(dato_rx == '1')
			{
				iniciar_flag = 1;
				detener_flag = 0;
				init_tx = 1;
				restart_rx_timeout();
				rx_trama_state = WAITING_DATA;
			}

			if(dato_rx == '2')
			{
				iniciar_flag = 0;
				detener_flag = 1;
				init_tx = 0;
				restart_rx_timeout();
				rx_trama_state = WAITING_END;
			}

			if(dato_rx != -1 && dato_rx != '1' && dato_rx !='2')
			{
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}

			break;
		}

		case WAITING_DATA:
		{
			int32_t check_data_result;
			dato_rx = UART0_pop_rx();

			check_data_result = check_if_data_valid(dato_rx);

			if(check_data_result == 1) {
				restart_rx_timeout();
				rx_trama_state = WAITING_NAME;
			}

			if(check_data_result == -1 ||
				rx_timeout_flag == 1) {
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}

			break;
		}

		case WAITING_NAME:
		{
			int32_t check_data_result;
			dato_rx = UART0_pop_rx();

			check_data_result = check_if_name_valid(dato_rx);

			if(check_data_result == 1) {
				stop_rx_timeout();

				start_datos_timeout();
				rx_trama_state = WAITING_END;
			}

			if(check_data_result == -1 ||
			   rx_timeout_flag == 1) {
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}

			break;
		}

		case WAITING_END:
		{
			dato_rx = UART0_pop_rx();

			if(dato_rx == END_CHAR && iniciar_flag == 1)
			{

				Cuidando = TRUE; //Significa que tengo todos los datos listos
				detener_flag=0;
				rx_trama_state = WAITING_START;
			}

			if(dato_rx == END_CHAR && detener_flag== 1)
			{

				Cuidando = FALSE;
				iniciar_flag=0;
				stop_datos_timeout();
				rx_trama_state = WAITING_START;
			}

			if((dato_rx != -1 && dato_rx != END_CHAR)) {
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}
			break;
		}

		case RX_TRAMA_ERROR: {
			if(err_timeout_flag == 1) {
				err_timeout_flag = 0;
				rx_trama_state = WAITING_START;
			}
			break;
		}

		default: {
			rx_trama_state = RX_TRAMA_RESET;
			break;
		}
	}

	return rx_trama_state;
}

/**
	\fn    	rx_trama_current_state
	\brief  Devuelve el estado actual de la máqiona
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return El estado actual de la maquina
*/
rx_trama_state_en rx_trama_current_state(void)
{
	return rx_trama_state;
}

/**
	\fn    	check_if_data_valid
	\brief  Análisis de si los datos recibidos son válidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
 	\param  [in] int32_t dato_rx: dato que se recibe
	\return Retorna 1, 0 o -1 si se recibieron todos los datos,
			el buffer esta vacío o llego un dato erroneo respectivamente
*/
static int32_t check_if_data_valid(int32_t dato_rx)
{
	if(dato_rx == -1)
	{
		return 0;
	}

	if((dato_rx < '0' || dato_rx > '9') && (dato_rx !='%' && dato_rx != '&'))
	{
		return -1;
	}

	restart_rx_timeout();

	data_buffer[data_counter] = (uint8_t) dato_rx;
	if(data_counter == 8)
	{
		data_counter++;
		data_counter--;
	}
	data_counter++;

	if((uint8_t) dato_rx == '%') {
		data_counter = 0;
		return 1;
	}

	return 0;
}

static int32_t check_if_name_valid(int32_t dato_rx)
{
	if(dato_rx == -1)
	{
		return 0;
	}

	if(!(dato_rx >= 'A' || dato_rx <= 'Z') && !(dato_rx >= 'a' || dato_rx <= 'z') && (dato_rx != '&'))
	{
		return -1;
	}

	restart_rx_timeout();

	name_buffer[data_counter] = (uint8_t) dato_rx;
	data_counter++;

	if((uint8_t) dato_rx == '&') {
		name_counter = data_counter;
		data_counter = 0;
		return 1;
	}

	return 0;
}

/**
	\fn    	start_rx_timeout
	\brief  Inicia el timer de espera de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void start_rx_timeout(void)
{
	TimerStart(TIMER_ID_RX, RX_TIMEOUT_MSECS, rx_timeout_callback, MIL);
	rx_timeout_flag = 0;
}

/**
	\fn    	restart_rx_timeout
	\brief  Reinicia el timer de recepcion de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void restart_rx_timeout(void)
{
	stop_rx_timeout();
	start_rx_timeout();
}

/**
	\fn    	stop_rx_timeout
	\brief  Detiene el timer de recepcion de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void stop_rx_timeout(void) {
	TimerStop(TIMER_ID_RX);
}

/**
	\fn    	rx_timeout_callback
	\brief  Funcion callback del timer de recepcion
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void rx_timeout_callback(void)
{
	rx_timeout_flag = 1;
//	update_datos();
//	UART0_push_tx(START_CHAR);
//	UART0_transmitir(datos_enviar_buffer);
//	UART0_push_tx(END_CHAR);
//	start_datos_timeout();
}

/**
	\fn    	start_err_timeout
	\brief  Inicia el timer de error
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void start_err_timeout(void)
{
	TimerStart(TIMER_ID_ERR, ERR_TIMEOUT_MSECS, err_timeout_callback, MIL);
	err_timeout_flag = 0;
}

/**
	\fn    	err_timeout_callback
	\brief  Inicia el timer de error
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void err_timeout_callback(void)
{
	err_timeout_flag = 1;
}

/**
	\fn    	err_func
	\brief  Funcion de error que inicia el timer de error
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void err_func(void)
{
	start_err_timeout();
}

/**
	\fn    	start_datos_timeout
	\brief  Inicia el timer de espera de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void start_datos_timeout(void)
{
	TimerStart(TIMER_ID_DATOS, DATOS_TIMEOUT_SECS, datos_timeout_callback, MIL);
	datos_timeout_flag = 0;
}

/**
	\fn    	datos_timeout_callback
	\brief  Funcion callback de la espera de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void datos_timeout_callback(void)
{
	datos_timeout_flag=1;
}

/**
	\fn    	stop_datos_timeout
	\brief  Detiene el timer de espera de datos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/
static void stop_datos_timeout(void)
{
	TimerStop(TIMER_ID_DATOS);
}

/**
	\fn    	static void update_datos(void)
	\brief  Guarda en el buffer de envio el status y los datos medidos en tiempo real
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return no hay retorno
*/
static void update_datos(void)
{
	uint32_t Humedad = Hum;
	uint32_t Humedad_tierra = Hum_tierra;
	uint32_t Temperatura = Temp;

	datos_enviar_buffer[0]= (Temperatura/10 +'0');
	Temperatura%=10;
	datos_enviar_buffer[1]=(Temperatura + '0');

	datos_enviar_buffer[2]= (Humedad/10 +'0');
	Humedad%=10;
	datos_enviar_buffer[3]=(Humedad + '0');

	datos_enviar_buffer[4]= (Humedad_tierra/10 +'0');
	Humedad_tierra%=10;
	datos_enviar_buffer[5]=(Humedad_tierra + '0');

	datos_enviar_buffer[6]= Status + '0';
}

/**
	\fn    	void EnviarDatos(void)
	\brief  Transmite por la UART los datos de las mediciones y el estado
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return no hay retorno
*/
void EnviarDatos(void)
{
	if(init_tx)
	{
		update_datos();
		UART0_push_tx(START_CHAR);
		UART0_transmitir(datos_enviar_buffer);
		UART0_push_tx(END_CHAR);
	}
}

/**
	\fn    	uint32_t get_temp_min(void)
	\brief  Toma el valor de la temperatura minima de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return temperatura: el valor de la temperatura recibida
*/
uint32_t get_temp_min(void)
{
	uint32_t temperatura = (data_buffer[1]-'0');

	temperatura += (data_buffer[0]-'0')*10;

	return temperatura;
}

/**
	\fn    	uint32_t get_temp_max(void)
	\brief  Toma el valor de la temperatura maxima de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return temperatura: el valor de la temperatura recibida
*/
uint32_t get_temp_max(void)
{
    uint32_t temperatura = (data_buffer[3]-'0');

	temperatura += (data_buffer[2]-'0')*10;

	return temperatura;
}

/**
	\fn    	uint32_t get_hum_tierra(void)
	\brief  Toma el valor de la humedad de la tierra de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return hum: el valor de la humedad recibida
*/
uint32_t get_hum_tierra(void)
{
    uint32_t hum = (data_buffer[5]-'0');

    hum += (data_buffer[4]-'0')*10;

	return hum;
}

/**
	\fn    	uint32_t get_hum_amb(void)
	\brief  Toma el valor de la humedad de ambiente de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return hum: el valor de la humedad recibida
*/
uint32_t get_hum_amb(void)
{
    uint32_t hum = (data_buffer[7]-'0');

    hum += (data_buffer[6]-'0')*10;

	return hum;
}

/**
	\fn    	uint32_t get_suministro(void)
	\brief  Toma el valor del suministro de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return suministro: el valor del suministro recibido
*/
uint32_t get_suministro(void)
{
	uint32_t suministro = (data_buffer[8]-'0');

	return suministro;
}

/**
	\fn    	void get_name(char * name)
	\brief  Toma el nombre de los datos recibidos
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\params [out] name
	\return no hay retorno
*/
void get_name(char * name)
{
    int32_t i = 0;

    while(name_buffer[i] != '&')
    {
    	name[i]=name_buffer[i];
    	i++;
    }
    name[i] = '\0';
}
