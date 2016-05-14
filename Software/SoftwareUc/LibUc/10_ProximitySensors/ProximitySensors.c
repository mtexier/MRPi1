/**
  ******************************************************************************
  * @file    ProxSensors.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
#include <stdbool.h>
#include "stm32f4xx.h"
#include "ProximitySensors.h"

/************************************************************************
 * Private functions
***********************************************************************/
static void ProxSensors_init_timer(void);
static void ProxSensors_FSM(void); // finite-state machine


GPIO_TypeDef* IRPEN_PORT[NUMBER_IR_PROX] = {IR1EN_PORT, IR2EN_PORT, IR3EN_PORT, IR4EN_PORT, IR5EN_PORT, IR6EN_PORT};
const uint16_t IRPEN_PIN[NUMBER_IR_PROX] = {IR1EN_PIN, IR2EN_PIN, IR3EN_PIN, IR4EN_PIN, IR5EN_PIN, IR6EN_PIN};

 
/************************************************************************
 * Variable definitions
***********************************************************************/
TIM_HandleTypeDef TIMER2_InitStruct;
uint16_t Reflec_Irp[NUMBER_IR_PROX]; // Reflective light buffer
struct_IR_Prox IR_Proximity;


bool Irq_FSM = false;
 

/**********************************************************
 * @brief  ProxSensors_init
 * @param  None
 * @retval None
**********************************************************/
void ProxSensors_init(void)
{
GPIO_InitTypeDef  GPIO_ProxSenors;

  // Configure Prox sensor n°1,2,3 and 4  pin as analog input
  GPIO_ProxSenors.Pin = IR1_PIN | IR2_PIN | IR3_PIN | IR4_PIN;
  GPIO_ProxSenors.Mode = GPIO_MODE_ANALOG; // Analog mode
  GPIO_ProxSenors.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_ProxSenors);

  // Configure Prox sensor n°5,6  pin as analog input
  GPIO_ProxSenors.Pin = IR5_PIN | IR6_PIN;
  GPIO_ProxSenors.Mode = GPIO_MODE_ANALOG; // Analog mode
  GPIO_ProxSenors.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_ProxSenors);


  // Configuration  enable ir pins
  GPIO_ProxSenors.Pin = IR1EN_PIN | IR2EN_PIN | IR3EN_PIN; // Pin
  GPIO_ProxSenors.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(GPIOA, &GPIO_ProxSenors);

  // Configuration  enable ir pins
  GPIO_ProxSenors.Pin = IR4EN_PIN | IR5EN_PIN ; // Pin
  GPIO_ProxSenors.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(GPIOD, &GPIO_ProxSenors);
  
  // Configuration  enable ir pins
  GPIO_ProxSenors.Pin = IR6EN_PIN; // Pin
  GPIO_ProxSenors.Mode = GPIO_MODE_OUTPUT_PP; // GPIO mode output
  HAL_GPIO_Init(GPIOE, &GPIO_ProxSenors);

  // Disable emitter light
  _PROX_IR_DISABLE(IR_PROX1);
  _PROX_IR_DISABLE(IR_PROX2);
  _PROX_IR_DISABLE(IR_PROX3);
  _PROX_IR_DISABLE(IR_PROX4);
  _PROX_IR_DISABLE(IR_PROX5);
  _PROX_IR_DISABLE(IR_PROX6);
  
  // init FSM state
  IR_Proximity.State = IR_PROX1_S1;

  // Init timer for interruption.
  ProxSensors_init_timer();



}


/**********************************************************
 * @brief  ProxSensors_read_ir
 * @param  IR_Prox
 * @retval None
**********************************************************/
uint16_t ProxSensors_read_ir(IR_PROX_TypeDef IR_Prox)
{

  // Reflective light = (Ambient light) - (Ambient&Reflective light)
  if(IR_Proximity.Ambiant_Light[IR_Prox] > IR_Proximity.AmbiantReflective_Light[IR_Prox])
  {
    IR_Proximity.Reflective_Light[IR_Prox] =  IR_Proximity.Ambiant_Light[IR_Prox] - IR_Proximity.AmbiantReflective_Light[IR_Prox];
  }

  return IR_Proximity.Reflective_Light[IR_Prox];

}


/**********************************************************
 * @brief  ProxSensors_read_ambiantLight
 * @param  IR_Prox
 * @retval None
**********************************************************/
uint16_t ProxSensors_read_ambiantLight(IR_PROX_TypeDef IR_Prox)
{
	return IR_Proximity.Ambiant_Light[IR_Prox];
}


/**********************************************************
 * @brief  TIM2_IRQHandler
 * @param  None
 * @retval None
**********************************************************/
void TIM2_IRQHandler(void)
{
  if (__HAL_TIM_GET_FLAG(&TIMER2_InitStruct, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_ITSTATUS(&TIMER2_InitStruct, TIM_IT_UPDATE) != RESET)
	{
	  __HAL_TIM_CLEAR_FLAG(&TIMER2_InitStruct, TIM_FLAG_UPDATE);
	  
      // Finite State Machine : read ir proximity sensors.
      ProxSensors_FSM();

	}
  }

}


/**********************************************************
 * @brief  ProxSensors_init_timer
 * @param  None
 * @retval None
**********************************************************/
static void ProxSensors_init_timer(void)
{
  // TIM2 Clock Enable
  __TIM2_CLK_ENABLE();
  
  // Timer 2 init structure (Timer period = 175µs)
  TIMER2_InitStruct.Instance = TIM2;
  TIMER2_InitStruct.Init.Prescaler = 0; // Timer_Frequency = 84 Mhz.
  TIMER2_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  //TIMER2_InitStruct.Init.Period = 14699; //  (1/84e6)*14699 = 174µs
  TIMER2_InitStruct.Init.Period = 29398; //  (1/84e6)*14699 = 174µs
  TIMER2_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  
  // Init timer
  HAL_TIM_Base_Init(&TIMER2_InitStruct); 
  
  // Start timer interrupt
  HAL_TIM_Base_Start_IT(&TIMER2_InitStruct);

  // Init timer priority 
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 1);
  
  // Enable interrupt.
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}


/**********************************************************
 * @brief  ProxSensors_FSM
 * @param  None
 * @retval None
**********************************************************/
static void ProxSensors_FSM(void)
{
static uint8_t Id_IRprox = 0; //Counter IR_Prox
uint16_t data1, data2;



  switch(IR_Proximity.State)
  {
    // State 1
    case IR_PROX1_S1 :
	  // Read Ambiant light
      data1 = Adc_read(Id_IRprox+3);
      data2 = Adc_read(Id_IRprox+3);
      IR_Proximity.Ambiant_Light[Id_IRprox] = (data1 + data2)/2; // simple filter
      // Enable emitter led.
      _PROX_IR_ENABLE(Id_IRprox);
	  // Next state
      IR_Proximity.State = IR_PROX1_S2;
    break;

	// State 2
    case IR_PROX1_S2 :
	  // Read Ambiant and reflective light
      data1 = Adc_read(Id_IRprox+3);
      data2 = Adc_read(Id_IRprox+3);
      IR_Proximity.AmbiantReflective_Light[Id_IRprox] = (data1 + data2)/2;
	  // Disable emitter led.
     _PROX_IR_DISABLE(Id_IRprox);
	  // Next state
      IR_Proximity.State = IR_PROX1_S1;

      if(Id_IRprox < (NUMBER_IR_PROX-1))
        Id_IRprox++;
      else
        Id_IRprox = 0;


    break;

  }


}


 
 // End Of file
