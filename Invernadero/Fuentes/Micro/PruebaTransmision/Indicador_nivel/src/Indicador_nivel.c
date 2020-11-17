#include "DR_PLL.h"
#include "DR_SYSTICK.h"

#include "PR_timer.h"
#include "PR_UART0.h"

#include "rx_trama.h"

int main(void) {
	InicializarPLL();
	SYSTICK_init();

	UART0_init();

	while(1) {

		timer_event();
		rx_trama_MDE();

		if (get_datos()) {

			get_temp_min();
			get_temp_max();
			get_humidity();
		}
	}

	return 0;
}
