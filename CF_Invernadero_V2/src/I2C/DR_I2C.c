/*******************************************************************************************************************************//**
 *
 * @file		I2C.c
 * @brief		Descripcion del modulo
 * @date		3 oct. 2020
 * @author		Nicolás Taurozzi
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_I2C.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint8_t  I2CMasterState;
volatile uint32_t timeout = 0;
volatile uint8_t  I2CMasterBuffer[BUFSIZE];
volatile uint8_t  I2CSlaveBuffer[BUFSIZE];
volatile uint32_t I2CCount;
volatile uint32_t I2CReadLength;
volatile uint32_t I2CWriteLength;
volatile uint32_t RdIndex1 = 0;
volatile uint32_t WrIndex1 = 0;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 3 oct. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void Init_I2C1(void)
{
	PCONP |= (1 << 19); //Energizo el I2C

	PCLKSEL1 &= ~(0x03 << 6); //Activo el clock

	//Configuro los pins
	SetPINSEL(SCL1,3);  //SCL
	SetPINSEL(SDA1,3); //SDA

	SetPINMODE(SCL1,2); //Seteo el Open-drain mode
	SetPINMODE(SDA1,2);

	SetPINMODE_OD(SCL1,1); //Seteo el Open-drain mode
	SetPINMODE_OD(SDA1,1);

	ClearFlags();

	I2SCLH.SCLH = 0x80;
	I2SCLL.SCLL = 0x80;

	I2CONSET.I2EN = 1; //Habilito el I2C

	ISER0 |= (1 << 11); //Habilito interrupciones
}

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

  timeout = 0;
  /* this handler deals with master read and master write only */
  StatValue = I2STAT.STATUS;
  Display(StatValue);
  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
		WrIndex1 = 0;
		I2DAT.DATA= I2CMasterBuffer[WrIndex1++];
		I2CONCLR.SIC = 1;
		I2CONCLR.STAC = 1;
		break;

	case 0x10:			/* A repeated started is issued */
		RdIndex1 = 0;
		/* Send SLA with R bit set, */
		I2DAT.DATA = I2CMasterBuffer[WrIndex1++];
		I2CONCLR.SIC = 1;
		I2CONCLR.STAC = 1;
		break;

	case 0x18:			/* SLA+W has been transmitted; ACK has been received. */
		if ( I2CWriteLength == 1 )
		{
		  I2CONSET.STO = 1;      /* Set Stop flag */
		  I2CMasterState = I2C_NO_DATA;
		}
		else
		{
		  I2DAT.DATA = I2CMasterBuffer[WrIndex1++];
		}
		I2CONCLR.SIC = 1;
		break;

	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
		if ( WrIndex1 < I2CWriteLength )
		{
		  I2DAT.DATA = I2CMasterBuffer[WrIndex1++]; /* this should be the last one */
		}
		else
		{
		  if ( I2CReadLength != 0 )
		  {
			I2CONSET.STA = 1;	/* Set Repeated-start flag */
		  }
		  else
		  {
			I2CONSET.STO = 1;      /* Set Stop flag */
			I2CMasterState = I2C_OK;
		  }
		}
		I2CONCLR.SIC = 1;
		break;

	case 0x30: /*Data byte in I2DAT has been transmitted, NOT ACK  has been received.*/
		I2CONSET.STO = 1;      /* Set Stop flag */
		I2CMasterState = I2C_NACK_ON_DATA;
		I2CONCLR.SIC = 1;
		break;

	case 0x40:	/* Master Receive, SLA_R has been sent */
		if ( (RdIndex1 + 1) < I2CReadLength )
		{
		  /* Will go to State 0x50 */
		  I2CONSET.AA = 1;	/* assert ACK after data is received */
		}
		else
		{
		  /* Will go to State 0x58 */
		  I2CONCLR.AAC = 1;	/* assert NACK after data is received */
		}
		I2CONCLR.SIC = 1;
		break;

	case 0x50:	/* Data byte has been received, ACK was received */
		I2CSlaveBuffer[RdIndex1++] = I2DAT.DATA;
		if ( (RdIndex1 + 1) < I2CReadLength )
		{
		  I2CONSET.AA = 1;	/* assert ACK after data is received */
		}
		else
		{
		  I2CONCLR.AAC = 1;	/* assert NACK on last byte */
		}
		I2CONCLR.SIC = 1;
	break;

	case 0x58: /* Data byte has been received, NOT ACK was received */
		I2CSlaveBuffer[RdIndex1++] = I2DAT.DATA;
		I2CMasterState = I2C_OK;
		I2CONSET.STO = 1;	/* Set Stop flag */
		I2CONCLR.SIC = 1;	/* Clear SI flag */
		break;

	case 0x20:		/* SLA+W has been transmitted; NOT ACK has been received. */
		case 0x48:
		I2CONSET.STO = 1;      /* Set Stop flag */
		I2CMasterState = I2C_NACK_ON_ADDRESS;
		I2CONCLR.SIC = 1;
		break;

	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
		I2CMasterState = I2C_ARBITRATION_LOST;
		I2CONCLR.SIC = 1;
		break;
  }
  return;
}


/*****************************************************************************
** Function name:		I2CStop
**
** Descriptions:		Set the I2C stop condition, if the routine
**				never exit, it's a fatal bus error.
**
** parameters:			None
** Returned value:		true or never return
**
*****************************************************************************/
uint8_t I2CStop( void )
{
  I2CONSET.STO = 1;      /* Set Stop flag */
  I2CONCLR.SIC = 1;  /* Clear SI flag */

  /*--- Wait for STOP detected ---*/
  while(I2CONSET.STO);
  return TRUE;
}


/*****************************************************************************
** Function name:		ClearFlags
**
** Descriptions:		Clear all I2CONSET flags
**
** parameters:			None
** Returned value:		None
**
*****************************************************************************/
void ClearFlags(void)
{
	I2CONCLR.AAC = 0;
	I2CONCLR.SIC = 0;
	I2CONCLR.STAC = 0;
	I2CONCLR.I2ENC = 0;
}


/*****************************************************************************
** Function name:		I2CEngine
**
** Descriptions:		The routine to complete a I2C transaction
**						from start to stop. All the intermitten
**						steps are handled in the interrupt handler.
**						Before this routine is called, the read
**						length, write length, I2C master buffer,
**						and I2C command fields need to be filled.
**						see i2cmst.c for more details.
**
** parameters:			I2C port number
** Returned value:		master state of current I2C port.
**
*****************************************************************************/
uint8_t I2CEngine()
{
  /*--- Issue a start condition ---*/
  I2CONSET.STA = 1;	/* Set Start flag */
  I2CONCLR.SIC = 1;

  I2CMasterState = I2C_BUSY;

  while ( I2CMasterState == I2C_BUSY )
  {
	if ( timeout >= MAX_TIMEOUT )
	{
	  I2CMasterState = I2C_TIME_OUT;
	  break;
	}
	timeout++;
  }
  I2CONCLR.STAC = 1;

  return ( I2CMasterState );
}







