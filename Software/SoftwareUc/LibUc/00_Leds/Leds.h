/**
  ******************************************************************************
  * @file    Leds.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Leds
  *
 *******************************************************************************/
 
#ifndef _LEDS_H
#define _LEDS_H

#include "Board.h"

/************************************************************************
 * Defines
***********************************************************************/
#define LEDn 5 // Number of leds

typedef enum
{
  LED_ON_OFF = 0,
  LED1 = 1,
  LED2 = 2,
  LED3 = 3,
  LED_LOW_BATT = 4,
}Led_TypeDef;

typedef enum
{
  LED_OFF = 0,
  LED_ON = 1
}LedState;

/**
  * @brief LEDS
  */
void Leds_init(void);

void Leds_on(Led_TypeDef Led);

void Leds_Write(Led_TypeDef Led,LedState State);

void Leds_off(Led_TypeDef Led);

void Leds_toggle(Led_TypeDef Led);
 
#endif
// End Of File
