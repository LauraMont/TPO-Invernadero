#include "../Inicializacion/tipos.h"


#define 	MAX_DIGITOS      6

extern uint8_t MSG_DSP [ MAX_DIGITOS ];


#define 	PORT0           0
#define 	PORT1           1
#define 	PORT2           2
#define 	PORT3           3
#define 	PORT4           4
#define 	PORT5           5


// PLACA EXPANSION 2
#define 	EXPANSION0		PORT2,7
#define 	EXPANSION1		PORT1,29
#define     EXPANSION2		PORT4,28
#define 	EXPANSION3		PORT1,23
#define 	EXPANSION4   	PORT1,20
#define 	EXPANSION5		PORT0,19
#define 	EXPANSION6	  	PORT3,26
#define 	EXPANSION9	    PORT1,19
#define 	EXPANSION10	    PORT0,20
#define 	EXPANSION11	    PORT3,25
#define 	EXPANSION12     PORT1,27
#define 	EXPANSION13	    PORT1,24
#define 	EXPANSION14    	PORT1,21
#define 	EXPANSION15    	PORT1,18

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
void BarridoDisplay ( void );
void Apagar(void);
void IniciarDisplay(void);

