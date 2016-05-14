/**
  ******************************************************************************
  * @file    positionControl.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    30/12/2015
  * @brief   Position control
  *
  * 
 *******************************************************************************/
#include <math.h>
#include "positionControl.h"



/************************************************************************
 * global variables
***********************************************************************/
struct_postionRobot postionRobot;
static float XposRobot = 0;
static float YposRobot = 0;
static void robotSpeedCalculator(int32_t wheelRight, int32_t wheelLeft );


/**********************************************************
 * @brief  position Control robot
 * @param  None
 * @retval None
**********************************************************/
void positionControl(void)
{
float deltaX=0, deltaY=0;
float encoderLeft, encoderRight;
float deltaDistance;



  //Read encoder
  encoderLeft = -encodeurLeft();
  encoderRight = -encodeurRight();



  // step distance calcul
  postionRobot.stepDistance = (float)(encoderRight + encoderLeft)/2;

  // delta distance calcul
  deltaDistance = postionRobot.stepDistance - postionRobot.old_stepDistance;
  postionRobot.old_stepDistance = postionRobot.stepDistance;

  // speed calculator (distance)
  robotSpeedCalculator((int32_t)encoderRight, (int32_t)encoderLeft);

  // step orientation calculator
  postionRobot.stepOrientation = encoderRight - encoderLeft;

  // radian orientation calculator
  postionRobot.radOrientation = postionRobot.stepOrientation * (float)(0.00032);

  // delat X and Y position robot calculator
  deltaX = (float)(deltaDistance*cos(postionRobot.radOrientation));
  deltaY = (float)(deltaDistance*sin(postionRobot.radOrientation));

  // X and Y position of the robot
  XposRobot = XposRobot + deltaX;
  YposRobot = YposRobot + deltaY;

  postionRobot.Xrobot = XposRobot;
  postionRobot.Yrobot = -YposRobot;

}


/**********************************************************
 * @brief  positionControl_stepDistance
 * @param  None
 * @retval step distance(unit = encoder tick)
**********************************************************/
int32_t positionControl_stepDistance(void)
{
  return((int32_t)(postionRobot.stepDistance));
}


/**********************************************************
 * @brief  positionControl_stepSpeedDistance
 * @param  None
 * @retval None
**********************************************************/
int32_t positionControl_stepSpeedDistance(void)
{
  return((int32_t)(postionRobot.stepSpeed_distance));
}


/**********************************************************
 * @brief  positionControl_stepOrientation
 * @param  None
 * @retval None
**********************************************************/
int32_t positionControl_stepOrientation(void)
{
  return((int32_t)(postionRobot.stepOrientation));
}


/**********************************************************
 * @brief  positionControl_stepOrientation
 * @param  None
 * @retval None
**********************************************************/
int32_t positionControl_stepSpeedOrientation(void)
{
  return((int32_t)(postionRobot.stepSpeed_orientation));
}


/**********************************************************
 * @brief  robotSpeedCalculator
 * @param  None
 * @retval None
**********************************************************/
static void robotSpeedCalculator(int32_t wheelRight, int32_t wheelLeft )
{
float speedWheelRight=0;
float speedWheelLeft=0;
static int32_t old_wheelRightDistance;
static int32_t old_wheelLeftDistance;


  speedWheelRight = wheelRight - old_wheelRightDistance;
  old_wheelRightDistance = wheelRight;

  speedWheelLeft = wheelLeft - old_wheelLeftDistance;
  old_wheelLeftDistance = wheelLeft;

  // Speed robot (distance)
  postionRobot.stepSpeed_distance = (speedWheelRight + speedWheelLeft)/2;

  // Speed robot (orientation)
  postionRobot.stepSpeed_orientation = speedWheelRight - speedWheelLeft;

}

 // End Of file
