/*
 * PR_BMP280.h
 *
 *  Created on: 24 oct. 2020
 *      Author: nico
 */
#ifndef BMP280_PR_BMP280_H_
#define BMP280_PR_BMP280_H_


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

void BMP280Config(void);

#endif /* BMP280_PR_BMP280_H_ */
