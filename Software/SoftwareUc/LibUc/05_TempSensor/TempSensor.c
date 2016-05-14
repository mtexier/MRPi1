/**
  ******************************************************************************
  * @file    TempSensor.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
#include <math.h>
#include "stm32f4xx.h"
#include "TempSensor.h"
#include "stm32f4xx_hal_rcc.h"
#include "Adc.h"
 
 
/************************************************************************
 * Variable definitions
***********************************************************************/

 
 
/**********************************************************
 * @brief  TempSensor_init
 * @param  None
 * @retval None
**********************************************************/
void TempSensor_init(void)
{
GPIO_InitTypeDef  GPIO_InitStruct;

  // Configure Temperature pin as analog input
  GPIO_InitStruct.Pin = TEMP_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // Analog mode
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TEMP_PORT, &GPIO_InitStruct);

}
 

/**********************************************************
 * @brief  TempSensor_get
 * @param  None
 * @retval None
**********************************************************/
float TempSensor_get(void)
{
const float Resistance_25degree = 10000; // 10Kohm
const float B_Constant = 0.000291;
const float T0_Constant = 0.003354;
float Tension_temp = 0;
float Resistance_temp = 0;
float Valeur1=0, Valeur2=0;

  // Read adc value
  Tension_temp = Adc_read(TEMPERATURE_CHANNEL);

  // Convert to voltage
  Tension_temp = (Tension_temp*3.3)/(4095);

  // Resistance temperature calcul (RT = Tension * 10K)/(3.3 - Tension)
  Resistance_temp = (Tension_temp*10000)/(3.3 - Tension_temp );

  Valeur1 = log(Resistance_temp/Resistance_25degree);

  Valeur2 = B_Constant * Valeur1 + T0_Constant;

  Valeur2 = 1/Valeur2;

  // Convert Kelvin to degree
  Valeur2 = Valeur2 - 273.15;


 return (Valeur2);
}

 
 // End Of file
