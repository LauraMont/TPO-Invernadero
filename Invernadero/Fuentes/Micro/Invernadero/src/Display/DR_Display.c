#include "DR_Display.h"

volatile uint8_t MSG_DSP [ MAX_DIGITOS ] = {0};

volatile uint8_t display_parpadeo = 0;

void Display_Init(void)
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
	SetDIR(segmento_dp, SALIDA);
}
void BarridoDisplay ()
{
    static int32_t IndiceDisplay = 5;
	static uint32_t contador = 0;
    uint8_t digito;

//    digito = MSG_DSP [ (uint8_t)IndiceDisplay ];

//    if((IndiceDisplay == 2) && (Modo ==CANT_DISP2)) digito |= (1 << 7);

    Apagar();

	if(display_parpadeo)//Como se llama cada 1 ms estará un segundo prendido y 1 segundo apagado
	{
		if(contador < 1000) digito = MSG_DSP[(uint8_t) IndiceDisplay]; // Aca tenemos la traduccion hecha

		else digito = 0;

		contador++;
		contador %= 2000;
	}
	else
	{
		digito = MSG_DSP[(uint8_t)IndiceDisplay]; // Aca tenemos la traduccion hecha
		contador = 0;
	}

    SetPIN( segmento_a , digito & 0x01);
    SetPIN( segmento_b , ( digito >> 1 ) & 0x01);
    SetPIN( segmento_c , ( digito >> 2 ) & 0x01);
    SetPIN( segmento_d , ( digito >> 3 ) & 0x01);
    SetPIN( segmento_e , ( digito >> 4 ) & 0x01);
    SetPIN( segmento_f , ( digito >> 5 ) & 0x01);
    SetPIN( segmento_g , ( digito >> 6 ) & 0x01);
    SetPIN( segmento_dp, ( digito >> 7 ) & 0x01);

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
    if(IndiceDisplay < 0) IndiceDisplay = 5;
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
