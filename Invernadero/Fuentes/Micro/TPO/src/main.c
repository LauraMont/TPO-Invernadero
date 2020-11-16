#include "DR_I2C.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"
#include "DR_Inicializacion.h"
#include "Infotronic.h"
#include "PR_Display.h"
#include "PR_BMP280.h"
#include "AP_Temporizadores.h"
#include "PR_Temporizadores.h"



extern volatile uint8_t I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CStatusBuffer[I2C_PORT_NUM][BUFSIZE];

extern uint8_t	fEventoTiempo_1;

void ApagarLuces(void);
void main(void)
{
	int i=0;
	int32_t mediciones[2] = {0};
	InicializacionExp1();
	ApagarLuces();
	SetDIR(1,26, ENTRADA);

	IniciarDisplay();
	Init_I2C1();
	BMP280_init(1); //Configura los parámetros de medición y toma los valores necesarios
	mediciones[0] = get_temp(1);
	mediciones[1] = get_pres(1);
//   TimerStart( 1, 1, Ev_Estado1, SEG );      Las líneas comentadas son para que la medición se repita cada 1 segundo
	while(1)
	{
//		TimerEvent();
//		if(fEventoTiempo_1)
//		{
//			mediciones[0] = get_temp(1);
//			mediciones[1] = get_pres(1);
//		}
		Display(mediciones[i]);
		if(GetPIN(1,26,BAJO))
		{
			while(GetPIN(1,26,BAJO));
			i++;
		}
		i %=2;
	}
}

void ApagarLuces(void)
{
	SetDIR(led0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(led2, SALIDA);//Seteo el relay 0 como salida

	SetDIR(RELAY0, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY1, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY2, SALIDA);//Seteo el relay 0 como salida
	SetDIR(RELAY3, SALIDA);//Seteo el relay 0 como salida

	SetPIN(led0, OFF);
	SetPIN(led1, OFF);
	SetPIN(led2, OFF);

	SetPIN(RELAY0, OFF);
	SetPIN(RELAY1, OFF);
	SetPIN(RELAY2, OFF);
	SetPIN(RELAY3, OFF);

}
