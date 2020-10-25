/*******************************************************************************************************************************//**
 *
 * @file		DR_I2C.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		3 oct. 2020
 * @author		Nicolás Taurozzi
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I2C_DR_I2C_H_
#define I2C_DR_I2C_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"
#include "PR_BMP280.h"
#include "DR_GPIO.h"
#include "DR_PLL.h"
#include "PR_Display.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define SDA1 0,0
#define SCL1 0,1

#define MAX_TIMEOUT         0x00FFFFFF
#define BUFSIZE             64
#define TRUE				1
#define FALSE				0

#define I2C_IDLE              0
#define I2C_STARTED           1
#define I2C_RESTARTED         2
#define I2C_REPEATED_START    3
#define DATA_ACK              4
#define DATA_NACK             5
#define I2C_BUSY              6
#define I2C_NO_DATA           7
#define I2C_NACK_ON_ADDRESS   8
#define I2C_NACK_ON_DATA      9
#define I2C_ARBITRATION_LOST  10
#define I2C_TIME_OUT          11
#define I2C_OK                12
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define			ISER0		(*(uint32_t *)(0xE000E100))

#define I2C ((I2C_t*)0x4001C000)

#define I2CONSET		I2C->_I2CONSET
#define I2STAT			I2C->_I2STAT
#define I2DAT			I2C->_I2DAT
#define I2ADR0			I2C->_I2ADR0
#define I2SCLH			I2C->_I2SCLH
#define I2SCLL			I2C->_I2SCLL
#define I2CONCLR		I2C->_I2CONCLR
#define I2MMCTRL		I2C->_I2MMCTRL
#define I2DATA_BUFFER	I2C->_I2DATA_BUFFER
#define I2ADR1			I2C->_I2ADR1
#define I2ADR2			I2C->_I2ADR2
#define I2ADR3			I2C->_I2ADR3
#define I2MASK0			I2C->_I2MASK0
#define I2MASK1			I2C->_I2MASK1
#define I2MASK2			I2C->_I2MASK2
#define I2MASK3			I2C->_I2MASK3

//#define 	SYSTICK		( (systick_t *) 0xE000E010UL )
//
//#define		STCTRL		SYSTICK->_STCTRL
//
//	#define	ENABLE			SYSTICK->bits._ENABLE
//	#define	TICKINT			SYSTICK->bits._TICKINT
//	#define	CLKSOURCE		SYSTICK->bits._CLKSOURCE
//	#define	COUNTFLAG		SYSTICK->bits._COUNTFLAG
//
//#define		STRELOAD	SYSTICK->_STRELOAD
//#define		STCURR		SYSTICK->_STCURR
//#define		STCALIB		SYSTICK->_STCALIB


/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef struct
{
	struct
	{
		__RW uint32_t RESERVED0:2;
		__RW uint32_t AA:1;   //Acknowledge flag
		__RW uint32_t SI:1;   //I2C interrupt flag
		__RW uint32_t STO:1;  //STOP flag
		__RW uint32_t STA:1;  //START flag
		__RW uint32_t I2EN:1; //I2C interface enable
		__RW uint32_t RESERVED1:25;
	}_I2CONSET;//I2C Control Set Register

	struct
	{
		__RW uint32_t UNUSED:3;
		__RW uint32_t STATUS:5;//Actual status information about the I2C interface
		__RW uint32_t RESERVED0:24;
	}_I2STAT;

	struct
	{
		__RW uint32_t DATA:8; //Data to be received or transmitted
		__RW uint32_t RESERVED0:24;
	}_I2DAT;

	struct
	{
		__RW uint32_t GC:1; // General Call enable bit.
		__RW uint32_t ADDRESS:7;// The I2C device address for slave mode.
		__RW uint32_t RESERVED0:24;
	}_I2ADR0;//Contains the 7-bit slave address

	struct
	{
		__RW uint16_t SCLH:16;// Count for SCL HIGH time period selection.
		__RW uint16_t RESERVED0:16;
	}_I2SCLH;

	struct
	{
		__RW uint16_t SCLL:16;// Count for SCL HIGH time period selection.
		__RW uint16_t RESERVED0:16;
	}_I2SCLL;

	struct
	{
		__RW uint32_t RESERVED0:2;
		__RW uint32_t AAC:1;        //Assert acknowledge Clear bit.
		__RW uint32_t SIC:1;        //I2C interrupt Clear bit.
		__RW uint32_t RESERVED1:1;
		__RW uint32_t STAC:1;       //START flag Clear bit.
		__RW uint32_t I2ENC:1;      //I2C interface Disable bit.le
		__RW uint32_t RESERVED2:25;

	}_I2CONCLR;

	struct
	{
		__RW uint32_t MM_ENA:1;
		__RW uint32_t ENA_SCL:1;//Actual status information about the I2C interface
		__RW uint32_t MATCH_ALL:24;
		__RW uint32_t RESERVED0:24;
	}_I2MMCTRL;

	__RW uint32_t _I2ADR1;//Contains the 7-bit slave address
	__RW uint32_t _I2ADR2;//Contains the 7-bit slave address
	__RW uint32_t _I2ADR3;//Contains the 7-bit slave address

	struct
	{
		__RW uint32_t DATA:8; //Data to be received or transmitted
		__RW uint32_t RESERVED0:24;
	}_I2DATA_BUFFER;;

	__RW uint32_t _I2MASK0;//Mask register associated with I2ADR0
	__RW uint32_t _I2MASK1;//Mask register associated with I2ADR1
	__RW uint32_t _I2MASK2;//Mask register associated with I2ADR2
	__RW uint32_t _I2MASK3;//Mask register associated with I2ADR3
}I2C_t;


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern type nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Init_I2C1(void);
void ClearFlags(void);
uint8_t I2CStop( void );
uint8_t I2CEngine();
extern void I2C1_IRQHandler( void );

#endif /* I2C_DR_I2C_H_ */
