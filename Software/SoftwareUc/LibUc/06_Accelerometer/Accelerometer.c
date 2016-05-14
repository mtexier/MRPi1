/**
  ******************************************************************************
  * @file    Accelerometer.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/
#include "Accelerometer.h"



/************************************************************************
 * Private functions definitions
***********************************************************************/
static void Accelerometer_writeReg(uint8_t register_address, uint8_t data);
static uint8_t Accelerometer_readReg(uint8_t register_address);
static void Accelerometer_standby(void);
static void Accelerometer_active(void);

static void mma8652Reg8Writre (I2C_HandleTypeDef *i2cHandle, uint8_t reg, uint8_t value);



/**********************************************************
 * @brief  Initializes Accelerometer 
 * @param  None
 * @retval None
**********************************************************/
void Accelerometer_init(void)
{
uint8_t data;

  // init i2c digital interface
 MR_I2C_init(I2C1, I2C1_PB6_PB7, I2C_CLOCK_100K);







  // Put the part in Standby Mode
  //Accelerometer_standby();

 //MR_I2C_Write(ACC_ADDRESS,CTRL_REG1,0x44);














}



/**********************************************************
 * @brief  Accelerometer write register
 * @param  None
 * @retval None
**********************************************************/
static void Accelerometer_writeReg(uint8_t register_address, uint8_t data)
{
uint8_t r;

  r = MR_I2C_Write( ACC_ADDRESS, register_address, data);





}


/**********************************************************
 * @brief  Accelerometer read register
 * @param  None
 * @retval None
**********************************************************/
static uint8_t Accelerometer_readReg(uint8_t register_address)
{
uint8_t data;

  MR_I2C_Read(ACC_ADDRESS, register_address, &data);



  return 22;
}


/**********************************************************
 * @brief  Put the sensor into Standby Mode 
 * @param  None
 * @retval None
**********************************************************/
static void Accelerometer_standby(void)
{
uint8_t data;

 // data = Accelerometer_readReg(CTRL_REG1);
  //Accelerometer_writeReg( CTRL_REG1, data & ~(0x01));
  //Accelerometer_writeReg( CTRL_REG1, 0x00);

}


/**********************************************************
 * @brief  Put the sensor into Active Mode 
 * @param  None
 * @retval None
**********************************************************/
static void Accelerometer_active(void)
{
uint8_t data;

 // data = Accelerometer_readReg(CTRL_REG1);

 // Accelerometer_writeReg( CTRL_REG1, data | 0x01);
}
 
 // End Of file
