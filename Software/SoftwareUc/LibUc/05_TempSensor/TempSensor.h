/**
  ******************************************************************************
  * @file    TempSensor.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Temperature sensor
  *
 *******************************************************************************/
 
#ifndef _TEMP_SENSOR_H
#define _TEMP_SENSOR_H

#include "Board.h"

#define TEMPERATURE_CHANNEL 2 // Adc PA2

void TempSensor_init(void);   // initialisation, to be call before read sensor.
float TempSensor_get(void); // to get analog value of temperature sensor
 
 #endif
// End Of File
