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


void led(int led, int state)
{
  String  commande;
  commande = "#LED," + String(led) + "," + String(state) + "!";
  Serial.println(commande); 
}

void ledToggle(int led)
{
  String  commande;
  commande = "#LEDT," + String(led) + "!";
  Serial.println(commande); 
}

void firmwareVersion()
{
  String  commande;
  commande = "#FV!";
  Serial.println(commande);  
}

void forward(int speed)
{
  String  commande;
  commande = "#MF," + String(speed) + "!";
  Serial.println(commande); 
}

void back(int speed)
{
  String  commande;
  commande = "#MB," + String(speed) + "!";
  Serial.println(commande); 
}


void turnLeft(int speed)
{
  String  commande;
  commande = "#TL," + String(speed) + "!";
  Serial.println(commande); 
}


void turnRight(int speed)
{
  String  commande;
  commande = "#TR," + String(speed) + "!";
  Serial.println(commande); 
}

int proxSensor(int number)
{
  String  commande;
  int data;
 
  commande = "#PROX," + String(number) + "!";
  Serial.println(commande); 

  data = readData();
  return data;
}

int ambiantLight(int number)
{
  String  commande;
  int data;
 
  commande = "#AL," + String(number) + "!";
  Serial.println(commande); 

  data = readData();
  return data;
}

void controlEnable()
{
  Serial.println("#CRE!"); 
}

void controlDisable()
{
  Serial.println("#CRD!"); 
}

void stop()
{
  Serial.println("#STP!"); 
}

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

