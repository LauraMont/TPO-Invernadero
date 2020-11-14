/*
===============================================================================
 Name        : CF_Invernadero.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include "F_Datos.h"
#include "DR_tipos.h"
#include "DR_SYSTICK.h"


int main(void)
{
	InicializarPLL();

	Inicializar_systick();

	Cargar_Datos_Referencia();

	while(1)
	{
		if(get_ticks == 100)	//Entra cada segundo
		{
			Sys_Control();		//Invoca al systema de control
			reset_ticks();		//Reseteamos el contador
		}
	}
}
