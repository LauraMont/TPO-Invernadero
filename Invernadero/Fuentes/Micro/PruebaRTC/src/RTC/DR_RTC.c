#include "DR_RTC.h"

volatile uint32_t f_alarma ;
volatile uint32_t f_tick_rtc;
    
void RTCStart( void )
{
  /*--- Start RTC counters ---*/
  CCR |= CCR_CLKEN;
  ILR = ILR_RTCCIF;
  return;
}

void RTCStop( void )
{
  /*--- Stop RTC counters ---*/
  CCR &= ~CCR_CLKEN;
  return;
}

void RTC_SetHoraFecha(horaRTC_t horafecha) //seteo la fecha del reloj
{
	SECONDS = horafecha.seg;
	MINUTES = horafecha.min;
	HOURS = horafecha.hora;
	DOM = horafecha.dia_mes;
	DOW = horafecha.dia_semana;
	DOY = horafecha.dia_anio;
	MONTH = horafecha.mes;
	YEAR = horafecha.anio;

	return;
}

void RTC_SetAlarm( horaRTC_t Alarm )
{
	ALSEC = Alarm.seg;
	ALMIN = Alarm.min;
	ALHOUR = Alarm.hora;
	ALDOM = Alarm.dia_mes;
	ALDOW = Alarm.dia_semana;
	ALDOY = Alarm.dia_anio;
	ALMON = Alarm.mes;
	ALYEAR = Alarm.anio;
}

horaRTC_t RTC_GetHoraFecha()
{
	horaRTC_t horafecha;

	horafecha.seg 			= 	SECONDS;
	horafecha.min 			= 	MINUTES;
	horafecha.hora 			= 	HOURS;
	horafecha.dia_mes 		= 	DOM;
	horafecha.dia_semana 	= 	DOW;
	horafecha.dia_anio		= 	DOY;
	horafecha.mes 			= 	MONTH;
	horafecha.anio 			= 	YEAR;

	return horafecha;
}

void RTC_IRQHandler (void)
{
	if(ILR & (1<<0))//Interrupcion por incremento de contador
	{
		  ILR |= 0x01;		/* clear interrupt flag */
		  f_tick_rtc = 1;

	}
	if(ILR & (1<<1))//Interrupcion por alarma
	{
		  ILR |= 0x02;		/* clear interrupt flag */
		  f_alarma = 1;
	}
  return;
}

void RTC_Init( void )
{
	f_alarma = 0;
	f_tick_rtc = 0;

	ISER0 |=(0x01 <<17);
  /* Enable CLOCK into RTC */
  PCONP |= (0x01 << 9);

  /* If RTC is stopped, clear STOP bit. */
  if ( RTC_AUX & (0x1<<4) )
  {
	RTC_AUX |= (0x1<<4);
  }

  /*--- Initialize registers ---*/
  AMR = 0;
  //CIIR = 0;
  CIIR |= (0x01);	//mandara un flag cada vez que incrementa un segundo
  CCR = 0;			//hay que enmascararla para modificar que valores del seteo de la alarma mira (AMR=AMR|0xA3;)(idea de temporadas)
  return;
}

/*****************************************************************************
** Function name:		RTCSetAlarmMask
**
** Descriptions:		Set RTC timer alarm mask
**
** parameters:			Alarm mask setting
** Returned value:		None
**
*****************************************************************************/
void RTCSetAlarmMask( uint32_t AlarmMask )
{
  /*--- Set alarm mask ---*/
  AMR = AlarmMask;
  return;
}






