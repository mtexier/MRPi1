/**
  ******************************************************************************
  * @file    MoveRobot.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief
  *
 *******************************************************************************/

#include "MoveRobot.h"

/**********************************************************
 * @brief  Init move robot
 * @param  None
 * @retval None
**********************************************************/
void MoveRobot_init(void)
{
  Motors_init();
}

/**********************************************************
 * @brief  stop robot
 * @param  None
 * @retval None
**********************************************************/
void MoveRobot_stop(void)
{
  Motors_stop();
}


/**********************************************************
 * @brief  Move robot forward
 * @param  Speed (0 to 100 %)
 * @retval None
**********************************************************/
void MoveRobot_forward(uint32_t Speed)
{
  Motor_right(MOTOR_FORWARD, Speed-3); // -3 motor no perfect
  Motor_left(MOTOR_FORWARD, Speed);
}


/**********************************************************
 * @brief  Move robot back
 * @param  Speed (0 to 100 %
 * @retval None
**********************************************************/
void MoveRobot_back(uint32_t Speed)
{
  Motor_right(MOTOR_BACK, Speed);
  Motor_left(MOTOR_BACK, Speed);
}


/**********************************************************
 * @brief  Move robot turn right
 * @param  Angle (degree)
 * @retval None
**********************************************************/
void MoveRobot_turn_right(uint32_t Speed)
{
  Motor_right(MOTOR_BACK, Speed);
  Motor_left(MOTOR_FORWARD, Speed);
}


/**********************************************************
 * @brief  Move robot turn left
 * @param  Angle (degree)
 * @retval None
**********************************************************/
void MoveRobot_turn_left(uint32_t Speed)
{
  Motor_right(MOTOR_FORWARD, Speed);
  Motor_left(MOTOR_BACK, Speed);
}
 // End Of file
