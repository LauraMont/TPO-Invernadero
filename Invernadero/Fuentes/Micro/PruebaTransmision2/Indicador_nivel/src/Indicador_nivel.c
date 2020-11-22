#include "DR_PLL.h"
#include "DR_SYSTICK.h"

#include "PR_timer.h"
#include "PR_UART0.h"

#include "rx_trama.h"

int main(void) {
	uint32_t temp_min;
	uint32_t temp_max;
	uint32_t riego;
	InicializarPLL();
	SYSTICK_init();

	UART0_init();

	while(1) {

		timer_event();
		rx_trama_MDE();

		if (is_ready()) {

			temp_min = get_temp_min();
			temp_max = get_temp_max();
			riego = get_riego();
		}
	}

	return 0;
}
