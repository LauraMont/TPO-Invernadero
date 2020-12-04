#include "PR_Display.h"

extern volatile uint8_t display_parpadeo;

static int32_t valor_actual = -1;

volatile uint8_t Tabla_Traduccion[] = { 0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7C, 0x07, 0x7f, 0x6F};

void Display( uint32_t valor )
{
	uint8_t aux;

	valor_actual = valor;

    for (uint8_t idx = 0 ; idx < MAX_DIGITOS ; idx++)
    {
        aux = valor % 10;
        valor /= 10 ;

		if(valor == 0 && aux == 0 && idx != 0) {
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = 0; // Indicación para apagar ceros a la izquierda
		} else {
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = Tabla_Traduccion[aux];
		}
    }
}

void DispDoble( int32_t dsp1 , int32_t  dsp2 )
{
	uint8_t aux;

	int32_t valor = ( (dsp1%1000) * 1000) + (dsp2 % 1000); //El módulo 1000 es una protección por si pasan mas de 3 dígitos

	valor_actual = valor;

    for (uint8_t idx = 0 ; idx < MAX_DIGITOS ; idx++)
    {
        aux = valor % 10;
        valor /= 10 ;

		if(valor == 0 && aux == 0 && idx != 3 )
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = 0; // Indicación para apagar ceros a la izquierda

		else if (aux == 0 && (idx == 1 || idx == 2))//Elimino ceros a la izquierda del segundo display
			MSG_DSP[ MAX_DIGITOS - 1 - idx ] = 0;

		else
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = Tabla_Traduccion[aux];
    }

    MSG_DSP[2] |= (1 << 7);

}

void DispComa( int32_t decimal , int32_t  mantisa )
{
	int32_t valor;
	uint8_t aux;

//	uint8_t digDecimal = CantDigitos(decimal);
	uint8_t digMantisa = CantDigitos(mantisa);

	valor = Pot(10,digMantisa);
	valor *= (decimal%100000);
	valor += (mantisa % 100000); //El módulo 1000 es una protección por si pasan mas de 5 dígitos

	valor_actual = valor;
    for (uint8_t idx = 0 ; idx < MAX_DIGITOS ; idx++)
    {
        aux = valor % 10;
        valor /= 10 ;

		if(valor == 0 && aux == 0 && idx != 0)
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = 0; // Indicación para apagar ceros a la izquierda

		else
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = Tabla_Traduccion[aux];
    }

    MSG_DSP[MAX_DIGITOS - 1 - digMantisa] |= (1 << 7);

}

void DisplayParpadeo(int32_t valor)
{
	uint8_t aux;

	valor_actual = valor;

	display_parpadeo = 1;

    for (uint8_t idx = 0 ; idx < MAX_DIGITOS ; idx++)
    {
        aux = valor % 10;
        valor /= 10 ;

		if(valor == 0 && aux == 0 && idx != 0) {
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = 0; // Indicación para apagar ceros a la izquierda
		} else {
			 MSG_DSP[ MAX_DIGITOS - 1 - idx ] = Tabla_Traduccion[aux];
		}
    }
}

int32_t DisplayGet(void)
{
	return valor_actual;
}

void DisplayClear(void)
{
	uint8_t idx;

	for(idx = 0; idx < MAX_DIGITOS; idx++) {
		MSG_DSP[idx] = 0;
	}

	valor_actual = -1;
}

void DisplayShowAll(void)
{
	uint8_t idx;

	for(idx = 0; idx < MAX_DIGITOS; idx++) {
		MSG_DSP[idx] = 0xFF;
	}

	valor_actual = -1;
}

uint8_t CantDigitos(int32_t numero)
{
	uint8_t digitos = 0;
	while(numero)
	{
        numero /= 10 ;
        digitos ++;
	}
	return digitos;
}

uint32_t Pot(int32_t num, int32_t pot)
{
	uint32_t rta = num;
	for(uint8_t i=1; i < pot; i++ )
	{
		rta *= num;
	}
	return rta;
}

void InicializarDisplay(void)
{
	Display_Init();
}

void ApagarDisplay(void)
{
	Apagar();
}
