/**
  ******************************************************************************
  * @file    FirmwareVersion.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    12/06/2016
  * @brief  
  *
  * 
 *******************************************************************************/

#include "FirmwareVersion.h"

const float firmware_version = 0.8;

/**********************************************************
 * @brief  FirmwareVersion_init
 * @param  None
 * @retval None
**********************************************************/
float FirmwareVersion_read(void)
{
  return firmware_version;
}

 // End Of file
