/**
  ******************************************************************************
  * @file    Speaker.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Temperature sensor
  *
 *******************************************************************************/
 
#ifndef _SPEAKER_H
#define _SPEAKER_H

#include "Board.h"

// Musical notes
#define NOTE_DO 131
#define NOTE_RE 139
#define NOTE_MI 165
#define NOTE_FA 175
#define NOTE_SOL 196
#define NOTE_LA 220
#define NOTE_SI 247









void Speaker_init(void);   // initialisation, to be call before read sensor.
void Speaker_enable(void);
void Speaker_disable(void);

 #endif
// End Of File
