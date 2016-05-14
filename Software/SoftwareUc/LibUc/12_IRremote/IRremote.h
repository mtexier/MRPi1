/**
  ******************************************************************************
  * @file    IRremote.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief	 RC-5 protocol was developed by Philips
  *
 *******************************************************************************/
 
#ifndef _IRremote_H
#define _IRremote_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define SIZE_BUFFER_RC5 12 // Field bit + Control bit  + 5 Address bits + 6 Command bits
#define SIZE_COMMAND_RC5 6 // Field bit + Control bit  + 5 Address bits + 6 Command bits


/************************************************************************
 * enumeration
***********************************************************************/
typedef enum
{
WAIT_START_BIT,
MESURE_BIT,
START_SAMPLING2
}enum_StateIRremote;



typedef struct
{
uint8_t Buffer[SIZE_BUFFER_RC5];
uint8_t Command[SIZE_COMMAND_RC5];
uint8_t RC5_Cmd;
uint8_t  CounterSampling;
}struct_IRremote;


/**
  * @brief IRremote
  */
void IRremote_init(void);
void TIM8_BRK_TIM12_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

int8_t IRremote_read(void);


 
 #endif
// End Of File
