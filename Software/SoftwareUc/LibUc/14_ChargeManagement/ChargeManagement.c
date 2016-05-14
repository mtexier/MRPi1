/**
  ******************************************************************************
  * @file    ChargeManagement.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief  Charge Battery Management
  *
 *******************************************************************************/

#include "ChargeManagement.h"


/**********************************************************
 * @brief  ChargeManagement_init : charge management initialisation
 * @param  None
 * @retval None
**********************************************************/
void ChargeManagement_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  /* Configuration  gpio */
  GPIO_InitStruct.Pin =  USB_PRESENT_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT; // GPIO mode input
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

 /* Configuration  gpio */
 GPIO_InitStruct.Pin =  USB_CURRENT_PIN; // Pin
 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
 HAL_GPIO_Init(USB_CURRENT_PORT, &GPIO_InitStruct);

}


/**********************************************************
 * @brief  ChargeManagement_Put500mACharge
 * @param  None
 * @retval None
**********************************************************/
void ChargeManagement_Put500mACharge(void)
{
  USB_CURRENT_PORT->BSRRL = USB_CURRENT_PIN;
}


 // End Of file
