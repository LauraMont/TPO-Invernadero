#include "DR_I2C.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"
#include "DR_Inicializacion.h"
#include "Infotronic.h"
#include "DR_Display.h"
#include "PR_Display.h"
#include "PR_BMP280.h"
#include "RTC_Reloj.h"
#include "F_Datos.h"
#include "PR_Temporizadores.h"



extern volatile uint8_t  I2CMasterBuffer[BUFSIZE];
void AagarRGB(void);
void main(void)
{

	int i=0;
	InicializacionExp1();
	AagarRGB();
	IniciarDisplay(); ApagarDisplay();
	SetDIR(1,26, ENTRADA);
	Init_I2C1();
    BMP280Config();
    I2CEngine(); //Va a escribir y leer tantas veces como se configuro en la línea anterior

	Cargar_Datos_Referencia();

    /* Check the content of the Master and slave buffer */
	while(1)
	{
		Display(I2CMasterBuffer[i]);
		if(GetPIN(1,26,BAJO))
		{
			while(GetPIN(1,26,BAJO));
			i++;
		}
		//		i %=7;

		//Sistema de riego
		//le ingreso el valor del periodo de riego (ALTO, MEDIO,ETC)
		if(RTV_TimerRegado(PeriodoRegado)&&(f_HUMEDAD_T == BAJA))//agregar la condicion del sensor con humedad
		{
			Sys_Riego();
			f_HUMEDAD_T = ALTA;
		}
		TimerStart ( 1 , 1 , &Sys_Control(), MIN );		//Revisa los datos cada minuto
	}
}

void AagarRGB(void)
{
	SetDIR(led0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led2, SALIDA);//Seteo el relay 0 como salida
	SetPIN(led0, OFF);
	SetPIN(led1, OFF);
	SetPIN(led2, OFF);
}
