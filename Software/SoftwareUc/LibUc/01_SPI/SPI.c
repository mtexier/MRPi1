/**
  ******************************************************************************
  * @file    SPI.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    22/01/2016
  * @brief
  *
 *******************************************************************************/
#include <stdio.h>
#include "SPI.h"

SPI_HandleTypeDef hspi;



/************************************************************************
 * Private functions definitions
***********************************************************************/
static void spi_initGpio(SPI_TypeDef* SPIx);

uint8_t RxBuffer[1];
uint8_t TxBuffer[1];
/**********************************************************
 * @brief  Initializes SPI peripheral
 * @param  SPI
 * @retval None
**********************************************************/
void spi_init(SPI_TypeDef* SPIx)
{

  __SPI1_CLK_ENABLE();

  spi_initGpio(SPI1);

  hspi.Instance = SPIx;
  hspi.Init.Mode = SPI_MODE_SLAVE;
  hspi.Init.Direction = SPI_DIRECTION_2LINES;

  hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi.Init.NSS = SPI_NSS_SOFT;
  hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  hspi.Init.CRCPolynomial = 7;
  
  // init spi
  HAL_SPI_Init(&hspi);

  // Enable irq reception
  __HAL_SPI_ENABLE_IT(&hspi, SPI_IT_RXNE);




  HAL_SPI_Receive_IT(&hspi, RxBuffer, 1);


  HAL_NVIC_SetPriority(SPI1_IRQn, 0, 1);

  HAL_NVIC_EnableIRQ(SPI1_IRQn);


}


void spi_read(void)
{
//	Usart_Send_String(UART4, RxBuffer);// s
}


/**********************************************************
 * @brief  spi_write
 * @param  None
 * @retval None
**********************************************************/
void spi_write(char cara)
{
/*uint8_t data[1];
  // send data
TxBuffer[0] = 22;
HAL_SPI_Transmit_IT(&hspi, TxBuffer, 1);
*/

 // SPI_WAIT_RX(SPI1);

  //SPI1->DR = cara;

  /* Wait for SPI to end everything */
  //SPI_WAIT_TX(SPI1);





}

/**********************************************************
 * @brief  spi_write
 * @param  None
 * @retval None
**********************************************************/
void spi_writeUint(uint32_t Number)
{
char string_number[12]={'c','c','c','c','c','c','c','c','c','c','c','c'};
uint32_t size = 0, Count = 0;
char cara='.';

  // convert number to string
  sprintf(string_number, "%lu", Number);

  while((cara != 'c')&&(size < 12))
  {
    cara = string_number[size];
	size++;
  }

  for(Count=0; Count < (size-2); Count++)// Size - (caracter end string)
  {
	  spi_write(string_number[Count]);
  }

}


/**********************************************************
 * @brief  SPI1_IRQHandler
 * @param  None
 * @retval None
**********************************************************/
void SPI1_IRQHandler(void)
{
//char data;

HAL_SPI_IRQHandler(&hspi);


  // read data
  //data = (char)(SPI1->DR);

  //Usart_Send_Character(UART4, RxBuffer[0]);

  /*

  if(HAL_GPIO_ReadPin(SPI_CS1_PORT, SPI_CS1_PIN) == GPIO_PIN_RESET)// chip select
  {
    ComRPI_manage(data);
  }
*/
}


/**********************************************************
 * @brief  Initializes SPI peripheral
 * @param  SPI
 * @retval None
**********************************************************/
static void spi_initGpio(SPI_TypeDef* SPIx)
{
GPIO_InitTypeDef  gpioInit;

  if (SPIx == SPI1)
  {
    /* Configuration  gpio of the spi */
	gpioInit.Pin = SPI_MOSI_PIN | SPI_MISO_PIN | SPI_SCK_PIN; // Pin
	gpioInit.Mode = GPIO_MODE_AF_PP; // GPIO mode
	gpioInit.Alternate = GPIO_AF5_SPI1;
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &gpioInit);

	// Chips select
	gpioInit.Pin = SPI_CS1_PIN; // Pin
	gpioInit.Mode = GPIO_MODE_INPUT; // GPIO mode input
	gpioInit.Pull = GPIO_NOPULL;
	gpioInit.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(SPI_CS1_PORT, &gpioInit);
  }

}





 
 // End Of file
