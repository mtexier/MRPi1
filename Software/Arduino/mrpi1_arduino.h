/**
  ******************************************************************************
  * MRPi Arduino Interface
  *
  * @file    mrpi1_arduino.cpp
  * @author  Mace Robotics
  * @version V0.1
  * @date    20/04/2016
  * @brief
  *
 *******************************************************************************/

#ifndef _MRPi1_ARDUINO_H
#define _MRPi1_ARDUINO_H

/**
 * Set a led state
 *
 * @param led [in] id of the led
 * @param state [in] state to set
 */
void led(int led, int state);

/**
 * Toggle led state
 * @param led [in] id of the led
 */
void ledToggle(int led);


/**
 * Print firmware version
 */
void firmwareVersion();

/**
 * Move robot forward
 * @param speed [in] movement speed (0 to 100)
 */
void forward(int speed);

/**
 * Move the robot backward
 *
 * @param speed [in] movement speed (0 to 100)
 */
void back(int speed);


/**
 * Turn the robot left
 *
 * @param speed [in] movement speed (0 to 100)
 */
void turnLeft(int speed);

/**
 * Turn the robot right
 *
 * @param speed [in] movement speed (0 to 100)
 */
void turnRight(int speed);

/**
 * Read a proximity sensor
 *
 * @param number [in] id of the sensor to read
 * @return sensor status
 */
int proxSensor(int number);

/**
 * Read the ambiant light sensor
 *
 * @param number [in] : sensor to read
 * @return sensor status
 */
int ambiantLight(int number);

void controlEnable();
void controlDisable();

/**
 * Stop robot movement
 */
void stop();

int readData();


#endif
