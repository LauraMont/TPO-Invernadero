/*
 * PR_BMP280.c
 *
 *  Created on: 24 oct. 2020
 *      Author: nico
 */

#ifndef BMP280_PR_BMP280_C_
#define BMP280_PR_BMP280_C_

#include "PR_BMP280.h"

extern volatile uint8_t I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];

extern volatile uint32_t I2CReadLength[I2C_PORT_NUM];
extern volatile uint32_t I2CWriteLength[I2C_PORT_NUM];

volatile uint8_t calib_data[CANT_CALIB_PARAMS];
volatile uint8_t meas_data[CANT_DATA_REGS];

volatile struct bmp280_dev bmp;

static uint32_t pres;
static int32_t temp;
/*!
 * @brief Guarda en MasterBuffer las direcciones de los registros
 * que se van a configurar y la configuracion de cada uno. Luego lee
 * los parametros de calibracion y los deja configurados.
 */
void BMP280_init(uint32_t portNum)
{
	/* Write SLA(W), register configuration, SLA(R), and read one byte back. */
	I2CWriteLength[portNum] = 6; //Voy a enviar 5 datos de escritura

	I2CReadLength[portNum] = 25; //Voy a leer 25 datos

	I2CMasterBuffer[portNum][0] = BMP280_WR;	 //Dirección en modo de escritura

	I2CMasterBuffer[portNum][1] = CTRL_MEAS;	 //Dirección del registro a escribir
	I2CMasterBuffer[portNum][2] = MIN_OSRS_T | MIN_OSRS_P | NORMAL_MODE; //Configuración del registro

	I2CMasterBuffer[portNum][3] = CONFIG;	 //Dirección del registro a escribir
	I2CMasterBuffer[portNum][4] = T1MS | FILTER_OFF | SPI3E_OFF; //Configuración del registro

	I2CMasterBuffer[portNum][5] = 0x88; //Registro del que comenzar a leer

	I2CMasterBuffer[portNum][6] = BMP280_RD;  //Dirección en modo de lectura

	I2CEngine(portNum); //Va a escribir y leer tantas veces como se configuro en las líneas anteriores

	for(int i=0; i < CANT_CALIB_PARAMS; i++) //Guardo los parámetros de calibración
		{calib_data[i] = I2CSlaveBuffer[1][i];}

	set_calib_param();
}

void BMP280_get_meas_values(uint32_t portNum)
{
	I2CReadLength[portNum] = 6;

	I2CMasterBuffer[portNum][5] = 0xF7; //Registro del que comenzar a leer

	I2CEngine(1); //Va a escribir y leer tantas veces como se configuro en las líneas anteriores

	for(int i=0; i < CANT_DATA_REGS; i++) //Guardo los parámetros de las medidas
		{meas_data[i] = I2CSlaveBuffer[1][i];}
}



void BMP280_get_measure(uint8_t * data)
{
    struct bmp280_uncomp_data uncomp_data;

	bmp280_get_uncomp_data(&uncomp_data,data);

	get_comp_temp(&temp, uncomp_data.uncomp_temp, &bmp);
	get_comp_pres(&pres, uncomp_data.uncomp_press, &bmp);
}

int32_t get_temp(void)
{
	return temp;
}

uint32_t get_pres(void)
{
	return pres;
}

/*!
 * @brief This API reads the temperature and pressure data registers.
 * It gives the raw temperature and pressure data .
 */
void bmp280_get_uncomp_data(struct bmp280_uncomp_data *uncomp_data, uint8_t * data)
{
	uncomp_data->uncomp_press =
		(int32_t) ((((uint32_t) (data[0])) << 12) | (((uint32_t) (data[1])) << 4) | ((uint32_t) data[2] >> 4));
	uncomp_data->uncomp_temp =
		(int32_t) ((((int32_t) (data[3])) << 12) | (((int32_t) (data[4])) << 4) | (((int32_t) (data[5])) >> 4));

}

/*!
 * @brief This API is used to get the compensated temperature from
 * uncompensated temperature. This API uses 32 bit integers.
 */
