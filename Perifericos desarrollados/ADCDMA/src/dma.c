/****************************************************************************
 *   $Id:: dma.c 6089 2011-01-06 04:38:09Z nxp12832                         $
 *   Project: NXP LPC17xx ADC DMA example
 *
 *   Description:
 *     This file contains DMA code example which include DMA initialization, 
 *     DMA interrupt handler, and APIs for ADC DMA access.
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
#include "LPC17xx.h"
#include "type.h"                      
#include "adc.h"
#include "dma.h"

volatile uint32_t DMATCCount = 0;
volatile uint32_t DMAErrCount = 0;
volatile uint32_t ADCDMA0Done = 0;
volatile uint32_t ADCDMA1Done = 0;

/******************************************************************************
** Function name:		DMA_IRQHandler
**
** Descriptions:		DMA interrupt handler
**
** parameters:		None
** Returned value:	None
** 
******************************************************************************/
void DMA_IRQHandler(void) 
{
  uint32_t regVal;

  regVal = LPC_GPDMA->IntTCStat;
  if ( regVal )
  {
	DMATCCount++;
	LPC_GPDMA->IntTCClear = regVal;
	if ( regVal & 0x01 )
	{
	  ADCDMA0Done = 1;
	}
	else if ( regVal & 0x02 )
	{
	  ADCDMA1Done = 1;
	}
	LPC_ADC->CR &= ~(0x1<<16);		/* Disable the BURST mode bit */
  } 

  regVal = LPC_GPDMA->IntErrStat;
  if ( regVal )
  {
	DMAErrCount++;
	LPC_GPDMA->IntErrClr = regVal;
	LPC_ADC->CR &= ~(0x1<<16);		/* Disable the BURST mode bit */
  }
  return;
}

/******************************************************************************
** Function name:		DMA_Init
**
** Descriptions:		clock to GPDMA in PCONP, GPDMA init before channel init		
**
** parameters:			None			
** Returned value:		None		
** 
******************************************************************************/
void DMA_Init( void )
{
  /* Enable CLOCK into GPDMA controller */
  LPC_SC->PCONP |= (1 << 29);

  /* sync enabled */
  LPC_GPDMA->Sync = 0xFFFF;

  LPC_SC->DMAREQSEL = 0x0000;

  LPC_GPDMA->IntTCClear = 0x03;
  LPC_GPDMA->IntErrClr = 0x03;

  LPC_GPDMA->Config = 0x01;	/* Enable DMA channels, little endian */
  while ( !(LPC_GPDMA->Config & 0x01) );

  NVIC_EnableIRQ(DMA_IRQn);
  return;
}

/******************************************************************************
** Function name:		DMAChannel_Init
**
** Descriptions:		
**
** parameters:			Channel number, DMA mode: M2P, P2M, M2M, P2P			
** Returned value:		TRUE or FALSE
** 
******************************************************************************/
uint32_t DMAChannel_Init( uint32_t ChannelNum, uint32_t DMAMode )
{
  if ( ChannelNum == 0 )
  {
	ADCDMA0Done = 0;
	/* Clear DMA channel 0 terminal count. */
	LPC_GPDMA->IntTCClear = 0x01<<0;
	LPC_GPDMA->IntErrClr = 0x01<<0;
	LPC_GPDMACH0->CControl = 0;
	LPC_GPDMACH0->CConfig = 0;   
	if ( DMAMode == P2M )
	{
	  /* Ch0 set for P2M transfer from ADC to mempry. */
	  LPC_GPDMACH0->CSrcAddr = DMA_SRC;
	  LPC_GPDMACH0->CDestAddr = DMA_DST;
	  /* The burst size is set to 8, source and dest transfer width is
	  32 bits(word), src addr increment by 1. dst addr increment by 1. Terminal 
	  Count Int enable */
	  LPC_GPDMACH0->CControl = (DMA_SIZE & 0x0FFF)|(0x00<<12) 
		|(0x00<<15)|(0x02<<18)|(0x02<<21)|(1<<26)|(1<<27)|0x80000000;
	  return( TRUE );
	}
	else
	{
	  return ( FALSE );
	}
  }
  else if ( ChannelNum == 1 )
  {
	ADCDMA1Done = 0;
	/* Clear DMA channel 1 terminal count. */
	LPC_GPDMA->IntTCClear = 0x01<<1;
	LPC_GPDMA->IntErrClr = 0x01<<1;
	LPC_GPDMACH1->CControl = 0;
	LPC_GPDMACH1->CConfig = 0;      
	if ( DMAMode == P2M )
	{
	  /* Ch1 set for P2M transfer from ADC to mempry. */
	  LPC_GPDMACH1->CSrcAddr = DMA_SRC;
	  LPC_GPDMACH1->CDestAddr = DMA_DST;
	  /* The burst size is set to 8, source and dest transfer width is
	  32 bits(word), src addr increment by 1. dst addr unchange. Terminal 
	  Count Int enable */
	  LPC_GPDMACH1->CControl = (DMA_SIZE & 0x0FFF)|(0x00<<12) 
		|(0x00<<15)|(0x02<<18)|(0x02<<21)|(1<<26)|(1<<27)|0x80000000;
	  return( TRUE );
	}
	else
	{
	  return ( FALSE );
	}
  }
  else
  {
	return ( FALSE );
  }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
