/**
  ******************************************************************************
  * @file    LedOnOff.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief	Charge Battery Management
  *
 *******************************************************************************/
 
#ifndef _LedOnOff_H
#define _LedOnOff_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/


/**
  * @brief LedOnOff
  */
void LedOnOff_init(void);

void TIM5_IRQHandler(void);


 
#endif
// End Of File
