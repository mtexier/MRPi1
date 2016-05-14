/**
  ******************************************************************************
  * @file    control.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    29/12/2015
  * @brief	control
  *
 *******************************************************************************/
 
#ifndef _CONTROL_H
#define _CONTROL_H

#include "Board.h"

typedef enum{
CONTROL_ENABLE = 0,
CONTROL_DISABLE
}enum_Control;


//#define GAIN_P_DISTANCE (float)(90)
//#define GAIN_P_ORIENTATION (float)(40)
//#define GAIN_COM (float)(100)

#define GAIN_P_DISTANCE (float)(110)
#define GAIN_P_ORIENTATION (float)(250)
#define GAIN_COM (float)(100)



void controlManage(int32_t distanceCommand, int32_t orientationCommand );

void controlWrite(int32_t distanceCommand );

void controlEnable(bool state);
bool controlState(void);




 #endif
// End Of File
