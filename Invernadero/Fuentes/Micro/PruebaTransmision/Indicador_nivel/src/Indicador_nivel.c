#include "DR_PLL.h"
#include "DR_SYSTICK.h"

#include "PR_timer.h"
#include "PR_UART0.h"

#include "rx_trama.h"

static void callback(uint32_t id);
volatile uint8_t flagcito = 0;

int main(void) {
	uint32_t temp_min;
	uint32_t temp_max;
	uint32_t humidity;

	InicializarPLL();
	SYSTICK_init();

	UART0_init();

	timer_start(0, 10000 , callback);

	while(1)
	{

		timer_event();

		if(flagcito)
		{
			rx_trama_MDE();

			if (get_datos())
			{

				temp_min = get_temp_min();
				temp_max = get_temp_max();
				humidity = get_humidity();
			}

		}
	}

	return 0;
}

static void callback(uint32_t id) {
	flagcito = 1;
}
