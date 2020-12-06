#include "DR_GPIO.h"
#include "DR_SysTick.h"
#include "PR_Temporizadores.h"
#include "AP_Temporizadores.h"
#include "tipos.h"

#define 	MAX_DIGITOS      6

extern volatile uint8_t MSG_DSP [ MAX_DIGITOS ];

extern volatile uint8_t cantDispl;

//Modos
#define 	CANT_DISP1 		1
#define 	CANT_DISP2 		2
#define 	COMA 			3

#define    	digito0        		EXPANSION0
#define    	digito1        		EXPANSION1
#define    	digito2        		EXPANSION2
#define     digito3       		EXPANSION3
#define     digito4        		EXPANSION4
#define     digito5       		EXPANSION5
#define     segmento_a         	EXPANSION6
#define     segmento_dp        	EXPANSION9
#define     segmento_g         	EXPANSION10
#define    	segmento_f         	EXPANSION11
#define 	segmento_e          EXPANSION12
#define 	segmento_d          EXPANSION13
#define 	segmento_c          EXPANSION14
#define 	segmento_b          EXPANSION15

/*Includes*/
void BarridoDisplay();
void Apagar(void);
void Display_Init(void);

