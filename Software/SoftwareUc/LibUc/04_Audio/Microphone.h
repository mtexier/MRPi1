/**
  ******************************************************************************
  * @file    Microphone.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	
  *
 *******************************************************************************/
 
#ifndef _MICROPHONE_H
#define _MICROPHONE_H

#include "Board.h"




void Microphone_init(void);   // initialisation, to be call before read sensor.
int16_t Microphone_get(void); // to get analog value 
 
 #endif
// End Of File
