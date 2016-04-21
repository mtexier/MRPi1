/**
  ******************************************************************************
  * @file    mrpi1_arduino.cpp
  * @author  Mace Robotics
  * @version V0.1
  * @date    20/04/2016
  * @brief
  *
 *******************************************************************************/


#include <Arduino.h>
#include "mrpi1_arduino.h"


/**********************************************************
 * @brief  led
 * @param  None
 * @retval None
**********************************************************/
void led(int led, int state)
{
String  commande;
 
  commande = "#LED," + String(led) + "," + String(state) + "!";
  Serial.println(commande); 
  
}


/**********************************************************
 * @brief  ledToggle
 * @param  None
 * @retval None
**********************************************************/
void ledToggle(int led)
{
String  commande;
 
  commande = "#LEDT," + String(led) + "!";
  Serial.println(commande); 
}


/**********************************************************
 * @brief  firmwareVersion
 * @param  None
 * @retval None
**********************************************************/
void firmwareVersion()
{
String  commande;
 
  commande = "#FV!";
  Serial.println(commande);  
}




/**********************************************************
 * @brief  forward
 * @param  speed ( 0 to 100 )
 * @retval None
**********************************************************/
void forward(int speed)
{
String  commande;
 
  commande = "#MF," + String(speed) + "!";
  Serial.println(commande); 
  
}


/**********************************************************
 * @brief  back
 * @param  speed ( 0 to 100 )
 * @retval None
**********************************************************/
void back(int speed)
{
String  commande;
 
  commande = "#MB," + String(speed) + "!";
  Serial.println(commande); 
  
}


/**********************************************************
 * @brief  turnLeft
 * @param  speed ( 0 to 100 )
 * @retval None
**********************************************************/
void turnLeft(int speed)
{
String  commande;
 
  commande = "#TL," + String(speed) + "!";
  Serial.println(commande); 
  
}


/**********************************************************
 * @brief  turnRight
 * @param  speed ( 0 to 100 )
 * @retval None
**********************************************************/
void turnRight(int speed)
{
String  commande;
 
  commande = "#TR," + String(speed) + "!";
  Serial.println(commande); 
  
}


/**********************************************************
 * @brief  proxSensor
 * @param  speed ( 0 to 100 )
 * @retval None
**********************************************************/
int proxSensor(int number)
{
String  commande;
int data;
 
  commande = "#PROX," + String(number) + "!";
  Serial.println(commande); 

  data = readData();
  
  return data;
}


/**********************************************************
 * @brief  ambiantLight
 * @param  
 * @retval None
**********************************************************/
int ambiantLight(int number)
{
String  commande;
int data;
 
  commande = "#AL," + String(number) + "!";
  Serial.println(commande); 

  data = readData();
  
  return data;
}


/**********************************************************
 * @brief  controlEnable
 * @param  
 * @retval None
**********************************************************/
void controlEnable()
{
  Serial.println("#CRE!"); 
}


/**********************************************************
 * @brief  controlDisable
 * @param  
 * @retval None
**********************************************************/
void controlDisable()
{
  Serial.println("#CRD!"); 
}


/**********************************************************
 * @brief  stop
 * @param  
 * @retval None
**********************************************************/
void stop()
{
  Serial.println("#STP!"); 
}


/**********************************************************
 * @brief  readData
 * @param  
 * @retval None
**********************************************************/
int readData()
{ 
char c=0;        
String readString;

  while (c != '\n')
  {
    if (Serial.available() >0)
    {
      c = Serial.read();  //gets one byte from serial buffer
      if ( c != '$')
        readString += c; //makes the string readString
    } 
  }    

  return readString.toInt();
}

// end file