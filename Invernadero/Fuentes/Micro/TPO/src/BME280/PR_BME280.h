/*
 * PR_BME280.h
 *
 *  Created on: 24 oct. 2020
 *      Author: nico
 */
#ifndef BME280_PR_BME280_H_
#define BME280_PR_BME280_H_


#include <bme280_defs.h>
#include "DR_I2C.h"
#include "tipos.h"

#define CANT_DATA_REGS 8

#define CANT_CALIB_PARAMS_TP 25
#define CANT_CALIB_PARAMS_H 7

#define BME280_ADDR 0x77
#define RD_BIT 0x01
#define WR_BIT 0x00

#define BME280_RD (BME280_ADDR << 1) | RD_BIT
#define BME280_WR (BME280_ADDR << 1) | WR_BIT

#define CTRL_MEAS 0xF4
#define CONFIG 0xF5

#define T1MS (0x05 << 5)
#define FILTER_OFF (0x00 << 1)
#define SPI3E_OFF 0x00

#define NORMAL_MODE 0x03
#define MIN_OSRS_T (0x01 << 5)
#define MIN_OSRS_P (0x01 << 2)

void BME280_init(uint32_t portNum);
void BME280_get_meas_values(uint32_t portNum);
void bme280_get_uncomp_data(uint8_t * data);

int32_t get_temp(uint32_t portNum);
uint32_t get_pres(uint32_t portNum);
uint32_t get_hum(uint32_t portNum);

void compensate_temp(int32_t *comp_temp, int32_t uncomp_temp);
void compensate_pres(uint32_t *comp_pres, uint32_t uncomp_pres);
void compensate_hum(uint32_t *comp_hum);

void parse_temp_press_calib_data(void);
void parse_humidity_calib_data(void);

#endif /* BME280_PR_BME280_H_ */
