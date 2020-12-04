#include "Aplicacion.h"

void main(void)
{
	Inicializar();
	ApagarLuces();
	while(1)
	{
		TimerEvent();
		LeerTeclado();


//Para recibir transmisiones de UART
//		rx_trama_MDE();
//
//		if (is_ready())
//		{
//			temp_min = get_temp_min();
//			temp_max = get_temp_max();
//			riego = get_riego();
//		}


//Para leer el adc y la entrada digital
//		adc = ADC_get_average();
//		Display(adc);
//		if(GetPIN(IN0,BAJO))
//		{
//			SetPIN(RELAY1,ON);
//		}
//		else
//		{
//			SetPIN(RELAY1,OFF);
//		}

	}
}
