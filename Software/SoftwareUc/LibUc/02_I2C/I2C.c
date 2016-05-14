/**
  ******************************************************************************
  * @file    I2C.c
  * @author  Mace Robotics
  * @version V1.1
  * @date    27/04/2016
  * @brief
  *
 *******************************************************************************/

#include "I2C.h"
#include "leds.h"



/************************************************************************
 * Private functions definitions
***********************************************************************/
static void MR_I2C_initGpio(enum_GpioI2C GpioI2C);


I2C_HandleTypeDef Handle_I2C;

/**********************************************************
 * @brief  Initializes I2C peripheral
 * @param  None
 * @retval None
**********************************************************/
void MR_I2C_init(I2C_TypeDef* I2Cx, enum_GpioI2C GpioI2C, uint32_t clockSpeed)
{
HAL_StatusTypeDef Status;

  Handle_I2C.Instance = I2Cx;
  Handle_I2C.Init.ClockSpeed  = clockSpeed;
  Handle_I2C.Init.DutyCycle   = I2C_DUTYCYCLE_2;
  Handle_I2C.Init.OwnAddress1 = 0x2d;
  Handle_I2C.Init.OwnAddress2 = 0xFE;
  Handle_I2C.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  Handle_I2C.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  Handle_I2C.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  Handle_I2C.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

  if (I2Cx == I2C1)
  {
	// Clock enable
	  __I2C1_CLK_ENABLE();
  }

  if (I2Cx == I2C2)
  {
	// Clock enable
	  __I2C2_CLK_ENABLE();
  }

  if (I2Cx == I2C3)
  {
	// Clock enable
	  __I2C3_CLK_ENABLE();
  }

  MR_I2C_initGpio(GpioI2C);

  Status = HAL_I2C_Init(&Handle_I2C);




}


/**********************************************************
 * @brief  Write I2C peripheral
 * @param  target_address
 * @param  register_address
 * @param  data
**********************************************************/
uint8_t MR_I2C_Write( uint16_t target_address, uint8_t reg, uint8_t data)
{
uint8_t data_array[2] = {reg, data};





  HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)data_array, sizeof(data_array), (uint32_t)1000);


}




/**********************************************************
 * @brief  Read I2C peripheral
 * @param  target_address
 * @param  register_address
 * @param  pointer where data will be stored
**********************************************************/
void MR_I2C_Read( uint16_t target_address, uint8_t register_address, uint8_t *data_read)
{
uint8_t data[5];
uint8_t dataReg[2] = {register_address, 0};



  HAL_I2C_Master_Transmit(&Handle_I2C, ((target_address<<1)), &register_address, 1, 1000);


  HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), data, 1, 1000);




   //__disable_irq();
/*   if((HAL_I2C_Master_Transmit(&Handle_I2C,((target_address<<1)), (uint8_t*)dataReg, sizeof(dataReg), (uint32_t)1000) != HAL_OK)
   || (HAL_I2C_Master_Receive(&Handle_I2C,((target_address)), &data, 5, 1000) != HAL_OK))
   {
   }*/
   //MR_I2C_Write(ACC_ADDRESS,0x0D,0x00);
   //HAL_I2C_Master_Receive(&Handle_I2C,((target_address)), &data, 1, 1000) ;
   //__enable_irq();


   debugSend_int(data[0],data[1],data[2] );


   /*  Usart_Send_uint(UART4, data[0]);//TEST
     Usart_Send_uint(UART4, data[1]);//TEST
     Usart_Send_uint(UART4, data[2]);//TEST
     Usart_Send_uint(UART4, data[3]);//TEST*/

     return data[0];




	/*
uint8_t data[1];


	MR_I2C_Write(ACC_ADDRESS, 0x0D, 1);

	HAL_I2C_Master_Receive(&Handle_I2C, ((target_address<<1)), &data, 1, 1000);

	Usart_Send_String(UART4, "data=");//TEST
	Usart_Send_uint(UART4, data[0]);//TEST
*/




}




/**********************************************************
 * @brief  Initializes I2C peripheral
 * @param  None
 * @retval None
**********************************************************/
static void MR_I2C_initGpio(enum_GpioI2C GpioI2C)
{
GPIO_InitTypeDef  GPIO_InitStruct_Pin1;
GPIO_InitTypeDef  GPIO_InitStruct_Pin2;
GPIO_TypeDef *GPIO_Type_Pin1, *GPIO_Type_Pin2;


  // init pin
  switch(GpioI2C)
  {
    case I2C1_PB6_PB7 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_6;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_7;


      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C1_PB8_PB9 :
        // CLK enable
        __GPIOB_CLK_ENABLE();

        GPIO_InitStruct_Pin1.Pin = GPIO_PIN_8;
        GPIO_InitStruct_Pin2.Pin = GPIO_PIN_9;

        GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
        GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

        GPIO_Type_Pin1 = GPIOB;
        GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C1_PB6_PB9 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_6;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_9;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C1;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C1;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C2_PB10_PB11 :
      // CLK enable
      __GPIOB_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_10;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_11;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C2;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C2;

      GPIO_Type_Pin1 = GPIOB;
      GPIO_Type_Pin2 = GPIOB;

    break;

    case I2C2_PF0_PF1 :
      // CLK enable
      __GPIOF_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_0;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_1;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C2;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C2;

      GPIO_Type_Pin1 = GPIOF;
      GPIO_Type_Pin2 = GPIOF;
    break;

    case I2C3_PC9_PA8 :
      // CLK enable
      __GPIOC_CLK_ENABLE();

      GPIO_InitStruct_Pin1.Pin = GPIO_PIN_9;
      GPIO_InitStruct_Pin2.Pin = GPIO_PIN_8;

      GPIO_InitStruct_Pin1.Alternate = GPIO_AF4_I2C3;
      GPIO_InitStruct_Pin2.Alternate = GPIO_AF4_I2C3;

      GPIO_Type_Pin1 = GPIOC;
      GPIO_Type_Pin2 = GPIOA;

    break;

    default:
    break;

  }




  // init mode
  GPIO_InitStruct_Pin1.Mode = GPIO_MODE_AF_OD; // Open Drain Mode
  GPIO_InitStruct_Pin2.Mode = GPIO_MODE_AF_OD;// Open drain-mode

  // init pull up
  //GPIO_InitStruct_Pin1.Pull = GPIO_PULLUP;
  //GPIO_InitStruct_Pin2.Pull = GPIO_PULLUP;

  // init speed
  GPIO_InitStruct_Pin1.Speed = GPIO_SPEED_LOW;
  GPIO_InitStruct_Pin2.Speed = GPIO_SPEED_LOW;

  // Init hal gpio
  HAL_GPIO_Init(GPIO_Type_Pin1, &GPIO_InitStruct_Pin1);
  HAL_GPIO_Init(GPIO_Type_Pin2, &GPIO_InitStruct_Pin2);

}
 

 
 // End Of file
