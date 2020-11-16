/*
 * PR_BMP280.h
 *
 *  Created on: 24 oct. 2020
 *      Author: nico
 */
#ifndef BMP280_PR_BMP280_H_
#define BMP280_PR_BMP280_H_


#include "DR_I2C.h"
#include "tipos.h"
#include "bmp280_defs.h"

#define CANT_DATA_REGS 6
#define CANT_CALIB_PARAMS 25
#define BMP280_ADDR 0x77
#define RD_BIT 0x01
#define WR_BIT 0x00

#define BMP280_RD (BMP280_ADDR << 1) | RD_BIT
#define BMP280_WR (BMP280_ADDR << 1) | WR_BIT

#define CTRL_MEAS 0xF4
#define CONFIG 0xF5

#define T1MS (0x05 << 5)
#define FILTER_OFF (0x00 << 1)
#define SPI3E_OFF 0x00

#define NORMAL_MODE 0x03
#define MIN_OSRS_T (0x01 << 5)
#define MIN_OSRS_P (0x01 << 2)

void BMP280_init(uint32_t portNum);
void BMP280_get_meas_values(uint32_t portNum);
void bmp280_get_uncomp_data(uint8_t * data);

int32_t get_temp(uint32_t portNum);
uint32_t get_pres(uint32_t portNum);

void get_comp_temp(int32_t *comp_temp, int32_t uncomp_temp);
void get_comp_pres(uint32_t *comp_pres, uint32_t uncomp_pres);

void set_calib_param(void);

#endif /* BMP280_PR_BMP280_H_ */
