/**
  ******************************************************************************
  * @file    SPI.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief   SPI
  *
 *******************************************************************************/
 
#ifndef _SPI_H
#define _SPI_H

#include "Board.h"

#define SPI_WAIT_TX(SPIx)                   while ((SPIx->SR & SPI_FLAG_TXE) == 0 || (SPIx->SR & SPI_FLAG_BSY))
#define SPI_WAIT_RX(SPIx)                   while ((SPIx->SR & SPI_FLAG_RXNE) == 0 || (SPIx->SR & SPI_FLAG_BSY))

/************************************************************************
 * Defines
***********************************************************************/

void spi_init(SPI_TypeDef* SPIx);
void SPI1_IRQHandler(void);
void spi_write(char cara);
void spi_writeUint(uint32_t Number);
void spi_read(void);

#endif
// End Of File
