/**
  ******************************************************************************
  * @file    MRPi1.h
  * @author  Mace Robotic
  * @version V1.0
  * @date    22/08/2016
  * @brief	
  *
 *******************************************************************************/
#ifndef _MRPi1_H
#define _MRPi1_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_LEDS 3
#define NUMBER_GROUND_SENSORS 3
#define NUMBER_PROX_SENSORS 6
#define SIZE_BUFFER_READ 100

typedef enum
{
FORWARD,
BACK
}MotorDirection;

int init();

// Led control
int led(unsigned int id, unsigned int state);
int ledToggle(unsigned int id); 

// move robot
void forward(unsigned int speed); 
void back(unsigned int speed); 
void stop(void); 
void turnRight(unsigned int speed); 
void turnLeft(unsigned int speed);
void forwardC(unsigned int speed, unsigned int distance); 

// control
void controlEnable(void);
void controlDisable(void);
 
// motor control
void motorRight(MotorDirection direction, unsigned int speed); 
void motorLeft(MotorDirection direction, unsigned int speed);  

// Firmware
float firmwareVersion(void);

// Battery
float battery(void);

// temperature
float temperature(void);

// ground sensor
unsigned int groundSensor(unsigned int sensor);

// ambiant light
unsigned int ambiantLight(unsigned int sensor);

// proximity sensor
unsigned int proxSensor(unsigned int sensor);

// encoder sensor
int encoderLeft();
int encoderRight();

// accelerometer
float acceleroX();
float acceleroY();
float acceleroZ();



// play wav file
void playWav(char *file);

void playTxt(char *file);

void play(char *file);


#endif
// End Of File
