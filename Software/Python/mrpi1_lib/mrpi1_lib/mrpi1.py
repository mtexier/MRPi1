#!/usr/bin/python

######################################################
#  Python API
#  This library is used for the MRPi1 robot.
#  http://www.macerobotics.com
#  Date : 19/07/2016
#  Version : 0.2
#
#  MIT Licence

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
__all__ = ['controlEnable']
__all__ = ['controlDisable']
__all__ = ['forwardC']
__all__ = ['back']
__all__ = ['backC']
__all__ = ['stop']
__all__ = ['turnRight']
__all__ = ['turnRightC']
__all__ = ['turnLeft']
__all__ = ['turnLeftC']
__all__ = ['turnRight_degree']
__all__ = ['turnLeft_degree']
__all__ = ['forward_mm']
__all__ = ['back_mm']
__all__ = ['motorRight']
__all__ = ['motorLeft']
__all__ = ['encoderLeft']
__all__ = ['encoderRight']
__all__ = ['irReceiver']
__all__ = ['acceleroX']
__all__ = ['acceleroY']
__all__ = ['acceleroZ']
__all__ = ['playWav']
__all__ = ['playMp3']
__all__ = ['playTxt']
__all__ = ['play']
__all__ = ['writeCommand']
__all__ = ['readData']

###############################################################
###############################################################




# init serial port, baud rate = 115200
port = serial.Serial('/dev/ttyAMA0', 115200)




# turn led on or off
def led(led, on_off):
  """
        led on or off
        
        parameter 1 : led number (1 to 3)

        parameter 2 : led state (on = 1, off = 0)

        Exemple, led 2 on:
        >> led(2,1)
  """
  if( led not in(1,2,3) ) or (on_off not in (0,1)):
    print ("error parameter")
  else:
    led_number = str(led)
    action = str(on_off) # conversion number to string
    port.write("#LED,")
    port.write(led_number)
    port.write(",")
    port.write(action)
    port.write("!")

  
# toggle led
def ledToggle(led):
  """
        toggle led
        
        parameter : led number (1 to 3)

        Exemple:
        >> ledToggle(2)
  """
  if( led not in(1,2,3) ) :
    print("error : parameter can only be 1, 2 or 3")
  else:
    port.write("#LEDT,")
    port.write(str(led))
    port.write("!")

# Read firmware version of the microcontroller
def firmwareVersion():
  """
        Read the firmware version (microcontroller)

        Exemple:
        >> firmwareVersion()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("FV")
  value = readData()
  return __convListToFloat(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 switch methods]---------------------------------
  
# Read switch
def switch():
  """
        Read the switch state

        return switch()

        Exemple:
        >> switch()
  """
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
  if( sensor not in(1,2,3) ) :
    print ("error parameter")
  else:
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
  if( sensor not in(1,2,3,4,5,6) ) :
    print ("error parameter")
  else:
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

        parameter : 0 to 6

        return proximity sensor (0 to 4095)

        Exemple:
        >> proxSensor(2)
  """
  if( sensor not in(1,2,3,4,5,6) ) :
    print ("error parameter")
  else:
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
  else:
    print("error speed value")

# control robot enable
def controlEnable():
  """
        control robot enable

        Exemple:
        >> controlEnable()
  """
  global control_robot
  
  if control_robot == False :
    control_robot = True
    writeCommand("CRE")
  else:
    print "error : control is already enable !"

# control robot disable  
def controlDisable():
  """
        control robot disable

        Exemple:
        >> controlDisable()
  """
  global control_robot
  
  if (control_robot == True) or  (control_robot == False):
    control_robot = False
    writeCommand("CRD")

# the robot move forward with control
def forwardC(speed, distance):
  """
        move forward mrpi1 with control

        Exemple:
        >> forwardC(20, 4000)
  """
  if control_robot == True:
    speed = str(speed)
    distance = str(distance)
    port.write("#MFC,")
    port.write(distance)
    port.write(",")
    port.write(speed)
    port.write("!")
    
    while True:
      writeCommand("TGS,1")
      state = readData()
      if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
        if (state == '4'):
          print "error : speed to hight"
        chaine = 0
        break # end while 1
  else:
    print "error : control robot disable"

# the robot move forward with control (distance : millimeter)
def forward_mm(speed, distance):
  forwardC(speed, distance*4)

# the robot move back
def back(speed):
  """
        move back mrpi1

        parameter : 0 to 100

        Exemple:
        >> forward(20)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write("#MB,")
    port.write(speed)
    port.write("!")
  else:
    print("error speed value")
  
# the robot move back with control
def backC(speed, distance):
  """
        move forward mrpi1 with control

        Exemple:
        >> backC(20, 4000)
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
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
      chaine = 0
      break # end while 1 
	  
# the robot move back with control (distance : millimeter)
def back_mm(speed, distance):
  backC(speed, distance*4)

# the robot stop
def stop():
  """
        stop the robot

        Exemple:
        >> stop()
  """
  writeCommand("STP")
  
