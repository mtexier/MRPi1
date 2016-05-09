/**
  ******************************************************************************
  * @file    Board.h
  * @author  Mace Robotics
  * @version V1.0
  * @date    5/11/2015
  * @brief	 Definition of the I/O
  *
 *******************************************************************************/
#ifndef _BOARD_H
#define _BOARD_H

#include "stm32f4xx.h"
#include "Scheduler.h"
#include "Adc.h"
#include "Leds.h"
#include "LedOnOff.h"
#include "Motors.h"
#include "Adc.h"
#include "Speaker.h"
#include "IRremote.h"
#include "ProximitySensors.h"
#include "Usart.h"
#include "MoveRobot.h"
#include "BatteryTension.h"
#include "TempSensor.h"
#include "Switchs.h"
#include "GroundSensor.h"
#include "ComRPI.h"
#include "ChargeManagement.h"
#include "FirmwareVersion.h"
#include "I2C.h"
#include "SPI.h"
#include "Accelerometer.h"
#include "Encoder.h"
#include "positionControl.h"
#include "trapezoidGenerator.h"
#include "control.h"
#include "debug.h"
#include "trajectoryGenerator.h"

/**
  * @brief LEDS
  */
#define LED1_PORT GPIOA // LED ON/OFF
#define LED1_PIN  GPIO_PIN_5

#define LED2_PORT GPIOD
#define LED2_PIN  GPIO_PIN_1

#define LED3_PORT GPIOD
#define LED3_PIN  GPIO_PIN_2

#define LED4_PORT GPIOD
#define LED4_PIN  GPIO_PIN_3

#define LED5_PORT GPIOE       // LOW BATTERY
#define LED5_PIN  GPIO_PIN_8


/**
  * @brief IR Proximity
  */
#define IR1_PORT GPIOC
#define IR1_PIN  GPIO_PIN_0

#define IR2_PORT GPIOC
#define IR2_PIN  GPIO_PIN_1

#define IR3_PORT GPIOC
#define IR3_PIN  GPIO_PIN_2

#define IR4_PORT GPIOC
#define IR4_PIN  GPIO_PIN_3

#define IR5_PORT GPIOB
#define IR5_PIN  GPIO_PIN_0

#define IR6_PORT GPIOB
#define IR6_PIN  GPIO_PIN_1

/**
  * @brief IR Proximity Enable
  */
#define IR1EN_PORT GPIOA
#define IR1EN_PIN  GPIO_PIN_10

#define IR2EN_PORT GPIOA
#define IR2EN_PIN  GPIO_PIN_13

#define IR3EN_PORT GPIOA
#define IR3EN_PIN  GPIO_PIN_14

#define IR4EN_PORT GPIOD
#define IR4EN_PIN  GPIO_PIN_6

#define IR5EN_PORT GPIOD
#define IR5EN_PIN  GPIO_PIN_7

#define IR6EN_PORT GPIOE
#define IR6EN_PIN  GPIO_PIN_2

/**
  * @brief IR 38 Khz Reception
  */
#define IR38K_PORT GPIOA
#define IR38K_PIN  GPIO_PIN_8


/**
  * @brief Speaker
  */
#define SPEAKER_ENABLE_PORT GPIOB
#define SPEAKER_ENABLE_PIN  GPIO_PIN_14

/**
  * @brief Temperature Sensor
  */
#define TEMP_PORT GPIOA
#define TEMP_PIN  GPIO_PIN_2

/**
  * @brief Accelerometer IRQ
  */
#define ACC_IRQ_PORT GPIOE
#define ACC_IRQ_PIN  GPIO_PIN_5

/**
  * @brief I2C BUS
  */
#define I2C_SDA_PORT GPIOB
#define I2C_SDA_PIN  GPIO_PIN_7

#define I2C_SCL_PORT GPIOB
#define I2C_SCL_PIN  GPIO_PIN_6

/**
  * @brief SPI BUS
  */
#define SPI_SCK_PORT GPIOB
#define SPI_SCK_PIN  GPIO_PIN_3

#define SPI_MISO_PORT GPIOB
#define SPI_MISO_PIN  GPIO_PIN_4

#define SPI_MOSI_PORT GPIOB
#define SPI_MOSI_PIN  GPIO_PIN_5

#define SPI_CS1_PORT GPIOA
#define SPI_CS1_PIN  GPIO_PIN_15


/**
  * @brief Battery Tension
  */
#define BATT_PORT GPIOA
#define BATT_PIN  GPIO_PIN_0

/**
  * @brief H-Bridge DC Motor
  */
#define HBRIDGE_DIR1_PORT GPIOD
#define HBRIDGE_DIR1_PIN  GPIO_PIN_14

#define HBRIDGE_DIR2_PORT GPIOD
#define HBRIDGE_DIR2_PIN  GPIO_PIN_15

#define HBRIDGE_PWM1_PORT GPIOC
#define HBRIDGE_PWM1_PIN  GPIO_PIN_8

#define HBRIDGE_PWM2_PORT GPIOC
#define HBRIDGE_PWM2_PIN  GPIO_PIN_9

#define HBRIDGE_SLEEP_PORT GPIOB
#define HBRIDGE_SLEEP_PIN  GPIO_PIN_15

/**
  * @brief USB  management
  */
#define USB_CURRENT_PORT GPIOA
#define USB_CURRENT_PIN  GPIO_PIN_3

#define USB_PRESENT_PORT GPIOA
#define USB_PRESENT_PIN  GPIO_PIN_7

/**
  * @brief Switchs
  */
#define SWITCH1_PORT GPIOD
#define SWITCH1_PIN  GPIO_PIN_4

/**
  * @brief Ground sensors
  */
#define GRDS1_PORT GPIOA
#define GRDS1_PIN  GPIO_PIN_1
#define GRDS2_PORT GPIOA
#define GRDS2_PIN  GPIO_PIN_4
#define GRDS3_PORT GPIOA
#define GRDS3_PIN  GPIO_PIN_6


/**
  * @brief Encoder
  */
#define ENCOD1A_PORT GPIOC
#define ENCOD1A_PIN  GPIO_PIN_6

#define ENCOD1B_PORT GPIOC
#define ENCOD1B_PIN  GPIO_PIN_7

#define ENCOD2A_PORT GPIOE
#define ENCOD2A_PIN  GPIO_PIN_9

#define ENCOD2B_PORT GPIOE
#define ENCOD2B_PIN  GPIO_PIN_11



void Board_init(void);

#endif
// End Of File
