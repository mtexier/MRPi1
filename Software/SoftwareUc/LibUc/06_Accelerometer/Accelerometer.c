/**
  ******************************************************************************
  * @file    Accelerometer.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    12/06/2016
  * @brief
  *
 *******************************************************************************/
#include "Accelerometer.h"

/************************************************************************
 * Private functions definitions
***********************************************************************/


static float Accelerometer_ReadAxe(int Axe_accelero);


/**********************************************************
 * @brief  Initializes Accelerometer 
 * @param  None
 * @retval None
**********************************************************/
void Accelerometer_init(void)
{

  // init i2c digital interface
  MR_I2C_init(I2C1, I2C1_PB6_PB7, I2C_CLOCK_100K);

  Accelerometer_writeReg( CTRL_REG1, 0x01);//

}



/**********************************************************
 * @brief  Accelerometer write register
 * @param  None
 * @retval None
**********************************************************/
void Accelerometer_writeReg(uint8_t register_address, uint8_t data)
{
  MR_I2C_Write( ACC_ADDRESS, register_address, data);
}


/**********************************************************
 * @brief  Accelerometer read register
 * @param  None
 * @retval None
**********************************************************/
uint8_t Accelerometer_readReg(uint8_t register_address)
{
uint8_t data_read;

  data_read = MR_I2C_Read(ACC_ADDRESS, register_address);

  return data_read;
}


/**********************************************************
 * @brief  Accelerometer read axe X
 * @param  None
 * @retval None
**********************************************************/
float Accelerometer_ReadAxeX(void)
{
  return Accelerometer_ReadAxe(OUT_X_MSB);
}


/**********************************************************
 * @brief  Accelerometer read axe Y
 * @param  None
 * @retval None
**********************************************************/
float Accelerometer_ReadAxeY(void)
{
  return Accelerometer_ReadAxe(OUT_Y_MSB);
}


/**********************************************************
 * @brief  Accelerometer read axe Z
 * @param  None
 * @retval None
**********************************************************/
float Accelerometer_ReadAxeZ(void)
{
  return Accelerometer_ReadAxe(OUT_Z_MSB);
}


/**********************************************************
 * @brief  Accelerometer read axe X, Y or Z
 * @param  None
 * @retval None
**********************************************************/
static float Accelerometer_ReadAxe(int Axe_accelero)
{
int8_t MSB, LSB;
float axe;

  MSB = Accelerometer_readReg(Axe_accelero);

  if(MSB > 128)
  {
    MSB = 128 - MSB;
  }

  LSB = Accelerometer_readReg(Axe_accelero+1) >> 4;

  axe = MSB << 4;
  axe = axe + LSB;

  if(axe < -2046)
  {
    axe = 0;
  }
  else
  {
    axe = (axe * 2)/2047;
  }

  return axe;
}




 // End Of file
