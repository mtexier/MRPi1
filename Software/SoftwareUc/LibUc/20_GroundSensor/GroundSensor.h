/**
  ******************************************************************************
  * @file    GroundSensor.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief	GroundSensor
  *
 *******************************************************************************/
 
#ifndef _GroundSensor_H
#define _GroundSensor_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define GROUND_SENSOR_LEFT 1 // Adc PA6
#define GROUND_SENSOR_MIDDLE 9 // Adc PA4
#define GROUND_SENSOR_RIGHT 10 // Adc PA1

typedef enum{
GR_RIGHT = 0,
GR_LEFT,
GR_MIDDLE,
}enum_GroundSensors;


void GroundSensor_init(void);

uint16_t GroundSensor_read(enum_GroundSensors groundSensor);

 
 #endif
// End Of File
