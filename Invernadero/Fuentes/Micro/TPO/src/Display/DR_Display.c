#include "DR_Display.h"
#include "../Temporizadores/PR_Temporizadores.h"
#include "../Temporizadores/AP_Temporizadores.h"
#include "../Inicializacion/tipos.h"
#include "DR_GPIO.h"
#include "DR_SysTick.h"
uint8_t MSG_DSP [ MAX_DIGITOS ] = {0};

uint8_t Tabla_Digitos_BCD_7seg[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7C, 0x07, 0x7f, 0x6F};

void IniciarDisplay(void)
{
	SetDIR(digito0, SALIDA);
	SetDIR(digito1, SALIDA);
	SetDIR(digito2, SALIDA);
	SetDIR(digito3, SALIDA);
	SetDIR(digito4, SALIDA);
	SetDIR(digito5, SALIDA);

	SetDIR(segmento_a, SALIDA);
	SetDIR(segmento_b, SALIDA);
	SetDIR(segmento_c, SALIDA);
	SetDIR(segmento_d, SALIDA);
	SetDIR(segmento_e, SALIDA);
	SetDIR(segmento_f, SALIDA);
	SetDIR(segmento_g, SALIDA);
}
void BarridoDisplay ( void )
{
    static uint8_t IndiceDisplay = 5;
    uint8_t digito;

    digito = Tabla_Digitos_BCD_7seg [ MSG_DSP [ IndiceDisplay ] ];

    Apagar();

    SetPIN( segmento_a , digito & 0x01);
    SetPIN( segmento_b , ( digito >> 1 ) & 0x01);
    SetPIN( segmento_c , ( digito >> 2 ) & 0x01);
    SetPIN( segmento_d , ( digito >> 3 ) & 0x01);
    SetPIN( segmento_e , ( digito >> 4 ) & 0x01);
    SetPIN( segmento_f , ( digito >> 5 ) & 0x01);
    SetPIN( segmento_g , ( digito >> 6 ) & 0x01);

    switch (IndiceDisplay)
    {
        case 5:
            SetPIN( digito0 , ON );
            break;
        case 4:
            SetPIN( digito1 , ON );
            break;
        case 3:
            SetPIN( digito2 , ON );
            break;
        case 2:
            SetPIN( digito3 , ON );
            break;
        case 1:
            SetPIN( digito4 , ON );
            break;
        case 0:
            SetPIN( digito5 , ON );
            break;
    }
    IndiceDisplay --;
    if(IndiceDisplay <0) IndiceDisplay = 5;

    TimerStart(0,1,Ev_Display,DEC);
}

void Apagar(void)
{
    SetPIN( digito0 , OFF );
    SetPIN( digito1 , OFF );
    SetPIN( digito2 , OFF );
    SetPIN( digito3 , OFF );
    SetPIN( digito4 , OFF );
    SetPIN( digito5 , OFF );
}