void get_comp_temp(int32_t *comp_temp, int32_t uncomp_temp, struct bmp280_dev *dev)
{
    int32_t var1, var2;

    var1 =
		((((uncomp_temp / 8) - ((int32_t) dev->calib_param.dig_t1 << 1))) * ((int32_t) dev->calib_param.dig_t2)) / 2048;

	var2 =
		(((((uncomp_temp / 16) - ((int32_t) dev->calib_param.dig_t1)) *
		   ((uncomp_temp / 16) - ((int32_t) dev->calib_param.dig_t1))) / 4096) * ((int32_t) dev->calib_param.dig_t3)) / 16384;

	dev->calib_param.t_fine = var1 + var2;
	*comp_temp = (dev->calib_param.t_fine * 5 + 128) / 256;
}

/*!
 * @brief This API is used to get the compensated pressure from
 * uncompensated pressure. This API uses 32 bit integers.
 */
void get_comp_pres(uint32_t *comp_pres, uint32_t uncomp_pres, const struct bmp280_dev *dev)
{
    int32_t var1, var2;

	var1 = (((int32_t) dev->calib_param.t_fine) / 2) - (int32_t) 64000;
	var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t) dev->calib_param.dig_p6);
	var2 = var2 + ((var1 * ((int32_t) dev->calib_param.dig_p5)) * 2);
	var2 = (var2 / 4) + (((int32_t) dev->calib_param.dig_p4) * 65536);
	var1 =
		(((dev->calib_param.dig_p3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8) +
		 ((((int32_t) dev->calib_param.dig_p2) * var1) / 2)) / 262144;
	var1 = ((((32768 + var1)) * ((int32_t) dev->calib_param.dig_p1)) / 32768);
	*comp_pres = (uint32_t)(((int32_t)(1048576 - uncomp_pres) - (var2 / 4096)) * 3125);

	/* Avoid exception caused by division with zero */
	if (var1 != 0)
	{
		/* Check for overflows against UINT32_MAX/2; if pres is left-shifted by 1 */
		if (*comp_pres < 0x80000000)
		{
			*comp_pres = (*comp_pres << 1) / ((uint32_t) var1);
		}
		else
		{
			*comp_pres = (*comp_pres / (uint32_t) var1) * 2;
		}
		var1 = (((int32_t) dev->calib_param.dig_p9) * ((int32_t) (((*comp_pres / 8) * (*comp_pres / 8)) / 8192))) /
			   4096;
		var2 = (((int32_t) (*comp_pres / 4)) * ((int32_t) dev->calib_param.dig_p8)) / 8192;
		*comp_pres = (uint32_t) ((int32_t) *comp_pres + ((var1 + var2 + dev->calib_param.dig_p7) / 16));

    }
}

/*!
 * @brief This API is used to read the calibration parameters used
 * for calculating the compensated data.
 */
void set_calib_param(struct bmp280_dev *dev)
{
    dev->calib_param.dig_t1 =
        (uint16_t)(((uint16_t) calib_data[BMP280_DIG_T1_MSB_POS] << 8) | ((uint16_t) calib_data[BMP280_DIG_T1_LSB_POS]));
    dev->calib_param.dig_t2 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_T2_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_T2_LSB_POS]));
    dev->calib_param.dig_t3 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_T3_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_T3_LSB_POS]));
    dev->calib_param.dig_p1 =
        (uint16_t)(((uint16_t) calib_data[BMP280_DIG_P1_MSB_POS] << 8) | ((uint16_t) calib_data[BMP280_DIG_P1_LSB_POS]));
    dev->calib_param.dig_p2 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P2_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P2_LSB_POS]));
    dev->calib_param.dig_p3 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P3_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P3_LSB_POS]));
    dev->calib_param.dig_p4 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P4_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P4_LSB_POS]));
    dev->calib_param.dig_p5 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P5_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P5_LSB_POS]));
    dev->calib_param.dig_p6 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P6_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P6_LSB_POS]));
    dev->calib_param.dig_p7 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P7_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P7_LSB_POS]));
    dev->calib_param.dig_p8 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P8_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P8_LSB_POS]));
    dev->calib_param.dig_p9 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P9_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P9_LSB_POS]));
}

#endif /* BMP280_PR_BMP280_C_ */
