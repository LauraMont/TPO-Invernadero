/*
 * F_MdE.h
 *
 *  Created on: Nov 1, 2020
 *      Author: laura
 */

#ifndef F_MDE_H_
#define F_MDE_H_

#include "DR_tipos.h"

uint32_t Get_Temperatura();
void Set_Temperatura(int32_t);

void Encender_Lampara();
void Apagar_Lampara();

uint32_t Get_N_agua();
void Set_N_Agua(int32_t);

uint32_t Get_Humedad_T();
void Set_Humedad_T(int32_t);

uint32_t Get_Humedad_A();
void Set_Humedad_A(int32_t);

void Encender_Riego();
void Apagar_Riego();

void Apagar_Ventilacion ();
void Encender_Ventilacion ();

void Sys_Ventilacion();		//Prende y apaga la ventilacion en determinado tiempo

void Sys_Iluminacion();

#endif /* F_MDE_H_ */
