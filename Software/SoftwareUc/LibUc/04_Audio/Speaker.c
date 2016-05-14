/**
  ******************************************************************************
  * @file    Speaker.c
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
 #include "stm32f4xx.h"
 #include "Speaker.h"
 
 
/**********************************************************
 * @brief  Speaker_init
 * @param  None
 * @retval None
**********************************************************/
void Speaker_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
 
  // Pin enable sound configuration
  GPIO_InitStruct.Pin = SPEAKER_ENABLE_PIN ; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(SPEAKER_ENABLE_PORT, &GPIO_InitStruct);
  
  Speaker_disable();
 
}


/**********************************************************
 * @brief  Speaker_enable
 * @param  None
 * @retval None
**********************************************************/
void Speaker_enable(void)
{
	// Pin Low
	SPEAKER_ENABLE_PORT->BSRRH = SPEAKER_ENABLE_PIN;
}


/**********************************************************
 * @brief  Speaker_disable
 * @param  None
 * @retval None
**********************************************************/
void Speaker_disable(void)
{
	// Pin hight
	SPEAKER_ENABLE_PORT->BSRRL = SPEAKER_ENABLE_PIN;
}

 
 // End Of file
