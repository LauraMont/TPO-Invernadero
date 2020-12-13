#include "Aplicacion.h"

void main(void)
{
	Inicializar();
	ApagarLuces();
	Medir();
	while(1)
	{
		TimerEvent();
//Para recibir transmisiones de UART
//		rx_trama_MDE();
//
//		if (is_ready())
//		{
//			temp_min = get_temp_min();
//			temp_max = get_temp_max();
//			riego = get_riego();
//		}
	}
}
