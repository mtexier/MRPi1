/**
  ******************************************************************************
  * @file    ProximitySensors.h
  * @author  MRS
  * @version V1.0
  * @date    5/11/2015
  * @brief	Proximity Infrared sensor
  *
 *******************************************************************************/
 
#ifndef _PROXIMITY_SENSOR_H
#define _PROXIMITY_SENSOR_H

#include "Board.h"

#define _PROX_IR_DISABLE(IR) IRPEN_PORT[IR]->BSRRH = IRPEN_PIN[IR]
#define _PROX_IR_ENABLE(IR)  IRPEN_PORT[IR]->BSRRL= IRPEN_PIN[IR]

#define NUMBER_IR_PROX 6

#define IR_PROX1_CHANNEL 3 // Adc PC0
#define IR_PROX2_CHANNEL 4 // Adc PC1
#define IR_PROX3_CHANNEL 5 // Adc PC2
#define IR_PROX4_CHANNEL 6 // Adc PC3
#define IR_PROX5_CHANNEL 7 // Adc PB1
#define IR_PROX6_CHANNEL 8 // Adc PB0


typedef enum
{
  IR_PROX1_S1 = 0, // State n°1
  IR_PROX1_S2 = 1, // State n°2
}IR_PROX_State;

typedef enum
{
  IR_PROX1,
  IR_PROX2,
  IR_PROX3,
  IR_PROX4,
  IR_PROX5,
  IR_PROX6,
  NB_IR_PROX
}IR_PROX_TypeDef;

typedef struct
{
IR_PROX_State State;
uint16_t Ambiant_Light[NUMBER_IR_PROX];
uint16_t AmbiantReflective_Light[NUMBER_IR_PROX];
uint16_t Reflective_Light[NUMBER_IR_PROX];
uint16_t Reflective_Light_read[NUMBER_IR_PROX];
}struct_IR_Prox;



void ProxSensors_init(void);   // initialisation, to be call before read proximity sensor.
uint16_t ProxSensors_read_ir(IR_PROX_TypeDef IR_Prox);
uint16_t ProxSensors_read_ambiantLight(IR_PROX_TypeDef IR_Prox);

void TIM2_IRQHandler(void);

 
#endif
// End Of File
