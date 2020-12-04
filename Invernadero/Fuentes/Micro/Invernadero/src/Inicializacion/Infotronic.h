/*
 * Infotronic.h
 *
 *  Created on: 16 sep. 2020
 *      Author: marcelo
 */

#ifndef INICIALIZACION_INFOTRONIC_H_
#define INICIALIZACION_INFOTRONIC_H_

//!< Salidas Digitales
#define		RELAY3			PORT2,0
#define		RELAY2			PORT0,23
#define		RELAY1			PORT0,21
#define		RELAY0			PORT0,27

#define		led0			PORT2,1
#define		led1			PORT2,2
#define		led2			PORT2,3

//!< Leds Exp1
#define    led2_e1			PORT2,7
#define    led3_e1	   		PORT1,29
#define    led4_e1	   		PORT4,28
#define    led5_e1	   		PORT1,23
#define    led6_e1	   		PORT1,20
#define    led7_e1	   		PORT0,19
#define    led1_e1	   		PORT3,26
#define    led0_e1	   		PORT1,25

//!< Entradas Digitales
#define 	IN0				PORT1,26
#define 	IN1				PORT4,29
#define 	IN2				PORT2,11

//!< Teclas (teclado 4x1)
#define		KEY0			PORT2,10
#define		KEY1			PORT0,18
#define		KEY2			PORT0,11
#define		KEY3			PORT2,13

#endif /* INICIALIZACION_INFOTRONIC_H_ */
