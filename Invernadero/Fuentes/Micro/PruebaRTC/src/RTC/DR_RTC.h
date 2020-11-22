
#define RTC_RELOJ_H

#define	ISER0 (*(uint32_t *)0xE000E100UL)

#include "DR_PLL.h"
#include "DR_GPIO.h"
#include "DR_Inicializacion.h"
#include "Infotronic.h"
#include "tipos.h"



typedef struct {						// Estructura para manejo de los tiempos del RTC
    uint32_t seg;
    uint32_t min;
    uint32_t hora;
    uint32_t dia_mes;
    uint32_t dia_semana;
    uint32_t dia_anio;
    uint32_t mes;
    uint32_t anio;
}horaRTC_t;
extern horaRTC_t buffer_RTC;

 extern void RTCStart( void );		//DE LA YA CONFIG
 extern void RTCStop( void );


 void RTC_SetHoraFecha(horaRTC_t horafecha);
 void RTC_SetAlarm( horaRTC_t Alarm );
 horaRTC_t RTC_GetHoraFecha(void);
 void RTCSetAlarmMask( uint32_t AlarmMask );

 void RTC_IRQHandler (void);
 void RTC_Init( void );

///////////////////   RTC   /////////////////////////////
    //!< 0x40034000UL: Registro de configuracion y estado del RTC y registros de backup:


	#define		RTC 		( ( volatile uint32_t  * ) 0x40024000UL )

    //!< Miscellaneous registers
    #define		ILR			RTC[0]
    #define		CCR			RTC[2]
    #define		CIIR		RTC[3]
    #define		AMR			RTC[4]
    #define		RTC_AUX		RTC[23]
    #define		RTC_AUXEN	RTC[22]
    #define		CTIME0		RTC[5]
    #define		CTIME1		RTC[6]
    #define		CTIME2		RTC[7]

    //!< Registros del contador
    #define		SECONDS		RTC[8]
    #define		MINUTES		RTC[9]
    #define		HOURS		RTC[10]
    #define		DOM			RTC[11]
    #define		DOW			RTC[12]
    #define		DOY			RTC[13]
    #define		MONTH		RTC[14]
    #define		YEAR		RTC[15]
    #define		CALIBRATION	RTC[16]

    //!<Registros para distintos usos
    #define		GPREG0		RTC[17]
    #define		GPREG1		RTC[18]
    #define		GPREG2		RTC[19]
    #define		GPREG3		RTC[20]
    #define		GPREG4		RTC[21]

    //!<Registros de la Alarma
    #define		ALSEC		RTC[24]
    #define		ALMIN		RTC[25]
    #define		ALHOUR		RTC[26]
    #define		ALDOM		RTC[27]
    #define		ALDOW		RTC[28]
    #define		ALDOY		RTC[29]
    #define		ALMON		RTC[30]
    #define		ALYEAR		RTC[31]

    //!<Equivalente en dias para cada recurrencia de regado
    #define		RIEGO_ALTO          1
    #define		RIEGO_MEDIO         3
    #define		RIEGO_BAJO          7
    #define		RIEGO_MUYBAJO		10


 	 //DEFINICIONES DEL YA CONFIG

	#define		CCR_CLKEN 	0x01
	#define		CCR_CTCRST 	0x02
	#define		CCR_CLKSRC 	0x10

	#define 	ILR_RTCCIF	0x01
	#define 	ILR_RTCALF	0x02

	#define 	IMSEC		0x01
	#define 	IMMIN		0x02
	#define 	IMHOUR		0x04
	#define 	IMDOM		0x08
	#define 	IMDOW		0x10
	#define 	IMDOY		0x20
	#define 	IMMON		0x40
	#define 	IMYEAR		0x80

	#define 	AMRSEC		0x01  /* Alarm mask for Seconds */
	#define 	AMRMIN		0x02  /* Alarm mask for Minutes */
	#define 	AMRHOUR		0x04  /* Alarm mask for Hours */
	#define 	AMRDOM		0x08  /* Alarm mask for Day of Month */
	#define 	AMRDOW		0x10  /* Alarm mask for Day of Week */
	#define 	AMRDOY		0x20  /* Alarm mask for Day of Year */
	#define 	AMRMON		0x40  /* Alarm mask for Month */
	#define 	AMRYEAR		0x80  /* Alarm mask for Year */


