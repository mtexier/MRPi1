/**
  ******************************************************************************
  * @file    Leds.c
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/

 #include "Leds.h"
 
 
GPIO_TypeDef* LEDS_PORT[LEDn] = {LED1_PORT, LED2_PORT, LED3_PORT,LED4_PORT,LED5_PORT};
 
const uint16_t LEDS_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN};
 
/**********************************************************
 * @brief  Leds_init : led initialisation
 * @param  None
 * @retval None
**********************************************************/
void Leds_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
 
  /* Configuration  gpio of the leds */
  GPIO_InitStruct.Pin = LED2_PIN | LED3_PIN | LED4_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  /* Configuration  gpio of the led 1 ON/OFF */
  GPIO_InitStruct.Pin = LED1_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(LED1_PORT, &GPIO_InitStruct);

  /* Configuration  gpio of the led low battery */
  GPIO_InitStruct.Pin = LED5_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(LED5_PORT, &GPIO_InitStruct);


}
 
 
/**********************************************************
 * @brief  Leds_on : leds on
 * @param  None
 * @retval None
**********************************************************/
void Leds_on(Led_TypeDef Led)
{
  LEDS_PORT[Led]->BSRRL = LEDS_PIN[Led];
}


/**********************************************************
 * @brief  Leds_off : leds off
 * @param  None
 * @retval None
**********************************************************/
void Leds_off(Led_TypeDef Led)
{
  LEDS_PORT[Led]->BSRRH = LEDS_PIN[Led];
}


/**********************************************************
 * @brief  Leds_Write
 * @param  None
 * @retval None
**********************************************************/
void Leds_Write(Led_TypeDef Led,LedState State)
{
  if(State == LED_OFF)
  {
	  LEDS_PORT[Led]->BSRRH = LEDS_PIN[Led];// led off
  }
  else
  {
	  LEDS_PORT[Led]->BSRRL = LEDS_PIN[Led];// led on
  }
}


/**********************************************************
 * @brief  Leds_toggle
 * @param  None
 * @retval None
**********************************************************/
void Leds_toggle(Led_TypeDef Led)
{
  LEDS_PORT[Led]->ODR ^= LEDS_PIN[Led];
}
 
 
 // End Of file
