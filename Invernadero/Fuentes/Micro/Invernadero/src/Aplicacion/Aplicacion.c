#include "Aplicacion.h"

void main(void)
{
//	uint8_t SinAgua = 0;
	Inicializar();
	ApagarLuces();
	Medir();
	while(1)
	{
		TimerEvent();
		if(GetIN())
		{
			RelayON(0);
//			TimedBuzzer(1,SEG);
		}
		else
		{
			RelayOFF(0);
			BuzzerOFF();
		}
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


	}
}
