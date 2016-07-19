/**
  ******************************************************************************
  * @file    IRremote.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    16/11/2015
  * @brief
  *
 *******************************************************************************/
#include <string.h>

#include "IRremote.h"
#include "Leds.h"
#include "Motors.h"


/************************************************************************
 * Variable definitions
***********************************************************************/
TIM_HandleTypeDef TIMER12_InitStruct;
enum_StateIRremote StateIRremote;



static void IRremote_Timer(void);

static int8_t IRremote_data = -1;


/**********************************************************
 * @brief  Initializes IR remote
 * @param  None
 * @retval None
**********************************************************/
void IRremote_init(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  /* Configuration  gpio  */
  GPIO_InitStruct.Pin = IR38K_PIN; // Pin
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // GPIO mode input rising and falling edge interrupt.
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(IR38K_PORT, &GPIO_InitStruct);

  StateIRremote = WAIT_START_BIT;

  IRremote_Timer();

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);

  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);


}


/**********************************************************
 * @brief  External IRQ handler
 * @param  None
 * @retval None
**********************************************************/
void EXTI9_5_IRQHandler(void)
{
  // Rising or falling edge detection
  if(__HAL_GPIO_EXTI_GET_IT(IR38K_PIN) != RESET)
  {

	// clear interrupt
    __HAL_GPIO_EXTI_CLEAR_IT(IR38K_PIN);


    // Finite state machine
    switch(StateIRremote)
    {
      // wait the start bit (rising edge)
      case WAIT_START_BIT:
   
    	// if rising edge
        if (HAL_GPIO_ReadPin(IR38K_PORT, IR38K_PIN) == GPIO_PIN_RESET)
		{

		  HAL_TIM_Base_Start(&TIMER12_InitStruct);// Start timer
          StateIRremote = MESURE_BIT; // next state
		}
        else
        {
          StateIRremote = WAIT_START_BIT;
        }
        
      break;

      // duration mesurement
      case MESURE_BIT:
        // Stop the timer.
        HAL_TIM_Base_Stop(&TIMER12_InitStruct);
        // next state
        StateIRremote = START_SAMPLING2;
      break;

      case START_SAMPLING2:
    	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    	TIMER12_InitStruct.Instance->CNT = 0;
    	TIMER12_InitStruct.Instance->ARR = 51000;
    	HAL_TIM_Base_Start_IT(&TIMER12_InitStruct);
      break;
    }

  }// Fin if

}

/**********************************************************
 * @brief  timer irq handler
 * @param  None
 * @retval None
**********************************************************/
void TIM8_BRK_TIM12_IRQHandler(void)
{
uint8_t Test_Command = 0;
uint8_t Buffer_TV_Commande[6]={0,0,0,0,0,0};
static uint8_t  CompteurBufferTv = 0;
static uint8_t Buffer_TV[12]={0,0,0,0,0,0,0,0,0,0,0,0};

  if (__HAL_TIM_GET_FLAG(&TIMER12_InitStruct, TIM_FLAG_UPDATE) != RESET)
  {
    if (__HAL_TIM_GET_ITSTATUS(&TIMER12_InitStruct, TIM_IT_UPDATE) != RESET)
	{
	  __HAL_TIM_CLEAR_FLAG(&TIMER12_InitStruct, TIM_FLAG_UPDATE);

      if(StateIRremote == START_SAMPLING2)
      {
        if(CompteurBufferTv < 12)
        {
        	//not
        	Buffer_TV[CompteurBufferTv++]  = !(  HAL_GPIO_ReadPin(IR38K_PORT, IR38K_PIN) );
        }
        else
        {

    	  Buffer_TV_Commande[0] =  Buffer_TV[6]*32;
    	  Buffer_TV_Commande[1] =  Buffer_TV[7]*16;
    	  Buffer_TV_Commande[2] =  Buffer_TV[8]*8;
    	  Buffer_TV_Commande[3] =  Buffer_TV[9]*4;
    	  Buffer_TV_Commande[4] =  Buffer_TV[10]*2;
    	  Buffer_TV_Commande[5] =  Buffer_TV[11];

    	  Test_Command = Buffer_TV_Commande[0]
    	                 +Buffer_TV_Commande[1]
    	                 +Buffer_TV_Commande[2]
    	                 +Buffer_TV_Commande[3]
    	                 +Buffer_TV_Commande[4]
    	                 +Buffer_TV_Commande[5];

    	  // reset Buffer_TV and Buffer_TV_Commande
    	  memset(Buffer_TV, 0, sizeof(Buffer_TV));
    	  memset(Buffer_TV_Commande, 0, sizeof(Buffer_TV_Commande));

          switch(Test_Command)
          {
            case 0:
              //Usart_Send_String(UART4, "$IR0\n");
              IRremote_data = 0;
            break;

            case 1:
              //Usart_Send_String(UART4, "$IR1\n");
              IRremote_data = 1;
            break;

            case 2:
              //Usart_Send_String(UART4, "$IR2\n");
              IRremote_data = 2;
            break;

            case 3:
              //Usart_Send_String(UART4, "$IR3\n");
              IRremote_data = 3;
            break;

            case 4:
              //Usart_Send_String(UART4, "$IR4\n");
              IRremote_data = 4;
            break;

            case 5:
             //Usart_Send_String(UART4, "$IR5\n");
             IRremote_data = 5;
            break;

            case 6:
              //Usart_Send_String(UART4, "$IR6\n");
              IRremote_data = 6;
            break;

            case 7:
             //Usart_Send_String(UART4, "$IR7\n");
             IRremote_data = 7;
            break;

            case 8:
             //Usart_Send_String(UART4, "$IR8\n");
             IRremote_data = 8;
            break;

            case 9:
              //Usart_Send_String(UART4, "$IR9\n");
              IRremote_data = 9;
            break;
          }


    	  CompteurBufferTv = 0;
    	  StateIRremote = WAIT_START_BIT;
    	  HAL_TIM_Base_Stop(&TIMER12_InitStruct);// Stop timer
    	  TIMER12_InitStruct.Instance->CNT = 0;
    	  TIMER12_InitStruct.Instance->ARR = 65535;
    	  __HAL_GPIO_EXTI_CLEAR_IT(IR38K_PIN);
    	  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
      }
	}

	}
  }
}

/**********************************************************
 * @brief  IRremote_read
 * @param  None
 * @retval None
**********************************************************/
int8_t IRremote_read(void)
{
  return (IRremote_data);
}



/**********************************************************
 * @brief  init timer
 * @param  None
 * @retval None
**********************************************************/
static void IRremote_Timer(void)
{
  // TIM12 Clock Enable
  __TIM12_CLK_ENABLE();

  // Timer 12 init structure (2.3ms)
  TIMER12_InitStruct.Instance = TIM12;
  TIMER12_InitStruct.Init.Prescaler = 2; // Timer_Frequency = 168Mhz/2 = 84Mhz / 3 = 28MHz
  TIMER12_InitStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER12_InitStruct.Init.Period = 65535;
  TIMER12_InitStruct.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;


  // Init timer
  HAL_TIM_Base_Init(&TIMER12_InitStruct);

  // Init timer priority
  HAL_NVIC_SetPriority(TIM8_BRK_TIM12_IRQn, 0, 1);

  // Enable interrupt.
  HAL_NVIC_EnableIRQ(TIM8_BRK_TIM12_IRQn);

}

 
 // End Of file
