#include "DR_I2C.h"
#include "DR_PLL.h"
#include "DR_GPIO.h"
#include "DR_Inicializacion.h"
#include "Infotronic.h"
#include "DR_Display.h"
#include "PR_Display.h"
#include "PR_BMP280.h"




extern volatile uint8_t I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CStatusBuffer[I2C_PORT_NUM][BUFSIZE];

void ApagarLuces(void);
void main(void)
{
	int i=0;
	InicializacionExp1();
	ApagarLuces();
	IniciarDisplay(); //ApagarDisplay();
	SetDIR(1,26, ENTRADA);
	Init_I2C1();
    (void)I2CMasterBuffer;
	BMP280Config();
    (void)I2CMasterBuffer;
//    I2CEngine(); //Va a escribir y leer tantas veces como se configuro en la línea anterior
    I2CStart(1);
    /* Check the content of the Master and slave buffer */
	while(1)
	{
		Display(I2CStatusBuffer[i]);
		if(GetPIN(1,26,BAJO))
		{
			while(GetPIN(1,26,BAJO));
			i++;
		}
		i %=7;
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
