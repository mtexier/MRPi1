/**
  ******************************************************************************
  * @file    control.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    30/12/2015
  * @brief   control robot with PID
  *
  * 
 *******************************************************************************/
#include "control.h"

// state control robot
static bool state_control_robot = false;

int32_t distance_control = 0;

uint32_t test_counter = 0;



/**********************************************************
 * @brief  controlManage
 * @param  distanceCommand and orientationCommand
 * @retval None
**********************************************************/
void controlManage(int32_t distanceCommand, int32_t orientationCommand )
{
float DistanceRobot, OrientationRobot;
float DistanceSpeed, OrientationSpeed;
float error_distance, error_orientation;
float command, command_distance, command_orientaton;
int32_t wheelRightCommand, wheelLeftCommand;

  // ************************** control Distance ********************************************************/


  // read distance
  DistanceRobot = positionControl_stepDistance();

  // read speed
  DistanceSpeed = positionControl_stepSpeedDistance();

  // distance error calcul
  error_distance = distanceCommand - DistanceRobot;

  command = error_distance*GAIN_P_DISTANCE/(GAIN_COM);

  command_distance = command - (GAIN_P_DISTANCE)*DistanceSpeed/(GAIN_COM);

  // ************************** end control Distance ********************************************************/


  // ************************** control Orientation ********************************************************/

  // read orientation
  OrientationRobot = positionControl_stepOrientation();

  // read speed
  OrientationSpeed = positionControl_stepSpeedOrientation();

  // orientation error calcul
  error_orientation = orientationCommand - OrientationRobot;

  command = error_orientation*GAIN_P_ORIENTATION/(GAIN_COM);

  command_orientaton = command - (GAIN_P_ORIENTATION)*OrientationSpeed/(GAIN_COM);



  // ************************** end control Orientation ********************************************************/


  // wheels command
  wheelRightCommand = command_distance + command_orientaton;
  wheelLeftCommand = command_distance - command_orientaton;

  // saturation
  if(wheelRightCommand > MOTOR_CMD_MAX )
	  wheelRightCommand = MOTOR_CMD_MAX;

  if(wheelLeftCommand > MOTOR_CMD_MAX )
	  wheelLeftCommand = MOTOR_CMD_MAX;

  if(wheelRightCommand < -MOTOR_CMD_MAX )
	  wheelRightCommand = -MOTOR_CMD_MAX;

  if(wheelLeftCommand < -MOTOR_CMD_MAX )
	  wheelLeftCommand = -MOTOR_CMD_MAX;


  // right motor
  if(wheelRightCommand > 0)
    Motor_right(MOTOR_FORWARD, wheelRightCommand );
  else
    Motor_right(MOTOR_BACK, -wheelRightCommand );


  // left motor
  if(wheelLeftCommand > 0)
    Motor_left(MOTOR_FORWARD, wheelLeftCommand );
  else
    Motor_left(MOTOR_BACK, -wheelLeftCommand );


}


/**********************************************************
 * @brief  controlWrite
 * @param  distanceCommand
 * @retval None
**********************************************************/
void controlWrite(int32_t distanceCommand )
{

	distance_control = distanceCommand;
}


/**********************************************************
 * @brief  controlEnableDisable
 * @param  state
 * @retval None
**********************************************************/
void controlEnable(bool state)
{
  state_control_robot = state;
}


/**********************************************************
 * @brief  controlState
 * @param  state
 * @retval None
**********************************************************/
bool controlState(void)
{
  return(state_control_robot);
}


 // End Of file
