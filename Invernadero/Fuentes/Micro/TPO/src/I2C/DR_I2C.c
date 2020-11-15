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
volatile uint32_t I2CMasterState[I2C_PORT_NUM] = {I2C_IDLE,I2C_IDLE,I2C_IDLE};
volatile uint32_t timeout[I2C_PORT_NUM] = {0, 0, 0};

volatile uint8_t I2CMasterBuffer[I2C_PORT_NUM][BUFSIZE];
volatile uint8_t I2CSlaveBuffer[I2C_PORT_NUM][BUFSIZE];
volatile uint8_t I2CStatusBuffer[I2C_PORT_NUM][BUFSIZE];

volatile uint32_t I2CCount[I2C_PORT_NUM] = {0, 0, 0};
volatile uint32_t I2CReadLength[I2C_PORT_NUM];
volatile uint32_t I2CWriteLength[I2C_PORT_NUM];

volatile uint32_t RdIndex0 = 0, RdIndex1 = 0, RdIndex2 = 0;
volatile uint32_t WrIndex0 = 0, WrIndex1 = 0, WrIndex2 = 0;

volatile I2C_t* I2C[3] = { I2C0, I2C1, I2C2 };

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
	SetPINSEL(SDA1,3); //SDA
	SetPINSEL(SCL1,3);  //SCL

	SetPINMODE(SDA1,2);
	SetPINMODE(SCL1,2); //Seteo el Open-drain mode

	SetPINMODE_OD(SDA1,1);
	SetPINMODE_OD(SCL1,1); //Seteo el Open-drain mode

	//Limpio los flags
	I2C[1]->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;

	I2C[1]->SCLH = 60;
	I2C[1]->SCLL = 60;

	ISER0 |= (1 << 11); //Habilito interrupciones

	I2C[1]->CONSET = I2CONSET_I2EN; //Habilito el I2C
}

/*****************************************************************************
** Function name:		I2C_IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void I2C1_IRQHandler(void)
{
  uint8_t StatValue;
  int i = 0;
  timeout[1] = 0;
  /* this handler deals with master read and master write only */
  StatValue = I2C[1]->STAT;
  I2CStatusBuffer[1][i++] = StatValue;
  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
		WrIndex1 = 0;
		I2C[1]->DAT = I2CMasterBuffer[1][WrIndex1++];
		I2C[1]->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;

	case 0x10:			/* A repeated started is issued */
		RdIndex1 = 0;
		I2C[1]->DAT = I2CMasterBuffer[1][WrIndex1++]; 		/* Send SLA with R bit set*/
		I2C[1]->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;

	case 0x18:			/* SLA+W has been transmitted; ACK has been received. */
		if ( I2CWriteLength[1] == 1 )
		{
		  I2C[1]->CONSET = I2CONSET_STO;      /* Set Stop flag */
		  I2CMasterState[1] = I2C_NO_DATA;
		}
		else
		{
		  I2C[1]->DAT = I2CMasterBuffer[1][WrIndex1++];
		}
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x20:		/* SLA+W has been transmitted; NOT ACK has been received. */

	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
		if ( WrIndex1 < I2CWriteLength[1] )
		{
		  I2C[1]->DAT = I2CMasterBuffer[1][WrIndex1++]; /* this should be the last one */
		}
		else
		{
		  if ( I2CReadLength[1] != 0 )
		  {
			I2C[1]->CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
		  }
		  else
		  {
			I2C[1]->CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2CMasterState[1] = I2C_OK;
		  }
		}
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x30:
		I2C[1]->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2CMasterState[1] = I2C_NACK_ON_DATA;
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x40:	/* Master Receive, SLA_R has been sent */
		if ( (RdIndex1 + 1) < I2CReadLength[1] )
		{
		  /* Will go to State 0x50 */
		  I2C[1]->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
		}
		else
		{
		  /* Will go to State 0x58 */
		  I2C[1]->CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
		}
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
		I2CSlaveBuffer[1][RdIndex1++] = I2C[1]->DAT;
		if ( (RdIndex1 + 1) < I2CReadLength[1] )
		{
		  I2C[1]->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
		}
		else
		{
		  I2C[1]->CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
		}
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x58:
		I2CSlaveBuffer[1][RdIndex1++] = I2C[1]->DAT;
		I2CMasterState[1] = I2C_OK;
		I2C[1]->CONSET = I2CONSET_STO;	/* Set Stop flag */
		I2C[1]->CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
		break;

	case 0x48:
		I2C[1]->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2CMasterState[1] = I2C_NACK_ON_ADDRESS;
		I2C[1]->CONCLR = I2CONCLR_SIC;
		break;

	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
		I2CMasterState[1] = I2C_ARBITRATION_LOST;
		I2C[1]->CONCLR = I2CONCLR_SIC;
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
uint8_t I2CStop( uint32_t portNum )
{
  I2C[portNum]->CONSET = I2CONSET_STO;      /* Set Stop flag */
  I2C[portNum]->CONCLR = I2CONCLR_SIC;  /* Clear SI flag */

  /*--- Wait for STOP detected ---*/
  while( I2C[portNum]->CONSET & I2CONSET_STO );
  return TRUE;
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
uint8_t I2CEngine( uint32_t portNum )
{
  /*--- Issue a start condition ---*/
  I2C[portNum]->CONSET = I2CONSET_STA;	/* Set Start flag */

  I2CMasterState[portNum] = I2C_BUSY;

  while ( I2CMasterState[portNum] == I2C_BUSY )
  {
	if ( timeout[portNum] >= MAX_TIMEOUT )
	{
	  I2CMasterState[portNum] = I2C_TIME_OUT;
	  break;
	}
	timeout[portNum]++;
  }
  I2C[portNum]->CONCLR = I2CONCLR_STAC;

  I2CStop(portNum);

  return ( I2CMasterState[portNum] );
}


/*****************************************************************************
** Function name:		I2CStart
**
** Descriptions:		Create I2C start condition, a timeout
**				value is set if the I2C never gets started,
**				and timed out. It's a fatal error.
**
** parameters:			None
** Returned value:		true or false, return false if timed out
**
*****************************************************************************/
uint32_t I2CStart( uint32_t portNum )
{
  uint32_t retVal = FALSE;

  timeout[portNum] = 0;
  /*--- Issue a start condition ---*/
  I2C[portNum]->CONSET = I2CONSET_STA;	/* Set Start flag */

  /*--- Wait until START transmitted ---*/
  while( 1 )
  {
	if ( I2CMasterState[portNum] == I2C_STARTED )
	{
	  retVal = TRUE;
	  break;
	}
	if ( timeout[portNum] >= MAX_TIMEOUT )
	{
	  retVal = FALSE;
	  break;
	}
	timeout[portNum]++;
  }
  return( retVal );
}




