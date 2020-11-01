/*
 * PR_BMP280.c
 *
 *  Created on: 24 oct. 2020
 *      Author: nico
 */

#ifndef BMP280_PR_BMP280_C_
#define BMP280_PR_BMP280_C_

#include "PR_BMP280.h"
#include "DR_I2C.h"

extern volatile uint8_t  I2CMasterBuffer[BUFSIZE];
extern volatile uint8_t  I2CSlaveBuffer[BUFSIZE];
extern volatile uint32_t I2CCount;
extern volatile uint32_t I2CReadLength;
extern volatile uint32_t I2CWriteLength;

void BMP280Config(void)
{
	  I2CWriteLength = 2;
	  I2CReadLength = 0;
	  I2CMasterBuffer[0] = BMP280_WR;
	  I2CMasterBuffer[1] = 0x00;		/* address */

	/* Write SLA(W), register configuration, SLA(R), and read one byte back. */
//	I2CWriteLength = 5; //Voy a enviar 5 datos de escritura
//	I2CReadLength = 7; //Voy a leer 7 veces
//	I2CMasterBuffer[0] = BMP280_WR;	 //Dirección en modo de escritura
//
//	I2CMasterBuffer[1] = CTRL_MEAS;	 //Dirección del registro a escribir
//	I2CMasterBuffer[2] = MIN_OSRS_T | MIN_OSRS_P | NORMAL_MODE; //Configuración del registro
//
//	I2CMasterBuffer[3] = CONFIG;	 //Dirección del registro a escribir
//	I2CMasterBuffer[4] = T1MS | FILTER_OFF | SPI3E_OFF; //Configuración del registro
//
//	I2CMasterBuffer[5] = BMP280_RD;  //Dirección en modo de lectura
}

#endif /* BMP280_PR_BMP280_C_ */
