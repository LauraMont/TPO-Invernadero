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
#include "rx_trama.h"

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

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static rx_trama_state_en rx_trama_state = RX_TRAMA_RESET;

static uint8_t rx_timeout_flag = 0;
static uint8_t err_timeout_flag = 0;
static uint8_t datos_timeout_flag = 0;

static uint8_t data_buffer[DATA_BUFFER_SIZE];
static uint8_t data_counter = 0;

static uint8_t datos_enviar_buffer[DATOS_BUFFER_SIZE];

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/
/*	TRAMA
 * $17%20%3&#
 */

/**
	\fn    	void rx_trama_MDE(void)
	\brief  Máquina de estados de recepción
 	\author Nicolás Taurozzi
 	\date   22/07/2020
	\return No hay retorno
*/

void rx_trama_MDE(void)
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
				//start_rx_timeout();
				data_counter = 0;
				rx_trama_state = WAITING_DATA;
			}

			if(dato_rx != -1 && dato_rx != START_CHAR)
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

		case WAITING_END: {
			dato_rx = UART0_pop_rx();

			if(dato_rx == END_CHAR) {

				stop_datos_timeout();
				rx_trama_state = WAITING_START;
			}

			if(datos_timeout_flag==1){

				update_datos();
				UART0_push_tx(START_CHAR);
				UART0_transmitir(datos_enviar_buffer);
				UART0_push_tx(END_CHAR);
				start_datos_timeout();

			}

			if((dato_rx != -1 && dato_rx != END_CHAR)) {
				err_func();
				rx_trama_state = RX_TRAMA_ERROR;
			}

			break;
		}

		case RX_TRAMA_ERROR: {
			//if(err_timeout_flag == 1) {
				//rgb_set(0, 0 ,0);
				err_timeout_flag = 0;
				rx_trama_state = WAITING_START;
			//}

			break;
		}

		default: {
			rx_trama_state = RX_TRAMA_RESET;
			break;
		}
	}
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
	data_counter++;

	if((uint8_t) dato_rx == '&') {
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


uint32_t get_temp_min(void)
{
	uint32_t temperatura = (data_buffer[1]-'0');

	temperatura += (data_buffer[0]-'0')*10;

	return temperatura;
}

uint32_t get_temp_max(void)
{
    uint32_t temperatura = (data_buffer[4]-'0');

	temperatura += (data_buffer[3]-'0')*10;

	return temperatura;
}

uint32_t get_riego(void) {
	uint32_t riego = (data_buffer[6]-'0');

	return riego;
}
uint8_t is_ready(void){

	if(rx_trama_current_state()==WAITING_END) {
		return 1;
	}
	else return 0;
}

static void update_datos(void) {
	uint32_t humedad = get_humedad();
	uint32_t temp = get_temp();

	datos_enviar_buffer[2]= (humedad/10 +'0');
	humedad%=10;
	datos_enviar_buffer[3]=(humedad + '0');

	datos_enviar_buffer[0]= (temp/10 +'0');
	temp%=10;
	datos_enviar_buffer[1]=(temp + '0');
}
static uint32_t get_humedad(void){

	static uint32_t aux = 1;
	return aux++;				//funcion de prueba

}

static uint32_t get_temp(void){

	static uint32_t aux = 2;
	return aux++;				//funcion de prueba

}
