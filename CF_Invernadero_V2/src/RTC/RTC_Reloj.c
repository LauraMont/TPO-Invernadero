#include <stdio.h>
#include "RTC_Reloj.h"

#include "DR_I2C.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"
#include "DR_Inicializacion.h"
#include "Infotronic.h"
#include "DR_Display.h"
#include "PR_Display.h"
#include "PR_BMP280.h"


void Incializar_RTC(void)
    {
        buffer_RTC.seg 	= 0;			// Configuramos la hora de inicio del RTC
        buffer_RTC.min 	= 56;
        buffer_RTC.hora = 19;
        buffer_RTC.dia_mes	= 2;
        buffer_RTC.mes 	= 12;
        buffer_RTC.anio	= 2019;

        PCONP |= (0x01 << 9); 				// Habilitamos alimentacion del RTC
        CCR = 0x12; 					// Ponemos el divisor de clock y el contador en reset. Calibracion deshabilitada.
        RTC_AUXEN &= ~(0x01 << 4); 		// Deshabilito la interrupcion por fail del clock.

        RTC_SetHoraFecha(&buffer_RTC);	// Año, mes, dia. Ultimos tres argumentos: horas, minutos, segundos.
        //CIIR |= (0x01); 				// Cada un segundo me da una interrupcion.

        CIIR |= (0x01 << 4);        //CREO que cada dia genere una interrupcion por dia

        CCR = 0x11; 					// Habilitamos el RTC.
        ISER0 = (1 << 17);				// Habilito interrupciones en NVIC

        AMR =(0x11) << 2;           //CREO que habilito alarma para que vea dia y hora
        AMR =(0x01) << 6;           //CREO que habilito alarma para que vea mes
        AMR=~(AMR);                 //para que lo haga ignorara todos los bits en 1 por lo que primero le otorgo 1 a valores que quiero que esten en 0 y luego los niego
    }
    
    void RTC_SetHoraFecha(horaRTC_t* horafecha) //seteo la fecha del reloj
    {


        SECONDS = horafecha->seg;
        MINUTES = horafecha->min;
        HOURS 	= horafecha->hora;
        DOM 	= horafecha->dia_mes;
        DOW 	= horafecha->dia_semana;
        DOY 	= horafecha->dia_anio;
        MONTH 	= horafecha->mes;
        YEAR 	= horafecha->anio;
    }
    
    void RTC_SetAlarma()    //Mandara una signal cuando cambie de estacion
    {

        ALSEC   =0;
        ALMIN	=0;
        ALHOUR	=12;
        ALDOM	=21;
        ALDOW	=0;
        ALDOY	=0;
        ALMON	=6;
        ALYEAR	=0;


    }
    
    void RTC_GetHoraFecha(horaRTC_t* horafecha)
    {
        horafecha->seg 			= 	SECONDS;
        horafecha->min 			= 	MINUTES;
        horafecha->hora 		= 	HOURS;
        horafecha->dia_mes 		= 	DOM;
        horafecha->dia_semana 	= 	DOW;
        horafecha->dia_anio		= 	DOY;
        horafecha->mes 			= 	MONTH;
        horafecha->anio 		= 	YEAR;
    }

	int RTV_TimerRegado(unsigned int PeriodoRegado)
    {

        static unsigned int cantidad_dias=0;

        if(ILR & (1<<0))   //signal cuando hay incremento (configurado por CIIR)
        {
        	ILR  |=  1<<0;	//reinicio el flag
            cantidad_dias++;

            if(cantidad_dias==PeriodoRegado)
             {
                 cantidad_dias=0;
                 return 1;
             }
        }
        else return 0;

    }

	unsigned int RTV_CambioTemporada()  //si cambia de tempporada retorna 1 y debo cambiar la configuracion
    {
        if(ILR & (1<<1))       //signal cuando hay incremento (configurado por Alarma)
        {
        	ILR = 1<<1;	//reinicio el flag
            return 1;
        }
        else return 0;
    }












