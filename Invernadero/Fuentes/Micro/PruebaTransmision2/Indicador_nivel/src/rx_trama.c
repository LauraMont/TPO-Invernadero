/*
 * RxTrama.c
 *
 *  Created on: Nov 4, 2020
 *      Author: asantini
 */

#include "DR_tipos.h"
#include "PR_UART0.h"
#include "DR_GPIO.h"
#include "PR_timer.h"

#include "rx_trama.h"

#define		START_CHAR			('$')
#define		END_CHAR			('#')

#define		TIMER_ID_RX			(0)
#define		RX_TIMEOUT_MSECS	(50)

#define		TIMER_ID_ERR		(1)
#define		ERR_TIMEOUT_MSECS	(250)

#define		TIMER_ID_DATOS		(2)
#define		DATOS_TIMEOUT_SECS	(30)

#define		DATA_BUFFER_SIZE	(8)
#define 	DATOS_BUFFER_SIZE	(4)

//$17%20%3&#

static rx_trama_state_en rx_trama_state = RX_TRAMA_RESET;

static uint8_t rx_timeout_flag = 0;
static uint8_t err_timeout_flag = 0;
static uint8_t datos_timeout_flag = 0;

static uint8_t data_buffer[DATA_BUFFER_SIZE];
static uint8_t data_counter = 0;

static uint8_t datos_enviar_buffer[DATOS_BUFFER_SIZE];

static int32_t check_if_data_valid(int32_t dato_rx);

static void restart_rx_timeout(void);
static void stop_rx_timeout(void);

static void start_rx_timeout(void);
static void rx_timeout_callback(uint32_t id);

static void start_err_timeout(void);
static void err_timeout_callback(uint32_t id);

static void start_datos_timeout(void);
static void datos_timeout_callback(uint32_t id);
static void stop_datos_timeout(void);

static void err_func(void);

static void update_datos(void);				//Funcion que actualiza los datos a enviar

static uint32_t get_humedad(void);				//Funcion que regresará los valores medidos
static uint32_t get_temp(void);					//Funcion que regresará los valores medidos

void rx_trama_MDE(void) {
	static int32_t dato_rx;

	switch(rx_trama_state) {
	case RX_TRAMA_RESET: {
		rx_trama_state = WAITING_START;
		break;
	}

	case WAITING_START: {
		dato_rx = UART0_pop_rx();

		if(dato_rx == START_CHAR) {
			//start_rx_timeout();
			data_counter = 0;
			rx_trama_state = WAITING_DATA;
		}

		if(dato_rx != -1 && dato_rx != START_CHAR) {
			err_func();
			rx_trama_state = RX_TRAMA_ERROR;
		}

		break;
	}

	case WAITING_DATA: {
		int32_t check_data_result;
		dato_rx = UART0_pop_rx();

		check_data_result = check_if_data_valid(dato_rx);

		if(check_data_result == 1) {
			//stop_rx_timeout();
			//-- update_datos();

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

			// Esta funcion deberia imprimir el valor pasado en el display
			//display_set(data_a_valor());
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

rx_trama_state_en rx_trama_current_state(void) {
	return rx_trama_state;
}

static int32_t check_if_data_valid(int32_t dato_rx) {
	if(dato_rx == -1) {
		return 0;
	}

	if((dato_rx < '0' || dato_rx > '9') && (dato_rx !='%' && dato_rx != '&')) {
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

static void start_rx_timeout(void) {
	timer_start(TIMER_ID_RX, RX_TIMEOUT_MSECS, rx_timeout_callback);
	rx_timeout_flag = 0;
}

static void restart_rx_timeout(void) {
	stop_rx_timeout();
	start_rx_timeout();
}

static void stop_rx_timeout(void) {
	timer_stop(TIMER_ID_RX);
}

static void rx_timeout_callback(uint32_t id) {
	rx_timeout_flag = 1;
}

static void start_err_timeout(void) {
	timer_start(TIMER_ID_ERR, ERR_TIMEOUT_MSECS, err_timeout_callback);
	err_timeout_flag = 0;
}

static void err_timeout_callback(uint32_t id) {
	err_timeout_flag = 1;
}

static void err_func(void) {
	//rgb_set(1, 0, 0); // === rgb_red();
	start_err_timeout();
}


static void start_datos_timeout(void){
	timer_start(TIMER_ID_DATOS, DATOS_TIMEOUT_SECS*1000, datos_timeout_callback);
	datos_timeout_flag = 0;
}

static void datos_timeout_callback(uint32_t id){
	datos_timeout_flag=1;
}

static void stop_datos_timeout(void){
	timer_stop(TIMER_ID_DATOS);
}

/*static*/ uint32_t get_temp_min(void) {
	uint32_t temperatura = (data_buffer[7]-'0');

	temperatura += (data_buffer[6]-'0')*10;

	return temperatura;
}
/*static*/ uint32_t get_temp_max(void) {
	uint32_t temperatura = (data_buffer[4]-'0');

	temperatura += (data_buffer[3]-'0')*10;

	return temperatura;
}

/*static*/ uint32_t get_riego(void) {
	uint32_t riego = (data_buffer[1]-'0');

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

	datos_enviar_buffer[3]= (humedad/10 +'0');
	humedad%=10;
	datos_enviar_buffer[2]=(humedad + '0');

	datos_enviar_buffer[1]= (temp/10 +'0');
	temp%=10;
	datos_enviar_buffer[0]=(temp + '0');
}
static uint32_t get_humedad(void){

	return 52;				//funcion de prueba

}

static uint32_t get_temp(void){

	return 30;				//funcion de prueba

}
