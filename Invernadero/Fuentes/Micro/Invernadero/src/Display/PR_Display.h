#include "DR_Display.h"
#include "PR_Temporizadores.h"
#include "AP_Temporizadores.h"
#include "tipos.h"

void Display( uint32_t dato );
void DispDoble( int32_t dsp1 , int32_t dsp2 );
void DispComa( int32_t decimal , int32_t  mantisa );
void DisplayParpadeo(int32_t valor);

int32_t DisplayGet(void);
void DisplayClear(void);
void DisplayShowAll(void);

void ApagarDisplay(void);
void InicializarDisplay(void);

uint8_t CantDigitos(int32_t numero);
uint32_t Pot(int32_t num, int32_t pot);
