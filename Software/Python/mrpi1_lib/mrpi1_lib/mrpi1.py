#!/usr/bin/python

######################################################
#  Python API
#  This library is used for the MRPi1 robot.
#  http://www.macerobotics.com
# Date : 20/01/2016
# Version : 0.1
#
# Licence

######################################################

import serial
import time
import os

###############################################################
###############################################################

__all__ = ['led']
__all__ = ['ledToggle']
__all__ = ['firmwareVersion']
__all__ = ['switch']
__all__ = ['battery']
__all__ = ['temperature']
__all__ = ['groundSensor']
__all__ = ['ambiantLight']
__all__ = ['proxSensor']
__all__ = ['forward']
__all__ = ['forwardC']
__all__ = ['back']
__all__ = ['backC']
__all__ = ['stop']
__all__ = ['turnRight']
__all__ = ['turnRightC']
__all__ = ['turnLeft']
__all__ = ['turnLeftC']
__all__ = ['motorRight']
__all__ = ['motorLeft']
__all__ = ['encoderLeft']
__all__ = ['encoderRight']
__all__ = ['playWav']
__all__ = ['playTxt']
__all__ = ['play']
__all__ = ['writeCommand']
__all__ = ['readData']

###############################################################
###############################################################


# init serial port
port = serial.Serial('/dev/ttyAMA0', 115200)


# turn led on or off
def led(led, on_off):

  if led not in(1,2,3):
    raise ValueError("param can only be 1,2 or 3")
  if on_off not in (0,1):
    raise ValueError("param can only be 0 or 1")
   
  led_number = str(led)
  action = str(on_off) # conversion number to string
  port.write("#LED,")
  port.write(led_number)
  port.write(",")
  port.write(action)
  port.write("!")

  
# toggle led
def ledToggle(led):
  if led not in(1,2,3):
    raise ValueError("param can only be 1,2 or 3") 
  port.write("#LEDT,")
  port.write(str(led))
  port.write("!")

# Read firmware version of the microcontroller
def firmwareVersion():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("FV")
  value = readData()
  return __convListToUint(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 switch methods]---------------------------------
  
# Read switch
def switch():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("SW")
  value = readData()
  return __convListToUint(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 class sensors methods]--------------------------

# get battery tension
def battery():
  """
        Read battery tension

        return tension (volt)

        Exemple:
        >> battery()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("BAT")
  value = readData()
  return __convListToFloat(value) 
  
# get the temperature
def temperature():
  """
        Read temperature

        return temperature (degree)

        Exemple:
        >> temperature()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("TE")
  value = readData()
  return __convListToFloat(value) 
  
# read ground sensor
def groundSensor(sensor):
  """
        Read ground sensors (1 to 3)

        Exemple:
        >> groundSensor(1)
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  port.write("#GR,")
  port.write( str(sensor) )
  port.write("!")
  value = readData()
  return __convListToFloat(value) 
  
# read ambiant light sensor
def ambiantLight(sensor):
  """
        Read ambiantLight

        parameter : 0 to 3

        return ambiantLight (0 to 4095)

        Exemple:
        >> ambiantLight(0)
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  port.write("#AL,")
  port.write( str(sensor) )
  port.write("!")
  value = readData()
  return __convListToUint(value)
  
  
# read proximity sensor
def proxSensor(sensor):
  """
        Read proximity sensor

        parameter : 0 to 3

        return proximity sensor (0 to 4095)

        Exemple:
        >> proxSensor(2)
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  port.write("#PROX,")
  port.write( str(sensor) )
  port.write("!")
  value = readData()
  return __convListToUint(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 move robot methods]------------


# the robot move forward (speed :0 to 100 %)
def forward(speed):
  """
        move forward mrpi1

        parameter : 0 to 100

        Exemple:
        >> forward(20)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write("#MF,")
    port.write(speed)
    port.write("!")
    print "move forward"
  else:
    raise ValueError("error speed")

