
#define RTC_RELOJ_H
#include"../Inicializacion/tipos.h"


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



///////////////////   RTC   /////////////////////////////
    //!< 0x40034000UL: Registro de configuracion y estado del RTC y registros de backup:

    #define     SegPorDia   86400   //segundos por dia

    #define		RTC         ( ( volatile uint32_t  * ) 0x40024000UL )

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


	void RTC_SetHoraFecha(horaRTC_t* horafecha);
	void RTC_SetAlarma(void);
	int RTV_TimerRegado(unsigned int PeriodoRegado);
	unsigned int  RTV_CambioTemporada();


