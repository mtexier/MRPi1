/**
  ******************************************************************************
  * @file    Encoder.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief	Encoder
  *
 *******************************************************************************/
 
#ifndef _ENCODER_H
#define _ENCODER_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/

/**
  * @brief Encoder
  */
void encoder_init(void);
int32_t encodeurRight(void);
int32_t encodeurLeft(void);

void encodeur_reset(void);
 
 #endif
// End Of File
