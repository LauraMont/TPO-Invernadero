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
#define I2C_PORT_NUM        3

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

#define I2CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2CONSET_AA         (0x1<<2)
#define I2CONSET_SI         (0x1<<3)
#define I2CONSET_STO        (0x1<<4)
#define I2CONSET_STA        (0x1<<5)

#define I2CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (0x1<<3)
#define I2CONCLR_STAC       (0x1<<5)
#define I2CONCLR_I2ENC      (0x1<<6)
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define	ISER0 (*(uint32_t *)0xE000E100UL)

#define I2C0 ((I2C_t*)0x4001C000UL)
#define I2C1 ((I2C_t*)0x4005C000UL)
#define I2C2 ((I2C_t*)0x400A0000UL)

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef struct
{
  __RW uint32_t CONSET;                     /*!< Offset: 0x000 (R/W)  I2C Control Set Register */
  __R  uint32_t STAT;                       /*!< Offset: 0x004 (R/ )  I2C Status Register */
  __RW uint32_t DAT;                        /*!< Offset: 0x008 (R/W)  I2C Data Register */
  __RW uint32_t ADR0;                       /*!< Offset: 0x00C (R/W)  I2C Slave Address Register 0 */
  __RW uint32_t SCLH;                       /*!< Offset: 0x010 (R/W)  SCH Duty Cycle Register High Half Word */
  __RW uint32_t SCLL;                       /*!< Offset: 0x014 (R/W)  SCL Duty Cycle Register Low Half Word */
  __RW uint32_t CONCLR;                     /*!< Offset: 0x018 (R/W)  I2C Control Clear Register */
  __RW uint32_t MMCTRL;                     /*!< Offset: 0x01C (R/W)  Monitor mode control register */
  __RW uint32_t ADR1;                       /*!< Offset: 0x020 (R/W)  I2C Slave Address Register 1 */
  __RW uint32_t ADR2;                       /*!< Offset: 0x024 (R/W)  I2C Slave Address Register 2 */
  __RW uint32_t ADR3;                       /*!< Offset: 0x028 (R/W)  I2C Slave Address Register 3 */
  __R  uint32_t DATA_BUFFER;                /*!< Offset: 0x02C (R/ )  Data buffer Register */
  __RW uint32_t MASK0;                      /*!< Offset: 0x030 (R/W)  I2C Slave address mask register 0 */
  __RW uint32_t MASK1;                      /*!< Offset: 0x034 (R/W)  I2C Slave address mask register 1 */
  __RW uint32_t MASK2;                      /*!< Offset: 0x038 (R/W)  I2C Slave address mask register 2 */
  __RW uint32_t MASK3;                      /*!< Offset: 0x03C (R/W)  I2C Slave address mask register 3 */
} I2C_t;



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern type nombreVariable;


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Init_I2C1(void);
uint8_t I2CStop( uint32_t portNum );
uint8_t I2CEngine();
uint32_t I2CStart( uint32_t portNum );
extern void I2C1_IRQHandler( void );

/*
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
	}_I2CCONSET;//I2C Control Set Register

	struct
	{
		__RW uint32_t UNUSED:3;
		__W uint32_t  STATUS:5;//Actual status information about the I2C interface
		__RW uint32_t RESERVED0:24;
	}_I2CSTAT;

	struct
	{
		__RW uint32_t DATA:8; //Data to be received or transmitted
		__RW uint32_t RESERVED0:24;
	}_I2CDAT;

	struct
	{
		__RW uint32_t GC:1; // General Call enable bit.
		__RW uint32_t ADDRESS:7;// The I2C device address for slave mode.
		__RW uint32_t RESERVED0:24;
	}_I2CADR0;//Contains the 7-bit slave address

	struct
	{
		__RW uint16_t SCLH:16;// Count for SCL HIGH time period selection.
		__RW uint16_t RESERVED0:16;
	}_I2CSCLH;

	struct
	{
		__RW uint16_t SCLL:16;// Count for SCL HIGH time period selection.
		__RW uint16_t RESERVED0:16;
	}_I2CSCLL;

	struct
	{
		__RW uint32_t RESERVED0:2;
		__RW uint32_t AAC:1;        //Assert acknowledge Clear bit.
		__RW uint32_t SIC:1;        //I2C interrupt Clear bit.
		__RW uint32_t RESERVED1:1;
		__RW uint32_t STAC:1;       //START flag Clear bit.
		__RW uint32_t I2ENC:1;      //I2C interface Disable bit.le
		__RW uint32_t RESERVED2:25;

	}_I2CCONCLR;

	struct
	{
		__RW uint32_t MM_ENA:1;
		__RW uint32_t ENA_SCL:1;//Actual status information about the I2C interface
		__RW uint32_t MATCH_ALL:24;
		__RW uint32_t RESERVED0:24;
	}_I2CMMCTRL;

	__RW uint32_t _I2ADR1;//Contains the 7-bit slave address
	__RW uint32_t _I2ADR2;//Contains the 7-bit slave address
	__RW uint32_t _I2ADR3;//Contains the 7-bit slave address

	struct
	{
		__RW uint32_t DATA:8; //Data to be received or transmitted
		__RW uint32_t RESERVED0:24;
	}_I2CDATA_BUFFER;;

	__RW uint32_t _I2MASK0;//Mask register associated with I2ADR0
	__RW uint32_t _I2MASK1;//Mask register associated with I2ADR1
	__RW uint32_t _I2MASK2;//Mask register associated with I2ADR2
	__RW uint32_t _I2MASK3;//Mask register associated with I2ADR3
}I2C_t;

*/

#endif /* I2C_DR_I2C_H_ */
