#include "DR_RTC.h"
#include "DR_GPIO.h"
#include "DR_PLL.h"
#include "DR_Inicializacion.h"

extern volatile uint32_t f_alarma;
extern volatile uint32_t f_tick_rtc;

void ApagarLuces(void);

void main(void)
{
	Inicializacion();

	ApagarLuces();

	RTC_Init();

	horaRTC_t horafecha;
	horafecha.seg = 0;
	horafecha.min = 0;
	horafecha.hora= 0;
	horafecha.dia_mes = 0;
	horafecha.dia_semana = 0;
	horafecha.dia_anio = 0;		/* current date 07/12/2006 */
	horafecha.mes = 0;
	horafecha.anio = 2020;

	RTC_SetHoraFecha( horafecha );

	RTCSetAlarmMask(AMRSEC|AMRMIN|AMRHOUR|AMRDOM|AMRDOW|AMRDOY|AMRMON|AMRYEAR);//Inhabilito todas las alarmas

	CIIR = IMMIN;//Habilito interrupciones cada un segundo

	RTCStart();
	while(1)
	{

		if(f_tick_rtc)
		{
			SetTOGGLE(RELAY1);
			f_tick_rtc=0;
		}
	}
}

void ApagarLuces(void)
{
	SetDIR(led0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led2, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY0, SALIDA);
	SetDIR(RELAY1, SALIDA);
	SetDIR(RELAY2, SALIDA);

	SetPIN(led0, OFF);
	SetPIN(led1, OFF);
	SetPIN(led2, OFF);
	SetPIN(RELAY0,OFF);
	SetPIN(RELAY2,OFF);
	SetPIN(RELAY1,OFF);
}
