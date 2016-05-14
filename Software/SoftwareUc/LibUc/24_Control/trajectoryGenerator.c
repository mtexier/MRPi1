/**
  ******************************************************************************
  * @file    trajectoryGenerator.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    30/12/2015
  * @brief   trajectory generator
  *
  *
 *******************************************************************************/
#include <stdbool.h>
#include <stdio.h>

#include "trajectoryGenerator.h"

struct_trajectoryGenerator trajectoryGenerator;


/**********************************************************
 * @brief  trajectoryGenerator_type
 * @param  trajectory Type
 * @retval None
**********************************************************/
void trajectoryGenerator_type(enum_trajectoryType type)
{
	trajectoryGenerator.type = type;
}


/**********************************************************
 * @brief  trajectoryGenerator_readType
 * @param  None
 * @retval None
**********************************************************/
enum_trajectoryType trajectoryGenerator_readType(void)
{
  return(trajectoryGenerator.type);
}

 // End Of file

