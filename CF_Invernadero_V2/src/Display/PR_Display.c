#include <DR_Display.h>
#include <PR_Display.h>
#include "../Temporizadores/PR_Temporizadores.h"
#include "../Temporizadores/AP_Temporizadores.h"
#include "../Inicializacion/tipos.h"


void Display( uint32_t dato )
{
    uint8_t i;

    for (i = 0 ; i < MAX_DIGITOS ; i ++)
    {
        MSG_DSP[ MAX_DIGITOS - 1 - i ] = dato % 10;
        dato = dato / 10 ;
    }

    BarridoDisplay();
}

void Display1( int32_t dato , uint8_t dsp )
{

}

void ApagarDisplay(void)
{
	Apagar();
}