# the robot turn right
def turnRight(speed):
  """
        turn right

        parameter : speed (0 to 100)
        max speed = 100
        min speed = 0

        Exemple:
        >> turnRight(30)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write("#TR,")
    port.write(speed)
    port.write("!")
  else:
    print("error speed value")
  
# the robot turn right with control
def turnRightC(speed, distance):
  """
        turn right with control

        parameter 1 : speed (0 to 100)
        max speed = 100
        min speed = 0

        parameter 2 : degree angle
        546 = 90 degree 

        Exemple:
        >> turnRightC(10, 546)
  """
  speed = str(speed)
  distance = str(distance)
  port.write("#TRC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")

  while True:
    writeCommand("TGS,2")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
      chaine = 0
      break # end while 1 
	  
# the robot turn right with control 
def turnRight_degree(speed, degree):
  turnRightC(speed, degree*546/90)

# the robot turn left
def turnLeft(speed):
  """
        turn left

        parameter : speed (0 to 100)
        max speed = 100
        min speed = 0

        Exemple:
        >> turnLeft(30)
  """
  if speed > -1 and speed < 101:
    speed = str(speed)
    port.write("#TL,")
    port.write(speed)
    port.write("!")
  else:
    print("error speed value")
  
# the robot turn left with control
def turnLeftC(speed, distance):
  """
        turn left with control

        parameter 1 : speed (0 to 100)
        max speed = 100
        min speed = 0

        parameter 2 : degree angle
        546 = 90 degree

        Exemple:
        >> turnLeftC(10, 546)
  """
  speed = str(speed)
  distance = str(distance)
  port.write("#TLC,")
  port.write(distance)
  port.write(",")
  port.write(speed)
  port.write("!")
  
  while True:
    writeCommand("TGS,2")
    state = readData()
    if((state == '3') or (state == '4')):# state = 3 (end of trapezoid), state = 4 (error trapezoid)
      if (state == '4'):
        print "error : speed to hight"
      chaine = 0
      break # end while 1 
	  
# the robot turn right with control 
def turnLeft_degree(speed, degree):
  turnLeftC(speed, degree*546/90)
  
# the motor right
def motorRight(direction, speed):
  """
        motor right control

        parameter 1 : direction (0 or 1)

        parameter 2 : speed ( 0 to 100)     

        Exemple:
        >> motorRigh(1, 50)
  """
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTR,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")

# the motor left
def motorLeft(direction, speed):
  """
        motor left control

        parameter 1 : direction (0 or 1)

        parameter 2 : speed ( 0 to 100)     

        Exemple:
        >> motorLeft(1, 50)
  """
  dir = str(direction)
  pwm = str(speed)
  port.write("#MOTL,")
  port.write(dir)
  port.write(",")
  port.write(pwm)
  port.write("!")

#---------------------------------------------------------------------
#-------------[ MRPI1 encoders robot methods]-------------------------

# the encoderleft
def encoderLeft():
  """
        read the encoder left value  

        Exemple:
        >> encoderLeft()
  """
  writeCommand("EDL")
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  value = readData()
  return __convListToUint(value)
  
# the encoderleft
def encoderRight():
  """
        read the encoder right value  

        Exemple:
        >> encoderRight()
  """
  writeCommand("EDR")
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  value = readData()
  return __convListToUint(value)
  
#---------------------------------------------------------------------
#-------------[ MRPI1 IR receiver ]-----------------------------------

# read IR receiver
def irReceiver():
  """
        Read infrared receiver

        Exemple:
        >> irReceiver()
  """
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  port.write("#RC5!")
  value = readData()
  return __convListToUint(value) 

#---------------------------------------------------------------------
#-------------[ MRPI1 accelerometer ]-----------------------------------

# read accelerometer axe X
def acceleroX():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("ACCX")
  value = readData()
  return __convListToFloat(value) 

# read accelerometer axe Y
def acceleroY():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("ACCY")
  value = readData()
  return __convListToFloat(value) 
  
# read accelerometer axe Z
def acceleroZ():
  liste = []
  value = 0
  port.flushInput() # reset serial receive buffer
  writeCommand("ACCZ")
  value = readData()
  return __convListToFloat(value) 

#---------------------------------------------------------------------
#-------------[ MRPI1 audio robot methods]----------------------------

# play wav file, exemple : playWav("Hello.wav")
def playWav(file_wav):
  """
        play wav audio file 

        Exemple:
        >> playWav("hello.wav")
  """
  writeCommand("SPE")# enable speaker
  cmd = "aplay -D hw:1,0 " + file_wav
  os.system(cmd)
  writeCommand("SPD")# disable speaker
  
# play mp3 file, exemple : playMp3("Hello.mp3")
def playMp3(file_mp3):
  """
        play mp3 audio file 

        Exemple:
        >> playMp3("hello.wav")
  """
  writeCommand("SPE")# enable speaker
  cmd = "omxplayer " + file_mp3 
  os.system(cmd)
  writeCommand("SPD")# disable speaker

# play  text file, exemple : playFileTxt("Hello.txt")
def playTxt(file_txt):
  """
        play text file 

        Exemple:
        >> playTxt("hello.txt")
  """
  cmd = "text2wave " + file_txt
  cmd = cmd + " -o file.wav"
  os.system(cmd)
  playWav("file.wav")
  os.system("rm file.wav")

# play  text, exemple : playFileTxt("Hello MRPi1")
def play(text):
  """
        play text

        Exemple:
        >> play("hello my name is MRPi1")
  """
  cmd = 'echo "' + text + '" | festival --tts'
  writeCommand("SPE")# enable speaker
  os.system(cmd)
  writeCommand("SPD")# disable speaker
  
#---------------------------------------------------------------------
#-------------[ MRPI1 serial2 methods]----------------------------
  
# play  text file, exemple : playFileTxt("Hello.txt")
def serial2Write(data):
  """
        serial 2 write 

        Exemple:
        >> serial2Write("HELLO")
  """
  port.write("#SRLW,")
  port.write(data)
  port.write("!")
  

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
  
  
# control robot (postion/orientation disable)
control_robot = False
controlDisable()
 
# end file