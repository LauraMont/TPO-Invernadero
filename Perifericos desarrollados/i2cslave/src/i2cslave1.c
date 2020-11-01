/****************************************************************************
 *   $Id:: i2cslave1.c 5866 2010-12-08 21:44:48Z usb00423                   $
 *   Project: NXP LPC17xx I2C Slave example
 *
 *   Description:
 *     This file contains I2C slave code example which include I2C slave 
 *     initialization, I2C interrupt handler, and APIs for I2C slave access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "i2cslave.h"

extern volatile uint8_t I2CWrBuffer[BUFSIZE];
extern volatile uint8_t I2CRdBuffer[BUFSIZE];
extern volatile uint32_t I2CSlaveState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;
extern volatile uint32_t RdIndex, WrIndex;

/* 
From device to device, the I2C communication protocol may vary, 
in the example below, the protocol uses repeated start to read data from or 
write to the device:
For master read: the sequence is: STA,Addr(W),offset,RE-STA,Addr(r),data...STO 
for master write: the sequence is: STA,Addr(W),offset,RE-STA,Addr(w),data...STO
Thus, in state 8, the address is always WRITE. in state 10, the address could 
be READ or WRITE depending on the I2C command.
*/   

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
void I2C1_IRQHandler(void) 
{
  uint8_t StatValue;

  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C1->STAT;
  switch ( StatValue )
  {
	case 0x60:					/* An own SLA_W has been received. */
	case 0x68:
	RdIndex = 0;
	LPC_I2C1->CONSET = I2CONSET_AA;	/* assert ACK after SLV_W is received */
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_WR_STARTED;
	break;
	
	case 0x80:					/*  data receive */
	case 0x90:
	if ( I2CSlaveState == I2C_WR_STARTED )
	{
	  I2CRdBuffer[RdIndex++] = LPC_I2C1->DAT;
	  LPC_I2C1->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
	}
	else
	{
	  LPC_I2C1->CONCLR = I2CONCLR_AAC;	/* assert NACK */
	}
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	break;
		
	case 0xA8:					/* An own SLA_R has been received. */
	case 0xB0:
	RdIndex = 0;
	LPC_I2C1->CONSET = I2CONSET_AA;	/* assert ACK after SLV_R is received */
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_RD_STARTED;
	WrIndex = I2CRdBuffer[0];	/* The 1st byte is the index. */
	break;
	
	case 0xB8:					/* Data byte has been transmitted */
	case 0xC8:
	if ( I2CSlaveState == I2C_RD_STARTED )
	{
	  LPC_I2C1->DAT = I2CRdBuffer[WrIndex+1];/* write the same data back to master */
	  WrIndex++;							/* Need to skip the index byte in RdBuffer */
	  LPC_I2C1->CONSET = I2CONSET_AA;		/* assert ACK  */
	}
	else
	{
	  LPC_I2C1->CONCLR = I2CONCLR_AAC;		/* assert NACK  */
	}	
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	break;

	case 0xC0:					/* Data byte has been transmitted, NACK */
	LPC_I2C1->CONCLR = I2CONCLR_AAC;			/* assert NACK  */
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = DATA_NACK;
	break;

	case 0xA0:					/* Stop condition or repeated start has */
	LPC_I2C1->CONSET = I2CONSET_AA;	/* been received, assert ACK.  */
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	I2CSlaveState = I2C_IDLE;
	break;

	default:
	LPC_I2C1->CONCLR = I2CONCLR_SIC;
	LPC_I2C1->CONSET = I2CONSET_I2EN | I2CONSET_SI;	
	break;
  }
  return;
}

/*****************************************************************************
** Function name:		I2CSlaveInit
**
** Descriptions:		Initialize I2C controller
**
** parameters:			I2c mode is either MASTER or SLAVE
** Returned value:		true or false, return false if the I2C
**				interrupt handler was not installed correctly
** 
*****************************************************************************/
void I2CSlave1Init( void ) 
{
  LPC_SC->PCONP |= (1 << 19);

#if 1
  /* set PIO0.0 and PIO0.1 to I2C1 SDA and SCL */
  /* function to 11 on both SDA and SCL. */
  LPC_PINCON->PINSEL0 &= ~((0x3<<0)|(0x3<<2));
  LPC_PINCON->PINSEL0 |= ((0x3<<0)|(0x3<<2));
  LPC_PINCON->PINMODE0 &= ~((0x3<<0)|(0x3<<2));
  LPC_PINCON->PINMODE0 |= ((0x2<<0)|(0x2<<2));		/* No pull-up no pull-down */
  LPC_PINCON->PINMODE_OD0 |= ((0x01<<0)|(0x1<<1));	/* Open drain */	
#endif
#if 0
  /* set PIO0.19 and PIO0.20 to I2C1 SDA and SCL */
  /* function to 11 on both SDA and SCL. */
  LPC_PINCON->PINSEL1 &= ~((0x3<<6)|(0x3<<8));
  LPC_PINCON->PINSEL1 |= ((0x3<<6)|(0x3<<8));
  LPC_PINCON->PINMODE1 &= ~((0x3<<6)|(0x3<<8));
  LPC_PINCON->PINMODE1 |= ((0x2<<6)|(0x2<<8));	/* No pull-up no pull-down */
  LPC_PINCON->PINMODE_OD0 |= ((0x1<<19)|(0x1<<20));	
#endif

  /*--- Clear flags ---*/
  LPC_I2C1->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  LPC_I2C1->SCLL   = I2SCLL_SCLL;
  LPC_I2C1->SCLH   = I2SCLH_SCLH;

  LPC_I2C1->ADR0 = PCF8594_ADDR;    
  I2CSlaveState = I2C_IDLE;
  
  /* Enable the I2C Interrupt */
  NVIC_EnableIRQ(I2C1_IRQn);
  LPC_I2C1->CONSET = I2CONSET_I2EN | I2CONSET_SI;
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/

