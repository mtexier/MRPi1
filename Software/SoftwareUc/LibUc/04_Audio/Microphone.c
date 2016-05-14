/**
  ******************************************************************************
  * @file    Microphone.c
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
 #include "stm32f4xx.h"
 #include "Microphone.h"
 
 
  /**
  * @brief  Microphone init
  * @param  None
  * @retval None
  */
void Microphone_init(void)
{
GPIO_InitTypeDef  GPIO_InitStruct;
 
   // Configure Temperature pin as analog input
  GPIO_InitStruct.Pin = MICRO_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // Analog mode
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MICRO_PORT, &GPIO_InitStruct);
}
 
   /**
  * @brief  Microphone get analog value
  * @param  None
  * @retval None
  */
int16_t Microphone_get(void)
{
 return 0;
}

 
 // End Of file
