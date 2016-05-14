/**
  ******************************************************************************
  * @file    MoveRobot.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief	MoveRobot
  *
 *******************************************************************************/
 
#ifndef _MoveRobot_H
#define _MoveRobot_H

#include "Board.h"
#include "Motors.h"

/************************************************************************
 * Defines
***********************************************************************/

void MoveRobot_init(void);
void MoveRobot_forward(uint32_t Speed);
void MoveRobot_back(uint32_t Speed);
void MoveRobot_turn_right(uint32_t Speed);
void MoveRobot_turn_left(uint32_t Speed);
void MoveRobot_stop(void);


 #endif
// End Of File
