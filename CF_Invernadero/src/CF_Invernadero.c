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

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

#include "DR_tipos.h"
#include "DR_SYSTICK.h"


int main(void)
{
	InicializarPLL();

	Inicializar_systick();

	while(1)
	{

	}
}
