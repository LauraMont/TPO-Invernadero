#include <DR_Display.h>
#include <PR_Display.h>
#include "DR_GPIO.h"
#include "../ADC/DR_ADC.h"
#include "DR_SysTick.h"
#include "../pll/DR_PLL.h"
#include "../Inicializacion/Infotronic.h"
#include "../Temporizadores/PR_Temporizadores.h"

void AagarRGB(void);
void main(void)
{
	InicializarPLL();
	SetDIR(IN0, ENTRADA);
	SetDIR(RELAY1, SALIDA);
	while(1)
	{
		if(GetPIN(IN0,ALTO))
		{
			SetPIN(RELAY1,ON);
		}
		else
		{
			SetPIN(RELAY1,OFF);
		}
	}
}

//void main(void)
//{
//	int adc = 0;
//	InicializarPLL();
//	IniciarDisplay();
//	InicializarSysTick();
//	ADC_init();
//
//	AagarRGB();
//
//	SetDIR(RELAY0, SALIDA);
//	SetDIR(RELAY1, SALIDA);
//	SetDIR(RELAY2, SALIDA);
//	SetPIN(RELAY0,OFF);
//	SetPIN(RELAY2,OFF);
//
//	SetDIR(IN0, ENTRADA);
//
//	while(1)
//	{
//		TimerEvent();
//		adc = ADC_get_average();
//		Display(adc);
//		if(GetPIN(IN0,ALTO))
//		{
//			SetPIN(RELAY1,ON);
//		}
//		else
//		{
//			SetPIN(RELAY1,OFF);
//		}
//	}
//}


void AagarRGB(void)
{
	SetDIR(led0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led2, SALIDA);//Seteo el relay 0 como salida
	SetPIN(led0, OFF);
	SetPIN(led1, OFF);
	SetPIN(led2, OFF);
}
