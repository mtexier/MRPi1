/**
  ******************************************************************************
  * @file    GroundSensor.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    5/11/2015
  * @brief  Ground sensor
  *  Exemple : 
  * 
 *******************************************************************************/

#include "GroundSensor.h"


/**********************************************************
 * @brief  GroundSensor_init
 * @param  None
 * @retval None
**********************************************************/
void GroundSensor_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

	  // Congiguration GPIO
	  GPIO_InitStruct.Pin = GRDS1_PIN |  GRDS2_PIN  |  GRDS3_PIN ; // Pin
	  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; // GPIO mode output
	  HAL_GPIO_Init(GRDS1_PORT, &GPIO_InitStruct);
}

/**********************************************************
 * @brief  GroundSensor_read
 * @param  None
 * @retval None
**********************************************************/
uint16_t GroundSensor_read(enum_GroundSensors groundSensor)
{
uint16_t data;
uint8_t Channel = GROUND_SENSOR_RIGHT;

  switch(groundSensor)
  {
    case 1:
    	Channel = GROUND_SENSOR_RIGHT;
    break;

    case 2:
    	Channel = GROUND_SENSOR_LEFT;
    break;

    case 3:
    	Channel = GROUND_SENSOR_MIDDLE;
    break;

  }

  data = Adc_read(Channel);


  return(data);
}




 // End Of file