# the robot move forward with control
def forwardC(speed, distance):
  """
        move forward mrpi1 with control

        Exemple:
        >> forwardC(20, 4000)
  """
  speed = str(speed)
  distance = str(distance)
  port.write("#MFC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  while True:
    writeCommand("TGS,1")
    chaine = readData()
    if(chaine == '3'):
      print "FIN"
      chaine = 0
      break

# the robot move back
def back(speed):
  """
        move back mrpi1

        parameter : 0 to 100

        Exemple:
        >> forward(20)
  """
  speed = str(speed)
  port.write("#MB,")
  port.write(speed)
  port.write("!")
  
# the robot move back with control
def backC(speed, distance):
  """
        move forward mrpi1 with control

        Exemple:
        >> forwardC(20, 4000)
  """
  speed = str(speed)
  distance = str(distance)
  port.write("#MBC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  print "move back with control"
  
  while True:
    writeCommand("TGS,1")
    chaine = readData()
    if(chaine == '3'):
      print "FIN"
      chaine = 0
      break

# the robot stop
def stop():
  writeCommand("STP")
  
# the robot turn right
def turnRight(speed):
  speed = str(speed)
  port.write("#TR,")
  port.write(speed)
  port.write("!")
  print "turn right"
  
# the robot turn right with control
def turnRightC(speed, distance):
  speed = str(speed)
  distance = str(distance)
  port.write("#TRC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")

  while True:
    writeCommand("TGS,2")
    chaine = readData()
    if(chaine == '3'):
      print "FIN"
      chaine = 0
      break

# the robot turn left
def turnLeft(speed):
  speed = str(speed)
  port.write("#TL,")
  port.write(speed)
  port.write("!")
  print "turn left"
  
# the robot turn left with control
def turnLeftC(speed, distance):
  speed = str(speed)
  distance = str(distance)
  port.write("#TLC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  while True:
    writeCommand("TGS,2")
    chaine = readData()
    if(chaine == '3'):
      print "FIN"
      chaine = 0
      break
  
# the motor right
def motorRight(direction, speed):
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTR,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")
  print "motor right"

# the motor left
def motorLeft(direction, speed):
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTL,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")
  print "motor left"

#---------------------------------------------------------------------
#-------------[ MRPI1 encoders robot methods]-------------------------

# the encoderleft
def encoderLeft(self):
  writeCommand("EDL")
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  while value != '?':
    value = port.read()
    liste.append( value ) # Add an item to the end of the list
  return __convListToUint(liste)
  
# the encoderleft
def encoderRight(self):
  writeCommand("EDR")
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  while value != '?':
    value = port.read()
    liste.append( value ) # Add an item to the end of the list
  return __convListToUint(liste)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 audio robot methods]----------------------------

# play wav file, exemple : playWav("Hello.wav")
def playWav(file_wav):
  writeCommand("SPE")# enable speaker
  cmd = "aplay -D hw:1,0 " + file_wav
  os.system(cmd)
  writeCommand("SPD")# disable speaker

# play  text file, exemple : playFileTxt("Hello.txt")
def playTxt(file_txt):
  cmd = "text2wave " + file_txt
  cmd = cmd + " -o file.wav"
  os.system(cmd)
  playWav("file.wav")
  os.system("rm file.wav")

# play  text, exemple : playFileTxt("Hello MRPi1")
def play(text):
  cmd = 'echo "' + text + '" | festival --tts'
  writeCommand("SPE")# enable speaker
  os.system(cmd)
  writeCommand("SPD")# disable speaker

#------------------------------------------------------------
#-------------[ MRPI1 class utils private methods]------------
 
# convert list to unsigned int
def __convListToUint(liste):
  a=''
  i=0
  while i < (len(liste)):
    a = a + liste[i]
    i = i + 1
  return(int(a))

# write command
def writeCommand(command):
  port.write('#')
  port.write(command)
  port.write('!')
  
# read data
def readData():
  chaine = port.readline()
  pos1 = chaine.find('$')
  pos2 = chaine.find('\n')
  chaine = chaine[pos1+1:pos2]
  return chaine 
  
# convert list to float
def __convListToFloat(liste):
  a=''
  i=0
  while i < (len(liste)):# minus '?'
    a = a + liste[i]
    i = i + 1
  return(float(a))
  